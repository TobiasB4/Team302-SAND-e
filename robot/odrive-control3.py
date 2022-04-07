#!/usr/bin/env python3
"""
Example usage of the ODrive python library to monitor and control ODrive devices
"""

from __future__ import print_function

import odrive
from odrive.enums import *
import time
import math

# Find a connected ODrive (this will block until you connect one)
print("finding an odrive...")
my_drive1 = odrive.find_any(serial_number="205D37905753")
my_drive2 = odrive.find_any(serial_number="207934915748")
my_drive3 = odrive.find_any(serial_number="207A34705748")

# Calibrate motor and wait for it to finish
print("starting calibration drive1...")
#my_drive1.axis0.requested_state = AXIS_STATE_MOTOR_CALIBRATION
my_drive1.axis0.requested_state = AXIS_STATE_FULL_CALIBRATION_SEQUENCE
while my_drive1.axis0.current_state != AXIS_STATE_IDLE:
    time.sleep(0.1)

my_drive1.axis0.requested_state = AXIS_STATE_CLOSED_LOOP_CONTROL

my_drive1.axis0.controller.input_vel = 0

#my_drive1.axis1.requested_state = AXIS_STATE_MOTOR_CALIBRATION
my_drive1.axis1.requested_state = AXIS_STATE_FULL_CALIBRATION_SEQUENCE
while my_drive1.axis1.current_state != AXIS_STATE_IDLE:
    time.sleep(0.1)

my_drive1.axis1.requested_state = AXIS_STATE_CLOSED_LOOP_CONTROL

my_drive1.axis1.controller.input_vel = 0

print("starting calibration drive2...")
#my_drive2.axis0.requested_state = AXIS_STATE_MOTOR_CALIBRATION
my_drive2.axis0.requested_state = AXIS_STATE_FULL_CALIBRATION_SEQUENCE
while my_drive2.axis0.current_state != AXIS_STATE_IDLE:
    time.sleep(0.1)

my_drive2.axis0.requested_state = AXIS_STATE_CLOSED_LOOP_CONTROL

my_drive2.axis0.controller.input_vel = 0

#my_drive2.axis1.requested_state = AXIS_STATE_MOTOR_CALIBRATION
my_drive2.axis1.requested_state = AXIS_STATE_FULL_CALIBRATION_SEQUENCE
while my_drive2.axis1.current_state != AXIS_STATE_IDLE:
    time.sleep(0.1)

my_drive2.axis1.requested_state = AXIS_STATE_CLOSED_LOOP_CONTROL

my_drive2.axis1.controller.input_vel = 0

#my_drive3.axis0.requested_state = AXIS_STATE_MOTOR_CALIBRATION
my_drive3.axis0.requested_state = AXIS_STATE_FULL_CALIBRATION_SEQUENCE
while my_drive3.axis0.current_state != AXIS_STATE_IDLE:
    time.sleep(0.1)

my_drive3.axis0.requested_state = AXIS_STATE_CLOSED_LOOP_CONTROL

my_drive3.axis0.controller.input_vel = 0

#my_drive3.axis1.requested_state = AXIS_STATE_MOTOR_CALIBRATION
my_drive3.axis1.requested_state = AXIS_STATE_FULL_CALIBRATION_SEQUENCE
while my_drive3.axis1.current_state != AXIS_STATE_IDLE:
    time.sleep(0.1)

my_drive3.axis1.requested_state = AXIS_STATE_CLOSED_LOOP_CONTROL

my_drive3.axis1.controller.input_vel = 0


speed = 0

for i in range (7):
    my_drive1.axis0.controller.input_vel = speed
    my_drive2.axis0.controller.input_vel = speed
    my_drive3.axis0.controller.input_vel = speed
    my_drive1.axis1.controller.input_vel = -speed
    my_drive2.axis1.controller.input_vel = -speed
    my_drive3.axis1.controller.input_vel = -speed
    speed+=1
    time.sleep(1)

my_drive1.axis0.controller.input_vel = 2*speed
my_drive2.axis0.controller.input_vel = 2*speed
my_drive3.axis0.controller.input_vel = 2*speed
my_drive1.axis1.controller.input_vel = -speed
my_drive2.axis1.controller.input_vel = -speed
my_drive3.axis1.controller.input_vel = -speed
time.sleep(10)

for i in range (7):
    my_drive1.axis0.controller.input_vel = speed
    my_drive2.axis0.controller.input_vel = speed
    my_drive3.axis0.controller.input_vel = speed
    my_drive1.axis1.controller.input_vel = -speed
    my_drive2.axis1.controller.input_vel = -speed
    my_drive3.axis1.controller.input_vel = -speed
    speed-=1
    time.sleep(1)

my_drive1.axis0.controller.input_vel = 0
my_drive2.axis0.controller.input_vel = 0
my_drive3.axis0.controller.input_vel = 0
my_drive1.axis1.controller.input_vel = 0
my_drive2.axis1.controller.input_vel = 0
my_drive3.axis1.controller.input_vel = 0
