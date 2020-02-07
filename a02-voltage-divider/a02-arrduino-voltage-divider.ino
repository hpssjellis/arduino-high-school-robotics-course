/*  
 * Voltage Divider
 *
 * GND to resistor (try different resistors i used a 5 k ohm, larger resistor larger range of values)
 * resistor to both A0 and a 2 prong sensor (such as a photoresistor)
 * other side of 2 prong sensor to 3V3
 *   
 *  By Jeremy Ellis twitter @rocksetta
 *  Aarduino High School Course at
 *  https://github.com/hpssjellis/arduino-high-school-robotics-course
 * 
 *  Update Feb 7th, 2020
 * 
 */

#include <Arduino.h>  // only needed for https://platformio.org/

void setup(){  
  
  Serial.begin(9600);
  
}


void loop() {

  Serial.print("Max = 4095, Analog Read A0: ");
  Serial.println(analogRead(A0));

  delay(3000);    // wait a bit
                  
}
