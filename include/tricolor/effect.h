/*
 * Copyright 2025 Mitchell Matsumori-Kelly
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#pragma once

#include <freertos/FreeRTOS.h>

#include <atomic>
#include <functional>
#include <memory>

// #include "analog.h"
#include "color.h"

namespace tricolor {

    using Time = uint16_t;

    class Colorable {
    public:
        virtual ~Colorable() {}

        virtual void set_color(Color color) = 0;
    };

    class Effect {
    public:
        Effect() {}

        virtual ~Effect() {}

        virtual void reset() {}

        virtual Color step(Color current, Time elapsed) = 0;
    };

    class PeriodicEffect: public Effect {
    public:
        PeriodicEffect(Time period) : m_period(period), m_time(0) {}

        virtual void reset() {
            m_time = 0;
        }

        virtual Color step(Color current, Time elapsed) {
            m_time = (m_time + elapsed) % m_period;
            return current;
        }

        Time period() const {
            return m_period;
        }

        Time time() const {
            return m_time;
        }

    protected:
        Time m_period;
        Time m_time;
    };

    class Solid: public Effect {
    public:
        Solid(Color color) : m_color(color) {}

        virtual Color step(Color current, Time elapsed) override {
            __unused(current);
            __unused(elapsed);
            return m_color;
        }

    protected:
        Color m_color;
    };

    /// @brief Blink on/off
    ///
    /// |             t_on
    /// |          ┌───────-┐
    /// |          │        │
    /// |──────────┘        └───
    /// |   t_off
    /// |
    class Blink: public PeriodicEffect {
        Time m_time_off;

    public:
        Blink(Time time_on, Time time_off) :
            PeriodicEffect(time_on + time_off),
            m_time_off(time_off) {}

        Blink(uint32_t period) : Blink(period / 2, period / 2) {}

        virtual Color step(Color current, Time elapsed) override {
            current = PeriodicEffect::step(current, elapsed);
            return (m_time < m_time_off) ? Color(0, 0, 0) : current;
        }
    };

    /// @brief Blink on/off
    /// |                 t_on
    /// |              /───────-\
    /// |  ramp_up >> /          \  ramp_down
    /// |────────────/            \
    /// |   t_off
    /// |
    class Breathe: public PeriodicEffect {
        Time m_off;
        Time m_ramp_up;
        Time m_on;
        Time m_ramp_down;

    public:
        /// @brief Breathe effect
        /// @param period Duration of the entire effect
        Breathe(Time period) : Breathe(period / 6, period / 3, period / 3, period / 6) {}

        /// @brief Breathe effect
        /// @param off Duration of the "off" segment
        /// @param ramp_up Duration of "ramp up" segment
        /// @param on Duration of the "on" segment
        /// @param ramp_down Duration of the "ramp down" segment
        Breathe(Time off, Time ramp_up, Time on, Time ramp_down) :
            PeriodicEffect(off + ramp_up + on + ramp_down),
            m_off(off),
            m_ramp_up(ramp_up),
            m_on(on),
            m_ramp_down(ramp_down) {}

        virtual Color step(Color v, Time elapsed) override {
            v = PeriodicEffect::step(v, elapsed);
            // off
            if (m_time < m_off) {
                return Color::BLACK;
            }
            // ramp up
            else if (m_time < m_off + m_ramp_up) {
                Time rel = m_time - m_off;
                return v * ((float)rel / m_ramp_up);
            }
            // on
            else if (m_time < m_off + m_ramp_up + m_on) {
                return v;
            }
            // ramp down
            else {
                Time rel = m_time - (m_off + m_ramp_up + m_on);
                return v * (1.0 - (float)rel / m_ramp_down);
            }
        }
    };

    class Invert: public Effect {
    public:
        virtual Color step(Color v, Time elapsed) override {
            __unused(elapsed);
            return 255 - v;
        }
    };

    class MaxLevel: public Effect {
    public:
        MaxLevel(uint8_t r, uint8_t g, uint8_t b) : r(r), g(g), b(b) {}

        virtual Color step(Color current, Time elapsed) override {
            __unused(elapsed);
            return Color(
                current.r > r ? r : current.r,
                current.g > g ? g : current.g,
                current.b > b ? b : current.b
            );
        }

    private:
        uint8_t r, g, b;
    };

    class MinLevel: public Effect {
    public:
        MinLevel(uint8_t r, uint8_t g, uint8_t b) : r(r), g(g), b(b) {}

        virtual Color step(Color current, Time elapsed) override {
            __unused(elapsed);
            return Color(
                current.r < r ? r : current.r,
                current.g < g ? g : current.g,
                current.b < b ? b : current.b
            );
        }

    private:
        uint8_t r, g, b;
    };

    class EffectChain: public Effect {
        using EffectPtr = std::unique_ptr<Effect>;

    public:
        /// @brief Create an empty effect chain
        EffectChain() {}

        /// @brief Copy all effects from a chain into a new one
        /// @param other The effect chain to copy
        // EffectChain(const EffectChain& other) {
        //     for (const EffectPtr& e : other.m_effects) {
        //         add(*e.get());
        //     }
        // }
        EffectChain(const EffectChain& other) = delete;

        void clear() {
            m_effects.clear();
        }

        void reset() {
            for (EffectPtr& e : m_effects) {
                e->reset();
            }
        }

        Color step(Time elapsed) {
            return step(Color(), elapsed);
        }

        /// @brief Add a new effect to the end of the chain.
        /// @param e The effect
        template<typename E>
        EffectChain& add(E&& e) {
            m_effects.emplace_back(new E(std::forward<E>(e)));
            return *this;
        }

        /// @brief Add a "blink" effect to the end of the chain.
        /// @param period The number of time units before repeating
        EffectChain& blink(Time period) {
            return add(Blink(period));
        }

        /// @brief Add a "blink" effect to the end of the chain.
        /// @param on The number of time units to remain on.
        /// @param off The number of time units to remain off.
        EffectChain& blink(Time on, Time off) {
            return add(Blink(on, off));
        }

        EffectChain& breathe(Time period) {
            return add(Breathe(period));
        }

        EffectChain& breathe(Time off, Time ramp_up, Time on, Time ramp_down) {
            return add(Breathe(off, ramp_up, on, ramp_down));
        }

        /// @brief Add an "invert" effect to the end of the chain. This will
        /// flip the color so that each component ends up with a level of
        /// `255 - original`.
        EffectChain& invert() {
            return add(Invert());
        }

        EffectChain& solid(Color color) {
            return add(Solid(color));
        }

        EffectChain& solid(uint32_t rgb) {
            return add(Solid(Color(rgb)));
        }

        EffectChain& solid(uint8_t r, uint8_t g, uint8_t b) {
            return add(Solid(Color(r, g, b)));
        }

        EffectChain& max_level(uint8_t r, uint8_t g, uint8_t b) {
            return add(MaxLevel(r, g, b));
        }

        EffectChain& max_level(uint8_t max) {
            return add(MaxLevel(max, max, max));
        }

        EffectChain& min_level(uint8_t min) {
            return add(MinLevel(min, min, min));
        }

    protected:
        Color step(Color level, Time elapsed) override {
            for (EffectPtr& e : m_effects) {
                level = e->step(level, elapsed);
            }
            m_last_update_time = xTaskGetTickCount();
            return level;
        }

    private:
        TickType_t             m_last_update_time = 0;
        std::vector<EffectPtr> m_effects;
    };

} // namespace tricolor
