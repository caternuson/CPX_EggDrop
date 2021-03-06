# timing_test.py
#
# Simple timing test for writing "data" to RAM and SPI FLASH.
#
# Author: Carter Nelson
# MIT License (https://opensource.org/licenses/MIT)
import time
from adafruit_circuitplayground.express import cpx

# Configure the data logger
LOG_COUNT  = 1000  # total points to collect
LOG_FILE   = 'time_test.dat'

data = [None] * LOG_COUNT

print("Logging...")

# storing to RAM
start_time = time.monotonic()
for count in range(LOG_COUNT):
    data[count] = 0.0
end_time = time.monotonic()
dt_RAM = end_time - start_time

# storing to FLASH
try:
    with open("/"+LOG_FILE, "w") as f:
        start_time = time.monotonic()
        for _ in range(LOG_COUNT):
            f.write("{}\n".format(0.0))
        end_time = time.monotonic()
        dt_FLASH = end_time - start_time
except OSError as e:
    # Something happened with file access
    # Flash LED forever
    print("Error writing to file.")
    while True:
        cpx.red_led = not cpx.red_led
        time.sleep(0.1)

# print results
print("Total points = {}".format(LOG_COUNT))
print("RAM")
print("      total time = {}".format(dt_RAM))
print("       secs / pt = {}".format(dt_RAM/LOG_COUNT))
print("              Hz = {}".format(LOG_COUNT/dt_RAM))
print("FLASH")
print("      total time = {}".format(dt_FLASH))
print("       secs / pt = {}".format(dt_FLASH/LOG_COUNT))
print("              Hz = {}".format(LOG_COUNT/dt_FLASH))
