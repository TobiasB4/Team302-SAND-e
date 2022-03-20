# https://qwiic-ublox-gps-py.readthedocs.io/en/latest/ex3.html

import serial
from ublox_gps import UbloxGps

port = serial.Serial('/dev/serial0', baudrate=38400, timeout=1)
gps = UbloxGps(port)

def run():

    try:
        print("Listening for UBX Messages")
        while True:
            try:
                veh = gps.veh_attitude()
                print("Roll: ", veh.roll)
                print("Pitch: ", veh.pitch)
                print("Heading: ", veh.heading)
                print("Roll Acceleration: ", veh.accRoll)
                print("Pitch Acceleration: ", veh.accPitch)
                print("Heading Acceleration: ", veh.accHeading)
                coords = gps.geo_coords()
                print(coords.lon, coords.lat)
            except (ValueError, IOError) as err:
                print(err)

    finally:
        port.close()


if __name__ == '__main__':
    run()