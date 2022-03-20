# Contains functions for calculations required in automatic control

import math
from numpy import degrees, deg2rad

# TODO: verify functionality
# Calculate desired heading
# Inputs: current lat & long, intended lat & long
# Outputs: Bearing angle in degrees magnetic (0 to 360 degrees)
def CalcBearing(currentLat, currentLong, goalLat, goalLong):    
    calc_x = math.cos(goalLat) * math.sin(goalLong - currentLong)
    calc_y = math.cos(currentLat) * math.sin(goalLat) - (math.sin(currentLat) * math.cos(goalLat) * math.cos(goalLong - currentLong))
    bearing = ((degrees(math.atan2(calc_x, calc_y)) + 360) % 360) + 15.94 #15.94 is declination in Vancouver as of March 2022
    return bearing

# TODO: verify functionality
# Calculate great-circle distance in meters between current point and goal using the Haversine formula
# Inputs: current lat & long, intended lat & long
# Outputs: distance (m)
def DistBetween(currentLat, currentLong, goalLat, goalLong):
    lat1 = deg2rad(currentLat)
    long1 = deg2rad(currentLong)
    lat2 = deg2rad(goalLat)
    long2 = deg2rad(goalLong)
    diffLat = lat2 - lat1
    diffLong = long2 - long1 
    distance = 2*math.asin(math.sqrt((math.sin(diffLat/2)**2)+((1-(math.sin(diffLat/2)**2)-(math.sin((lat1+lat2)/2)**2))*(math.sin(diffLong/2)**2))))
    distance *= 6378137 # Earth's equatorial radius in m from https://nssdc.gsfc.nasa.gov/planetary/factsheet/earthfact.html
    return distance