//------------------------------------------------------------------
// egg_drop.ino
//
// Egg drop accelerometer data logger for Circuit Playground Express.
//
// Author: Carter Nelson
// MIT License (https://opensource.org/licenses/MIT)
//------------------------------------------------------------------
#ifndef ARDUINO_SAMD_CIRCUITPLAYGROUND_EXPRESS
#error "This sketch only works with the Circuit Playground Express"
#endif

#include <SPI.h>
#include <Adafruit_SPIFlash.h>
#include <Adafruit_SPIFlash_FatFs.h>
#include <Adafruit_CircuitPlayground.h>

#define GRAVITY          9.80665   // m/s^2
#define IMPACT_THRESHOLD     3.0   // G's
#define FREEFALL_THRESHOLD   0.1   // G's
#define XTRA_POINTS          200   // post-impact points
#define LOG_FILE   "egg_drop.dat"

#define FLASH_TYPE     SPIFLASHTYPE_W25Q16BV  // Flash chip type.
#define FLASH_SS       SS                    // Flash chip SS pin.
#define FLASH_SPI_PORT SPI                   // What SPI port is Flash on?

Adafruit_SPIFlash flash(FLASH_SS, &FLASH_SPI_PORT);
Adafruit_W25Q16BV_FatFs fatfs(flash);

unsigned long start_time;
float x, y, z, mag;
boolean free_fall = false;
File file;

//-----------------------------------------------------------------------
void pixel_fill(uint32_t c) {
  for (int p=0; p<10; p++) CircuitPlayground.setPixelColor(p, c);
}

//-----------------------------------------------------------------------
File open_file() {
  if (!flash.begin(FLASH_TYPE)) {
    return NULL;
  }  
  if (!fatfs.begin()) {
    return NULL;    
  }
  return fatfs.open(LOG_FILE, FILE_WRITE);
}

//-----------------------------------------------------------------------
void setup() {
  CircuitPlayground.begin();
  CircuitPlayground.setAccelRange(LIS3DH_RANGE_8_G);

  pixel_fill(0x00FFFF);

  // wait for button press
  while (!CircuitPlayground.leftButton() && !CircuitPlayground.rightButton()) {};

  // open file
  file = open_file();

  if (file == NULL) {
    while (true) {
      CircuitPlayground.redLED(0);
      delay(100);
      CircuitPlayground.redLED(1);      
      delay(100);      
    }
  }
    
  pixel_fill(0xFF0000);

  /// wait for free fall
  while (!free_fall) {
    x = CircuitPlayground.motionX();
    y = CircuitPlayground.motionY();
    z = CircuitPlayground.motionZ();
    mag = sqrt(x*x + y*y + z*z) / GRAVITY;
    if (mag < FREEFALL_THRESHOLD) free_fall = true;
  }

  pixel_fill(0x00FF00);

  // log free fall
  start_time = millis();
  while (free_fall) {
    x = CircuitPlayground.motionX();
    y = CircuitPlayground.motionY();
    z = CircuitPlayground.motionZ();
    file.print(millis()-start_time); file.print(", ");    
    file.print(x); file.print(", ");
    file.print(y); file.print(", ");
    file.print(z); file.println("");
    mag = sqrt(x*x + y*y + z*z) / GRAVITY;
    if (mag > IMPACT_THRESHOLD) free_fall = false;
  }
  // log extra points after impact
  for (int i=0; i<XTRA_POINTS; i++) {
    x = CircuitPlayground.motionX();
    y = CircuitPlayground.motionY();
    z = CircuitPlayground.motionZ();
    file.print(millis()-start_time); file.print(", ");    
    file.print(x); file.print(", ");
    file.print(y); file.print(", ");
    file.print(z); file.println("");
  }
  file.close();

  pixel_fill(0xFF00FF);
}

//-----------------------------------------------------------------------
void loop() {
  // do nothing
}
