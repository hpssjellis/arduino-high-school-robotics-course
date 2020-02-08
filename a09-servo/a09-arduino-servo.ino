/*  
 *   a09-arduino-servo
 *
 * MUST HAVE A 6 VOLT EXTERNAL BATTERY
 * Servos run from 0 to 180 degrees
 * 
 * servo red to 6V battery positive
 * servo ground (brown or black) to 6V battery negative
 * servo ground to Photon GND
 * servo controller (orange or the other color) to Photon PWM pin A4   
 * 
 * Note For PWM pins check your boards Pinout diagram.
 * 
 *  By Jeremy Ellis twitter @rocksetta
 *  Webpage http://rocksetta.com
 *  Arduino High School Robotics Course at
 *  https://github.com/hpssjellis/arduino-high-school-robotics-course
 * 
 *  Update Feb 7th, 2020
 * 
 */

#include <Arduino.h>  // only needed for https://platformio.org/
#include <Servo.h>

Servo myServo4;

void setup() {
    myServo4.attach(A4);
    pinMode(LED_BUILTIN, OUTPUT);

}

void loop() {
    
   // myServo4.attach(A4);
    
    
    digitalWrite(LED_BUILTIN, 1);       // D7 on    
    
    myServo4.write(0);          // servo at 0 degrees minimum
    delay(2000);
    
    myServo4.write(180);        // servo at 180 degrees Maximum
    delay(2000);

    myServo4.write(90);         // servo at 90 degrees
    delay(2000);   
    
    
    for (int myLoop = 0; myLoop <= 180; myLoop++){
        myServo4.write(myLoop);
        delay(25);  // short delay 25 ms
    }


    digitalWrite(LED_BUILTIN, 0);     // D7 off
    delay(5000);            // 5 second delay
    
    
   // myServo4.detach();   // less weird stuff if you detach the servo

}


