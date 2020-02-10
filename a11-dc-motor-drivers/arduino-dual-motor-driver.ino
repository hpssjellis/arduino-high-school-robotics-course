/*  
 *   a11-dual-driver.ino
 *
 * Motor Drivers take complex systems of transistors 
 * making working with motors much easier.
 * 
 *
 *
 *  By Jeremy Ellis twitter @rocksetta
 *  Webpage http://rocksetta.com
 *  Arduino High School Robotics Course at
 *  https://github.com/hpssjellis/arduino-high-school-robotics-course
 * 
 *  Update Feb 9th, 2020
 * 
 * Draw your circuit diagram first
 * This program will just tell you if  the connections are working
 * See https://www.pololu.com/product/2135 for assistance
 * 
 * 
 * Note: Check your board for the PWM pins.
 * On the Nano 33 IOT the PWM pins are: D3, D5, D6, D9, D10
 * For the Nano 33 BLE not sure if all digital pins can do PWM or just the above ones.
 * The Portenta H7 has 10 PWM pins not yet sure which ones.
 * 
 */


#include <Arduino.h>  // only needed for https://platformio.org/


void setup() {
    pinMode(9, OUTPUT);            // D9 PWM pin 0 to 255
    pinMode(10, OUTPUT);           // D10 digital pin 0 to 1
    pinMode(LED_BUILTIN, OUTPUT);  // User LED

}

void loop() {
    
    digitalWrite(LED_BUILTIN, 1); // User Led on
    digitalWrite(10, 1);           // set one direction
    analogWrite(9, 50);           // go medium
    delay(1000);
    
    analogWrite(9, 0);            // stop
    delay(1000); 
   
    digitalWrite(10, 0);           // set the other direction
    analogWrite(9, 50);           // go medium   
    delay(1000);    
    
    analogWrite(9, 255);          // go full speed
    delay(1000);
    
    analogWrite(9, 0);            // stop
    
    digitalWrite(LED_BUILTIN, 0); // User LEd off
    delay(6000);                  // wait 6 seconds
        
}
