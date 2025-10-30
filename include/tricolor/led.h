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

#include "color.h"
#include "effect.h"
#include "pwm.h"

namespace tricolor {

    class Tricolor: public Colorable {
    public:
        Tricolor(Pin red, Pin green, Pin blue, bool active_low = false) :
            m_pwms {red, green, blue} {
            set_active_low(active_low);
        }

        Tricolor(Pin pins[3]) : Tricolor(pins[0], pins[1], pins[2]) {}

        virtual void set_color(Color color) override {
            m_pwms[0].set(color.r);
            m_pwms[1].set(color.g);
            m_pwms[2].set(color.b);
        }

        void set_active_low(bool active_low) {
            set_active_low(active_low, active_low, active_low);
        }

        void set_active_low(bool red, bool green, bool blue) {
            m_pwms[0].set_inverted(red);
            m_pwms[1].set_inverted(green);
            m_pwms[2].set_inverted(blue);
        }

        EffectChain& effects() {
            return m_effects;
        }

        void reset_effects() {
            m_effects.reset();
        }

        void clear_effects() {
            m_effects.clear();
        }

        void update() {
            // first call to update() is skipped to generate an
            // accurate `elapsed` estimate
            if (m_last_update != 0) {
                Color c = m_effects.step(xTaskGetTickCount() - m_last_update);
                set_color(c);
            }
            m_last_update = xTaskGetTickCount();
        }

    private:
        Pwm m_pwms[3];

        EffectChain m_effects;
        TickType_t  m_last_update = 0;
    };

} // namespace tricolor
