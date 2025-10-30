
#include "tricolor/pwm.h"

#include <Arduino.h>

void tricolor::Pwm::put(uint8_t level) {
    if (m_inverted) {
        level = 255 - level;
    }
    level = (level < m_min) ? m_min : (level > m_max) ? m_max : level;
    analogWrite(m_pin, level);
}
