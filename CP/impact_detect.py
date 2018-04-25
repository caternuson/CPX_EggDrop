# impact_detect.py
#
# Detect impact via simple threshold check.
#
# Author: Carter Nelson
# MIT License (https://opensource.org/licenses/MIT)
import math
import time
from adafruit_circuitplayground.express import cpx

GRAVITY = 9.80665       # m/s^2
IMPACT_THRESHOLD = 2.0  # G's

cpx.pixels.fill(0xFF0000)

while not cpx.button_a:
    pass

cpx.pixels.fill(0x00FF00)    

falling = True
while falling:
    x, y, z = cpx.acceleration
    mag = math.sqrt(x*x + y*y + z*z) / GRAVITY
    if mag > IMPACT_THRESHOLD:
        falling = False

cpx.pixels.fill(0x0000FF)