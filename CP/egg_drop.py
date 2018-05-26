# egg_drop.py
#
# Egg drop accelerometer data logger for Circuit Playground Express.
#
# Author: Carter Nelson
# MIT License (https://opensource.org/licenses/MIT)
import math
import time
from adafruit_circuitplayground.express import cpx

GRAVITY = 9.80665           # m/s^2
IMPACT_THRESHOLD = 3.0      # G's
FREEFALL_THRESHOLD = 0.1    # G's
XTRA_POINTS = 100           # post-impact points
LOG_FILE = "egg_drop.dat"

cpx.pixels.fill(0x00FFFF)

while not cpx.button_a and not cpx.button_b:
    pass

cpx.pixels.fill(0xFF0000)

free_fall = False
while not free_fall:
    x, y, z = cpx.acceleration
    mag = math.sqrt(x*x + y*y + z*z) / GRAVITY
    if mag < FREEFALL_THRESHOLD:
        free_fall = True

cpx.pixels.fill(0x00FF00)

outstr = ""
logpoints = 0
BUFFER_SIZE = 25

try:
    with open("/"+LOG_FILE, "w") as f:
        start = time.monotonic()
        while free_fall:
            x, y, z = cpx.acceleration
            #f.write("{}, {}, {}, {}\n".format(time.monotonic()-start, x, y, z))
            logpoints += 1
            outstr += "%F, %0.2F, %0.2F, %0.2F\n" % (time.monotonic()-start, x, y, z)
            if logpoints > BUFFER_SIZE:
                cpx.red_led = True
                f.write(outstr+"\n")
                f.flush()
                outstr = ""
                logpoints = 0
                cpx.red_led = False
            mag = math.sqrt(x*x + y*y + z*z) / GRAVITY
            if mag > IMPACT_THRESHOLD:
                free_fall = False
        if logpoints < BUFFER_SIZE:
                cpx.red_led = True
                f.write(outstr+"\n")
                f.flush()
                cpx.red_led = False
        outstr = ""
        logpoints = 0
        cpx.pixels.fill(0xFFFF00)
        for _ in range(XTRA_POINTS):
            x, y, z = cpx.acceleration
            logpoints += 1
            outstr += "%F, %0.2F, %0.2F, %0.2F\n" % (time.monotonic()-start, x, y, z)
            if logpoints > BUFFER_SIZE:
                cpx.red_led = True
                f.write(outstr+"\n")
                f.flush()
                outstr = ""
                logpoints = 0
                cpx.red_led = False
            #f.write("{}, {}, {}, {}\n".format(time.monotonic()-start, *cpx.acceleration))
except OSError as e:
    # Something happened with file access
    # Flash LED forever
    print("Error writing to file.")
    while True:
        cpx.pixels.fill(0)
        cpx.red_led = not cpx.red_led
        time.sleep(0.1)

cpx.pixels.fill(0xFF00FF)
