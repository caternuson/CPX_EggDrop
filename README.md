# Circuit Playground Express Egg Drop
Egg drop code for Adafruit Circuit Playground Express

**Max Data Rate Summary (Hz)**
| LANG | RAM | FLASH |
|:----:|:---:|:-----:|
|  CP  | 110 |   40  |
| Ardu | 244 |  102  |

## CircuitPython
### Info
* https://learn.adafruit.com/cpu-temperature-logging-with-circuit-python/writing-to-the-filesystem
* https://learn.adafruit.com/adafruit-trinket-m0-circuitpython-arduino/circuitpython-storage

### Timing Test
Results from writing zeros (`timing_test.py`):
```
Total points = 1000
RAM
      total time = 0.196991
       secs / pt = 0.000196991
              Hz = 5076.38
FLASH
      total time = 4.755
       secs / pt = 0.004755
              Hz = 210.305
```
Results from reading and writing all 3 accelo axes (`timing_test_accelo.py`):
```
Total points = 200
RAM
      total time = 1.822
       secs / pt = 0.00910999
              Hz = 109.77
FLASH
      total time = 5.032
       secs / pt = 0.02516
              Hz = 39.7456
```

## Ardunio
### Info
* https://learn.adafruit.com/adafruit-feather-m0-express-designed-for-circuit-python-circuitpython/using-spi-flash

### Timing Test
Results from writing zeros (`timing_test.ino`):
```
Total points = 5000
RAM
      total time = 0.00
       secs / pt = 0.00000
              Hz = 5000000.00
FLASH
      total time = 23.52
       secs / pt = 0.00470
              Hz = 212.60
```
Results from reading and writing all 3 accelo axes (`timing_test_accelo.ino`):
```
Total points = 1000
RAM
      total time = 4.09
       secs / pt = 0.00409
              Hz = 244.26
FLASH
      total time = 9.79
       secs / pt = 0.00979
              Hz = 102.15
```