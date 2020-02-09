/*  
 *   a09-arduino-transistor.ino
 *
 *
 * Transistors can protect the board from higher voltages and currents 
 * while still allowing the board to control a higher power circuit.
 * 
 * Trick for connecting your board and 6V circuit to the transitor
 * First letter is opposite the 6 volt connection. P connect negative, N connect positive.
 * The middle letter tells you the board connection. If N connect ground, if P connect digital or analog output A4
 * The last letter tells you both the 6V circuit and the board connection, P for positive, N for negative
 * 
 * Example
 * P --> 6 Volt negative connection
 * N --> board GND
 * P --> 6V Positive connection and board positive from digital or analog output pin A4
 * 
 * N --> 6 volt positive connection
 * P --> board positive from digital or analog output pin A4
 * N --> 6 volt negative connection and board GND 
 * 
 * see image at https://github.com/hpssjellis/arduino-high-school-robotics-course/blob/master/a10-transistor/pnp-npn.png
 *
 *
 *
 *  By Jeremy Ellis twitter @rocksetta
 *  Webpage http://rocksetta.com
 *  Arduino High School Robotics Course at
 *  https://github.com/hpssjellis/arduino-high-school-robotics-course
 * 
 *  Update Feb 7th, 2020
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
   pinMode(3, OUTPUT);  // set D3 for PWM
   pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
    analogWrite(3, 100);   // Note: motors might hav a minimum of 100
    digitalWrite(LED_BUILTIN,1); // LED on
    delay(1000);
    
    analogWrite(3, 0);
    digitalWrite(LED_BUILTIN,0);  // LED off
    delay(1000);
    
    analogWrite(3, 255); // PWM Max  = 255 
    digitalWrite(LED_BUILTIN,1);
    delay(1000);

    
    analogWrite(3, 0);
    digitalWrite(LED_BUILTIN,0);
    delay(6000);     // longer delay

}
