import setup, asyncio, websockets, serial
import autocontrol as ac
from ublox_gps import UbloxGps

# Initialize GPS

port = serial.Serial('/dev/serial0', baudrate=38400, timeout=1)
gps = UbloxGps(port)

# -------------------------------------------------------------------------------------------------------
#
# Parse coordinates, init
# - Get the list of coordinates and put it into a list of latitudes and a list of longitudes
#
# -------------------------------------------------------------------------------------------------------

latitudes = []
longitudes = []

with open('base.txt','r') as f:
    for line in f:
        lines = line.replace('\n','').replace(']','').split(',')
        # Vancouver specific code:
        # if(float(lines[0]) < 48. or float(lines[0]) > 50.):
        #     continue
        # if(float(lines[1]) < -125. or -123.):
        #     continue
        latitudes.append(float(lines[0]))
        longitudes.append(float(lines[1]))

targetLat = latitudes[0]
targetLong = longitudes[0]

# -------------------------------------------------------------------------------------------------------
#
# Control loop
# At 10 Hz:
# - set orientation (to face intended GPS heading) (within 5 degrees is ok, pass)
# - check distance between current position and intended position and set rate accoringly
# - drive for based on inputs
#
# -------------------------------------------------------------------------------------------------------

# GPS Position and Target


# Generator for GPS heading

def turningSpeed():
    while 1:

        speed = 1500
        turnAngle = ac.CalcBearing()
        heading = gps.veh_attitude().heading
        latitude = gps.geo_coords().lat
        longitude = gps.geo_coords().long
    
        # Need to turn left
        if(ac.CalcBearing(latitude, longitude, targetLat, targetLong) > 0):
            leftMots = -1
            rightMots = 1

        # Need to turn right
        if(ac.CalcBearing(latitude, longitude, targetLat, targetLong) < 0):
            leftMots = 1
            rightMots = -1

        # No need to turn

