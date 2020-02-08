/*  
 *  A04-arduino-SOS.ino
 *   
 *  Make your Arduino flash S-O-S
 *  3 short flashes, 3 long flashes, 3 short flashes
 * 
 *  Update Feb 7th, 2020
 *   
 *  By Jeremy Ellis twitter @rocksetta
 *  Webpage http://rocksetta.com
 *  Arduino High School Robotics Course at
 *  https://github.com/hpssjellis/arduino-high-school-robotics-course
 * 
 *  Update Feb 7th, 2020
 * 
 *  Note: I use LOW = 0, HIGH = 1 so that it is easier for students to move to
 *  analogRead(A0) range 0-4095
 *  analogwrite(A0) range 0-255
 */

#include <Arduino.h>  // only needed for https://platformio.org/


void setup() {
  pinMode(LED_BUILTIN, OUTPUT);  
}

void loop() {
  
  digitalWrite(LED_BUILTIN, 1);   // LED on
  delay(200);                     // wait 
  digitalWrite(LED_BUILTIN, 0);   // LED off
  delay(200); 

      
  digitalWrite(LED_BUILTIN, 1);   
  delay(200);                      
  digitalWrite(LED_BUILTIN, 0);
  delay(200); 
  
  // You put code here to finish the SOS signal
  
  delay(3000);    // longer wait 
   
}
