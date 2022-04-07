// includes
#include <Arduino.h>
#include <stdio.h>
#include <HardwareSerial.h>
#include <SoftwareSerial.h>
#include "ODriveArduino.h"
#include "ODriveEnums.h"
// Printing with stream operator helper functions
template<class T> inline Print& operator <<(Print &obj,     T arg) { obj.print(arg);    return obj; }
template<>        inline Print& operator <<(Print &obj, float arg) { obj.print(arg, 4); return obj; }

int teensy_led = 13; // Output pin teensy led
////////////////////////////////
// Set up serial pins to the ODrive
////////////////////////////////

// Teensy 4.0: 
// Serial1
// pin 0: RX - connect to ODrive0 TX
// pin 1: TX - connect to ODrive0 RX
// Serial2
// pin 7: RX - connect to ODrive1 TX
// pin 8: TX - connect to ODrive1 RX
// Serial3
// pin 15: RX - connect to ODrive2 TX
// pin 14: TX - connect to ODrive2 RX

//HardwareSerial& odrive_serial = Serial1;

// ODrive object
//ODriveArduino odrive(odrive_serial);

ODriveArduino odrive1(Serial1);
ODriveArduino odrive2(Serial2);
ODriveArduino odrive3(Serial3);

void setup() {
  // ODrive uses 115200 baud
  Serial1.begin(115200);
  Serial2.begin(115200);
  Serial3.begin(115200);
  // Serial to PC
  Serial.begin(115200);

  Serial.println("ODriveArduino");
  Serial.println("Setting parameters...");
  pinMode(13,OUTPUT);
   
  for (int axis = 0; axis < 2; ++axis) {
    // Serial1
    // Encoder configuration
    Serial1 << "w axis" << axis << ".motor.encoder.config.cpr " << 20480 << '\n';
    // Motor limit configurations
    Serial1 << "w axis" << axis << ".motor.config.current_lim " << 60 << '\n';
    Serial1 << "w axis" << axis << ".controller.config.vel_limit " << 1000 << '\n';
    Serial1 << "w axis" << axis << ".motor.config.enable_brake_resistor " << 1 << '\n';
    Serial1 << "w axis" << axis << ".motor.config.brake_resistance " << 0.5f << '\n';
    Serial1 << "w axis" << axis << ".motor.config.torque_constant " << 0.01722916667f << '\n';
    Serial1 << "w axis" << axis << ".motor.config.motor_type " << MOTOR_TYPE_HIGH_CURRENT << '\n';
    // Motor controller tuning
    Serial1 << "w axis" << axis << ".motor.config.vel_gain " << 0.08f << '\n';
    Serial1 << "w axis" << axis << ".motor.config.pos_gain " << 30.0f << '\n';
    Serial1 << "w axis" << axis << ".motor.config.vel_integrator_gain " << 0.4f << '\n';
    // Configure PWM input mapping 
    Serial1 << ".config.gpio4_mode " << GPIO_MODE_PWM << '\n';
    Serial1 << ".config.gpio4_pwm_mapping.min " << -100 << '\n';
    Serial1 << ".config.gpio4_pwm_mapping.max " << 100 << '\n';
    Serial1 << ".config.gpio4_pwm_mapping.endpoint " << Serial1 << "w axis" << axis << ".controller._input_vel_property " << '\n';

    // Serial2
    // Encoder configuration
    Serial2 << "w axis" << axis << ".motor.encoder.config.cpr " << 20480 << '\n';
    // Motor limit configurations
    Serial2 << "w axis" << axis << ".motor.config.current_lim " << 60 << '\n';
    Serial2 << "w axis" << axis << ".controller.config.vel_limit " << 1000 << '\n';
    Serial2 << "w axis" << axis << ".motor.config.enable_brake_resistor " << 1 << '\n';
    Serial2 << "w axis" << axis << ".motor.config.brake_resistance " << 0.5f << '\n';
    Serial2 << "w axis" << axis << ".motor.config.torque_constant " << 0.01722916667f << '\n';
    Serial2 << "w axis" << axis << ".motor.config.motor_type " << MOTOR_TYPE_HIGH_CURRENT << '\n';
    // Motor controller tuning
    Serial2 << "w axis" << axis << ".motor.config.vel_gain " << 0.08f << '\n';
    Serial2 << "w axis" << axis << ".motor.config.pos_gain " << 30.0f << '\n';
    Serial2 << "w axis" << axis << ".motor.config.vel_integrator_gain " << 0.4f << '\n';
    // Configure PWM input mapping 
    Serial2 << ".config.gpio4_mode " << GPIO_MODE_PWM << '\n';
    Serial2 << ".config.gpio4_pwm_mapping.min " << -100 << '\n';
    Serial2 << ".config.gpio4_pwm_mapping.max " << 100 << '\n';
    Serial2 << ".config.gpio4_pwm_mapping.endpoint " << Serial2 << "w axis" << axis << ".controller._input_vel_property " << '\n';
  
    // Serial3
    // Encoder configuration
    Serial3 << "w axis" << axis << ".motor.encoder.config.cpr " << 20480 << '\n';
    // Motor limit configurations
    Serial3 << "w axis" << axis << ".motor.config.current_lim " << 60 << '\n';
    Serial3 << "w axis" << axis << ".controller.config.vel_limit " << 1000 << '\n';
    Serial3 << "w axis" << axis << ".motor.config.enable_brake_resistor " << 1 << '\n';
    Serial3 << "w axis" << axis << ".motor.config.brake_resistance " << 0.5f << '\n';
    Serial3 << "w axis" << axis << ".motor.config.torque_constant " << 0.01722916667f << '\n';
    Serial3 << "w axis" << axis << ".motor.config.motor_type " << MOTOR_TYPE_HIGH_CURRENT << '\n';
    // Motor controller tuning
    Serial3 << "w axis" << axis << ".motor.config.vel_gain " << 0.08f << '\n';
    Serial3 << "w axis" << axis << ".motor.config.pos_gain " << 30.0f << '\n';
    Serial3 << "w axis" << axis << ".motor.config.vel_integrator_gain " << 0.4f << '\n';
    // Configure PWM input mapping 
    Serial3 << ".config.gpio4_mode " << GPIO_MODE_PWM << '\n';
    Serial3 << ".config.gpio4_pwm_mapping.min " << -100 << '\n';
    Serial3 << ".config.gpio4_pwm_mapping.max " << 100 << '\n';
    Serial3 << ".config.gpio4_pwm_mapping.endpoint " << Serial3 << "w axis" << axis << ".controller._input_vel_property " << '\n';
  }
}

void loop() {
  digitalWrite(13,LOW);
  delay(500);
  digitalWrite(13,HIGH);
  delay(500);
  digitalWrite(13,LOW);
  delay(500);
  digitalWrite(13,HIGH);
  delay(500);
  
  // Run calibration sequence
  for (int c = 0; c < 2; ++c) {
    int motornum = c-'0';
    int requested_state;
    
    requested_state = AXIS_STATE_MOTOR_CALIBRATION;
    Serial << "Axis" << c << ": Requesting state " << requested_state << '\n';
    odrive1.run_state(motornum, requested_state, true);
    if(!odrive1.run_state(motornum, requested_state, true)){
      Serial.println("Failed Motor Calibration OD1");
      return;
    }
    requested_state = AXIS_STATE_CLOSED_LOOP_CONTROL;
    Serial << "Axis" << c << ": Requesting state " << requested_state << '\n';
    odrive1.run_state(motornum, requested_state, false /*don't wait*/);
    if(!odrive1.run_state(motornum, requested_state, false /*don't wait*/)) {
      Serial.println("Failed Closed Loop Control OD1");
      return;
    }
    
    requested_state = AXIS_STATE_MOTOR_CALIBRATION;
    Serial << "Axis" << c << ": Requesting state " << requested_state << '\n';
    odrive2.run_state(motornum, requested_state, true);
    if(!odrive2.run_state(motornum, requested_state, true)){
      Serial.println("Failed Motor Calibration OD2");
      return;
    }
    requested_state = AXIS_STATE_CLOSED_LOOP_CONTROL;
    Serial << "Axis" << c << ": Requesting state " << requested_state << '\n';
    odrive2.run_state(motornum, requested_state, false /*don't wait*/);
    if(!odrive2.run_state(motornum, requested_state, false /*don't wait*/)) {
      Serial.println("Failed Closed Loop Control OD2");
      return;
    }
    
    requested_state = AXIS_STATE_MOTOR_CALIBRATION;
    Serial << "Axis" << c << ": Requesting state " << requested_state << '\n';
    odrive3.run_state(motornum, requested_state, true);
    if(!odrive3.run_state(motornum, requested_state, true)){
      Serial.println("Failed Motor Calibration OD3");
      return;
    }
    requested_state = AXIS_STATE_CLOSED_LOOP_CONTROL;
    Serial << "Axis" << c << ": Requesting state " << requested_state << '\n';
    odrive1.run_state(motornum, requested_state, false /*don't wait*/);
    if(!odrive1.run_state(motornum, requested_state, false /*don't wait*/)) {
      Serial.println("Failed Closed Loop Control OD3");
      return;
    }
  }
  // Read bus voltage
    Serial1 << "r vbus_voltage\n";
    Serial << "Vbus voltage 1: " << odrive1.readFloat() << '\n';

    Serial2 << "r vbus_voltage\n";
    Serial << "Vbus voltage 2: " << odrive2.readFloat() << '\n';

    Serial3 << "r vbus_voltage\n";
    Serial << "Vbus voltage 3: " << odrive3.readFloat() << '\n';
    
  // Sinusoidal test move
    Serial.println("Executing sinusoidal test move, velocity");
    for (float ph = 0.0f; ph < 6.28318530718f; ph += 0.01f) {
      float vel_m0 = 3.0f * cos(ph);
      float vel_m1 = 2.0f * sin(ph);
      odrive1.SetVelocity(0, vel_m0);
      odrive1.SetVelocity(1, vel_m1);
      odrive2.SetVelocity(0, vel_m0);
      odrive2.SetVelocity(1, vel_m1);
      odrive3.SetVelocity(0, vel_m0);
      odrive3.SetVelocity(1, vel_m1);
      delay(5);
      Serial.println(vel_m0);
      Serial.println(vel_m1);
    }
}
