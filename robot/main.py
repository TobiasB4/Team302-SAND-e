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
posItem = 0

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

targetLat = latitudes[posItem]
targetLong = longitudes[posItem]

# TODO: calibration sequence for IMU and cardinal direction

while(calibration == 0):
    calibration = 1
# Check that IMU says robot is going in a straight line
# Record GPS points, take start and end gps points of isstraight and get cardinal direction

# -------------------------------------------------------------------------------------------------------
#
# Control loop: Generator & Output
#
# At 10 Hz:
# - set orientation (to face intended GPS heading) (within 5 degrees is ok, pass)
# - check distance between current position and intended position and set rate accoringly
# - drive for based on inputs
#
# -------------------------------------------------------------------------------------------------------

while(1):

    # GPS Position and Target Check
    latitude = gps.geo_coords().lat
    longitude = gps.geo_coords().long
    reqDistance = ac.DistBetween(latitude, longitude, targetLat, targetLong)

    if reqDistance <= 1:
        posItem += 1
        targetLat = latitudes[posItem]
        targetLong = longitudes[posItem]

    # Generator for GPS heading
    speed = 50
    vehicleHeading = gps.veh_attitude().heading # current heading, in degrees magnetic
    reqBearing = ac.CalcBearing(latitude, longitude, targetLat, targetLong) # required heading in degrees magnetic
    angleBetween = reqBearing - vehicleHeading

    # TODO: vary speed with amount of difference between reqBearing and vehicleHeading

    # Need to turn left
    if angleBetween < 0:
        leftMots = -1
        rightMots = 1
        speed = (vehicleHeading - reqBearing) / 3.6

    # Need to turn right
    elif angleBetween > 0:
        leftMots = 1
        rightMots = -1
        speed = angleBetween / 3.6

    # No need to turn
    # TODO: add angle buffer to functions above so this gets called
    else:
        leftMots = 1
        rightMots = 1

# TODO: yield values scaled into speed outputs 