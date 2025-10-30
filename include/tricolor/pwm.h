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

#include <cstdint>

namespace tricolor {

    using Pin = uint8_t;

    class Pwm {
    public:
        Pwm() : Pwm(0) {}

        Pwm(Pin pin) : Pwm(pin, 0, 255) {}

        Pwm(Pin pin, uint8_t min, uint8_t max) : m_pin(pin), m_min(min), m_max(max) {}

        Pwm& init(bool inverted) {
            pinMode(m_pin, OUTPUT);
            return *this;
        }

        Pwm& set(uint8_t level) {
            m_level = level;
            put(level);
            return *this;
        }

        Pwm& set_range(uint8_t min, uint8_t max) {
            m_min = (min < max) ? min : max;
            m_max = (max < min) ? min : max;
            rewrite();
            return *this;
        }

        Pwm& set_inverted(bool inverted) {
            m_inverted = inverted;
            rewrite();
            return *this;
        }

    private:
        Pin     m_pin;
        uint8_t m_min      = 0;
        uint8_t m_max      = 255;
        bool    m_inverted = false;
        uint8_t m_level    = 0;

        void rewrite() {
            put(m_level);
        }

        void put(uint8_t level) {
            if (m_inverted) {
                level = 255 - level;
            }
            level = (level < m_min) ? m_min : (level > m_max) ? m_max : level;
            analogWrite(m_pin, level);
        }
    };

} // namespace tricolor
