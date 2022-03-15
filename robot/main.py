import setup, asyncio, websockets, serial
import autocontrol as ac
from ublox_gps import UbloxGps

# Control loop
# Every 1 Hz:
# - set orientation (to face intended GPS heading) (within 5 degrees is ok, pass)
# - check distance between current position and intended position and set rate accoringly
# - drive for 1 second blind

