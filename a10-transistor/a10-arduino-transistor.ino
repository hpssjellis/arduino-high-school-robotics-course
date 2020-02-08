/*  
 *   a09-arduino-transistor.ino
 *
 *
 * Transistors can protect the board from higher voltages and currents 
 * while still allowing the board to control a higher power circuit.
 * 
 * Trick for connecting your board and 6V circuit to the transitor
 * First letter is opposite the 6 volt connection. P connect negative, N connect positive.
 * The middle letter tells you the board connection. If N connect ground, if P connect digital or analog output
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

 *  By Jeremy Ellis twitter @rocksetta
 *  Webpage http://rocksetta.com
 *  Arduino High School Robotics Course at
 *  https://github.com/hpssjellis/arduino-high-school-robotics-course
 * 
 *  Update Feb 7th, 2020
 * 
 */


void setup() {
   pinMode(A4, OUTPUT);
   pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
    analogWrite(A4, 100);
    digitalWrite(LED_BUILTIN,1);
    delay(1000);
    
    analogWrite(A4, 0);
    digitalWrite(LED_BUILTIN,0);
    delay(1000);
    
    
    analogWrite(A4, 200);  // PWM Max  = 255
    digitalWrite(LED_BUILTIN,1);
    delay(2000);
    
    analogWrite(A4, 0);
    digitalWrite(LED_BUILTIN,0);
    delay(2000);

}
