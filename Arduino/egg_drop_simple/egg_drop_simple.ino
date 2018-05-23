//------------------------------------------------------------------
// egg_drop_simple.ino
//
// Egg drop for Circuit Playground Express.
//
// Author: Carter Nelson
// MIT License (https://opensource.org/licenses/MIT)
//------------------------------------------------------------------
#ifndef ARDUINO_SAMD_CIRCUITPLAYGROUND_EXPRESS
#error "This sketch only works with the Circuit Playground Express"
#endif

#include <Adafruit_CircuitPlayground.h>

#define GRAVITY          9.80665   // m/s^2
#define IMPACT_THRESHOLD     8.0   // G's

float x, y, z, mag;

//-----------------------------------------------------------------------
void pixel_fill(uint32_t c) {
  for (int p=0; p<10; p++) CircuitPlayground.setPixelColor(p, c);
}

//-----------------------------------------------------------------------
void setup() {
  CircuitPlayground.begin();
  CircuitPlayground.setAccelRange(LIS3DH_RANGE_8_G);

  pixel_fill(0xFFFFFF); // white egg :)
}

//-----------------------------------------------------------------------
void loop() {
  // get magnitude
  x = CircuitPlayground.motionX();
  y = CircuitPlayground.motionY();
  z = CircuitPlayground.motionZ();
  mag = sqrt(x*x + y*y + z*z) / GRAVITY;
  // check for impact
  if (mag > IMPACT_THRESHOLD) {
    pixel_fill(0xFFFF00); // yellow yolk :(
    while (true);
  }
}
