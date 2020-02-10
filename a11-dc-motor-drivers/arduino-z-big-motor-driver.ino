/*  
 *   arduino-z-big-motor-driver.ino
 *
 * Motor Drivers take complex systems of transistors 
 * making working with DC motors much easier.
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
 * See https://www.pololu.com/product/1451 for assistance
 * 
 * 
 * Note: Check your board for the PWM pins.
 * On the Nano 33 IOT the PWM pins are: D3, D5, D6, D9, D10
 * For the Nano 33 BLE not sure if all digital pins can do PWM or just the above ones.
 * The Portenta H7 has 10 PWM pins not yet sure which ones.
 * 
 * 
 * 
 * Note: The Big motor driver is a bit confusing since
 * it has a left and a right pin
 * For some motors if both pins are set it puts on a break
 * If neither pin is set it coasts, runs freely.
 * Does not work for all motors
 * 
 */


#include <Arduino.h>  // only needed for https://platformio.org/


void setup() {
    pinMode(2, OUTPUT);            // D4 digital pin 0 to 1, Left for digitalWrite
    pinMode(3, OUTPUT);            // D3 PWM pin 0 to 255    PWM  for analogWrite
    pinMode(4, OUTPUT);            // D5 digital pin 0 to 1, Right for digitalWrite
    pinMode(LED_BUILTIN, OUTPUT);  // User LED

}


void loop() {
    
    digitalWrite(LED_BUILTIN, 1);    // D7 on
    
    digitalWrite(2, 1);              // set one direction
    digitalWrite(4, 0);              // set other direction 
    
    analogWrite(3, 50);              // go medium
    delay(1000);
    
    analogWrite(3, 0);               // stop
    delay(1000); 
   
    digitalWrite(2, 0);    
    digitalWrite(4, 1);   
    
    analogWrite(3, 50);   
    delay(1000);    
    
    analogWrite(3, 255);            // go full speed
    delay(1000);
    
    analogWrite(3, 0);              // stop
    digitalWrite(LED_BUILTIN, 0);   // D7 off
    delay(6000);                    // wait 6 seconds
        
}
