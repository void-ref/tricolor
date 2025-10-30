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
        Pwm();
        Pwm(Pin pin);
        Pwm(Pin pin, uint8_t min, uint8_t max);

        Pwm& init(bool inverted);
        Pwm& set(uint8_t level);
        Pwm& set_range(uint8_t min, uint8_t max);
        Pwm& set_inverted(bool inverted);

    private:
        Pin     m_pin;
        uint8_t m_min      = 0;
        uint8_t m_max      = 255;
        bool    m_inverted = false;
        uint8_t m_level    = 0;

        void put(uint8_t level);

        void rewrite() {
            put(m_level);
        }
    };

    uint32_t uptime_ms();

} // namespace tricolor
