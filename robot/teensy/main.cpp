#include <Arduino.h>
#include <stdio.h>
#include "PWM.h"

int rx_steer = 23; // Receiver input pin steer 
int rx_throttle = 22; // Receiver input pin throttle 

int pwm_steer = 24; // PWM output pin steer
int pwm_throttle = 25; // PWM output pin throttle

int teensy_led = 13; // Output pin teensy led

PWM ch1(rx_steer); // PWM class steer
PWM ch2(rx_throttle); // PWM class throttle

void setup() {
  Serial.begin(115200); // Serial debugger 
  analogWriteResolution(11); // analogWrite value 0 to 2048, or 2048 for high
  ch1.begin(true); // ch1, PWM HIGH
  ch2.begin(true); // ch2, PWM HIGH 
  pinMode(teensy_led, OUTPUT);
}

void loop() {
  Serial.print(ch1.getValue()); // Print PWM inputs on serial monitor
  Serial.print("\t");
  Serial.println();
  delay(10);

  digitalWrite(pwm_steer, HIGH);  // PWM output  
  delayMicroseconds(ch1.getValue());
  digitalWrite(pwm_steer, LOW);
  delayMicroseconds(20000-ch1.getValue());

  digitalWrite(teensy_led, HIGH);  // LED go blink blink
  delay(100);
  digitalWrite(teensy_led, LOW);
  delay(100);
}