# boot.py
# Use this to control file system state on power up and/or HW reset.
# If read only is set to False, then CP can write to the file system.
# If read only is set to True, then USB can write to the file system.
import storage
from adafruit_circuitplayground.express import cpx

# toward ear = False (CP can write to file system)
# toward note = True (USB can write to file system)
read_only = cpx.switch
print("Read Only = ", read_only)
storage.remount("/", read_only)