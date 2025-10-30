# Tri-Color LED Control Library

Ergonomic library for controlling four-pin (R, G, B, GND) tri-color LEDs.

## Example

This example sets up an LED with a "breathing" effect to repeat every 4 seconds.

```cpp
#include <Arduino.h>

#include "tricolor/led.h"

using namespace tricolor;

#define RED_PIN   22
#define GREEN_PIN 16
#define BLUE_PIN  17

Tricolor LED(RED_PIN, GREEN_PIN, BLUE_PIN);

void setup() {
    LED.set_active_low(true); // depends on wiring
    LED.effects()
        .solid(Color::ORCHID) // 1. Begin with solid color
        .breathe(4000)        // 2. Modulate with breathe effect
        .max_level(150);      // 3. Limit overall brightness
}

void loop() {
    LED.update();
    delay(5);
}
```
