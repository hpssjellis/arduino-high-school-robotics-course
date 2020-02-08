
/* 
 * DAC to ADC
 * Digital to Analog Converter (DAC) and  Analog to Digital Converter (ADC)
 * DAC converts a digital signal into analog signal.
 * ADC converts an Analog signal into a digital signal
 *
 * Connect Pin A0 (DAC0) to A1
 * Connect Pin A0 (DAC0) to Pin 3 (D3)
 *   
 *
 *  Update Feb 7th, 2020
 *
 *  analogWriteResolution(10) assumed default for DAC 0 - 1023 --> 0 to 3.3 Volts
 *  
 *  By Jeremy Ellis twitter @rocksetta
 *  Webpage http://rocksetta.com
 *  Arduino High School Robotics Course at
 *  https://github.com/hpssjellis/arduino-high-school-robotics-course
 *  
 */


#include <Arduino.h>  // only needed for https://platformio.org/

void setup() {
  analogWriteResolution(10);  
  Serial.begin(9600);
  pinMode(DAC0, OUTPUT);
  pinMode(3, INPUT_PULLDOWN);
  // pinMode(A1, INPUT); You don't have to declare A1 for Analog input, that is the default

}

void loop() {
  myDac(0);
  myDac(800); 
  int myRandomNumber  = rand() % 1023;
 // int myRandomNumber  = rand() % 50+380;
  myDac(myRandomNumber);
  Serial.println("----------------------");
  delay(6000); // wait a few seconds

}

void myDac(int myDacSet){
  
  analogWrite(DAC0, myDacSet);
  Serial.print("DAC0 set to: ");
  Serial.print(myDacSet);

  Serial.print(", A1: ");
  Serial.print(analogRead(A1));

  Serial.print(", Pin(D3): ");
  Serial.println(digitalRead(3));
  
}
