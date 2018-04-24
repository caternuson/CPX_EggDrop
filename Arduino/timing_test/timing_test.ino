//------------------------------------------------------------------
// timing_test.ino
//
// Simple timing test for writing "data" to RAM and SPI FLASH.
//
// Author: Carter Nelson
// MIT License (https://opensource.org/licenses/MIT)
//------------------------------------------------------------------
#include <SPI.h>
#include <Adafruit_SPIFlash.h>
#include <Adafruit_SPIFlash_FatFs.h>
#include <Adafruit_CircuitPlayground.h>

#define LOG_COUNT   5000  // total points to collect
#define LOG_FILE    "data.txt"

#define FLASH_TYPE     SPIFLASHTYPE_W25Q16BV  // Flash chip type.
#if defined(ARDUINO_SAMD_CIRCUITPLAYGROUND_EXPRESS)
  #define FLASH_SS       SS                    // Flash chip SS pin.
  #define FLASH_SPI_PORT SPI                   // What SPI port is Flash on?
#else
  #define FLASH_SS       SS1                    // Flash chip SS pin.
  #define FLASH_SPI_PORT SPI1                   // What SPI port is Flash on?
#endif

Adafruit_SPIFlash flash(FLASH_SS, &FLASH_SPI_PORT); // Use hardware SPI
Adafruit_W25Q16BV_FatFs fatfs(flash);

float data[LOG_COUNT];
unsigned long start_time, end_time;
float dt_RAM, dt_FLASH;

void setup() {
  Serial.begin(9600);
  while (!Serial) {};
  Serial.println("Logging...");

  // storing to RAM
  start_time = millis();
  for (int i=0; i<LOG_COUNT; i++) {
    data[i] = 0.0;
  }
  end_time = millis();
  dt_RAM = (end_time - start_time) / 1000.0;

  // storing to FLASH
  if (!flash.begin(FLASH_TYPE)) {
    Serial.println("Error, failed to initialize flash chip!");
    while(1);
  }  
  if (!fatfs.begin()) {
    Serial.println("Error, failed to mount newly formatted filesystem!");
    while(1);
  }
  File dataFile = fatfs.open(LOG_FILE, FILE_WRITE);
  if (!dataFile) {
    Serial.println("Failed to open file for writing.");
  }

  start_time = millis();
  for (int i=0; i<LOG_COUNT; i++) {
    dataFile.println(0.0, DEC);  
  }
  end_time = millis();
  dataFile.close();    
  dt_FLASH = (end_time - start_time) / 1000.0;
  Serial.println(dt_FLASH);      

  // print results
  Serial.print("Total points = "); Serial.println(LOG_COUNT);
  Serial.println("RAM");
  Serial.print("      total time = "); Serial.println(dt_RAM);
  Serial.print("       secs / pt = "); Serial.println(dt_RAM/LOG_COUNT,5);
  Serial.print("              Hz = "); Serial.println(LOG_COUNT/dt_RAM);
  Serial.println("FLASH");
  Serial.print("      total time = "); Serial.println(dt_FLASH);
  Serial.print("       secs / pt = "); Serial.println(dt_FLASH/LOG_COUNT,5);
  Serial.print("              Hz = "); Serial.println(LOG_COUNT/dt_FLASH);
}

void loop() {
  // do nothing
}
