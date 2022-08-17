odrivetool

odrv0.erase_configuration()
odrv0.reboot()

odrv0.axis0.encoder.config.cpr = 20480
odrv0.axis1.encoder.config.cpr = 20480

odrv0.save_configuration()
odrv0.reboot()

odrv0.axis0.motor.config.current_lim = 60
odrv0.axis0.controller.config.vel_limit = 1000
odrv0.axis1.motor.config.current_lim = 60
odrv0.axis1.controller.config.vel_limit = 1000
odrv0.config.enable_brake_resistor = 1
odrv0.config.brake_resistance = 0.5
odrv0.axis0.motor.config.torque_constant = 0.01722916667
odrv0.axis0.motor.config.motor_type = MOTOR_TYPE_HIGH_CURRENT
odrv0.axis1.motor.config.torque_constant = 0.01722916667
odrv0.axis1.motor.config.motor_type = MOTOR_TYPE_HIGH_CURRENT

odrv0.save_configuration()
odrv0.reboot()

odrv0.axis0.requested_state = AXIS_STATE_FULL_CALIBRATION_SEQUENCE
odrv0.axis1.requested_state = AXIS_STATE_FULL_CALIBRATION_SEQUENCE

odrv0.axis0.controller.config.pos_gain = 30
odrv0.axis0.controller.config.vel_gain = 0.08
odrv0.axis0.controller.config.vel_integrator_gain = 0.4
odrv0.axis1.controller.config.pos_gain = 30
odrv0.axis1.controller.config.vel_gain = 0.08
odrv0.axis1.controller.config.vel_integrator_gain = 0.4

odrv0.axis0.requested_state = AXIS_STATE_CLOSED_LOOP_CONTROL
odrv0.axis1.requested_state = AXIS_STATE_CLOSED_LOOP_CONTROL

odrv0.axis0.requested_state =  AXIS_STATE_IDLE
odrv0.axis1.requested_state =  AXIS_STATE_IDLE

dump_errors(odrv0)
odrv0.clear_errors()
odrv0.axis0.encoder.shadow_count
odrv0.axis1.encoder.shadow_count

odrv0.axis0.controller.config.control_mode = CONTROL_MODE_VELOCITY_CONTROL
odrv0.axis1.controller.config.control_mode = CONTROL_MODE_VELOCITY_CONTROL


odrv0.axis0.controller.input_vel = 2
odrv0.axis1.controller.input_vel = -2

odrv0.axis0.controller.input_vel = 0
odrv0.axis1.controller.input_vel = 0


odrv0.axis0.encoder.config.use_index = 1
odrv0.axis1.encoder.config.use_index = 1 

odrv0.axis0.requested_state=AXIS_STATE_ENCODER_INDEX_SEARCH
odrv0.axis1.requested_state=AXIS_STATE_ENCODER_INDEX_SEARCH

odrv0.axis0.requested_state = AXIS_STATE_ENCODER_OFFSET_CALIBRATION
odrv0.axis1.requested_state = AXIS_STATE_ENCODER_OFFSET_CALIBRATION
odrv0.axis0.error
odrv0.axis0.encoder.config.phase_offset
odrv0.axis1.error
odrv0.axis1.encoder.config.phase_offset

odrv0.axis0.encoder.config.pre_calibrated = 1
odrv0.axis1.encoder.config.pre_calibrated = 1

odrv0.axis0.config.startup_encoder_index_search = 1
odrv0.axis1.config.startup_encoder_index_search = 1

odrv0.save_configuration()
odrv0.reboot()

odrv0.axis0.controller.config.input_mode = INPUT_MODE_POS_FILTER
odrv0.axis0.controller.config.input_mode = INPUT_MODE_VEL_RAMP

odrv0.config.gpio4_mode = GPIO_MODE_PWM
odrv0.config.gpio4_pwm_mapping.min = -100
odrv0.config.gpio4_pwm_mapping.max = 100
odrv0.config.gpio4_pwm_mapping.endpoint = odrv0.axis0.controller._input_vel_property
odrv0.config.gpio4_pwm_mapping.endpoint = odrv0.axis1.controller._input_vel_property

odrv0.axis0.controller.config.circular_setpoints = True
odrv0.axis1.controller.config.circular_setpoints = True
odrv0.axis0.controller.config.control_mode = CONTROL_MODE_VELOCITY_CONTROL
odrv0.axis0.controller.config.vel_ramp_rate = 1

odrv0.axis0.controller.config.input_mode = INPUT_MODE_VEL_RAMP

odrv0.axis0.controller.config.input_mode = INPUT_MODE_POS_FILTER

odrv0.config.gpio4_pwm_mapping.endpoint = odrv0.axis0.controller._vel_setpoint_property

odrv0.save_configuration()
odrv0.reboot()

odrv0.axis0.controller.input_pos = 1

odrv0.axis0.controller.config.input_mode = INPUT_MODE_POS_FILTER

axis.controller.config.input_mode = INPUT_MODE_POS_FILTER
