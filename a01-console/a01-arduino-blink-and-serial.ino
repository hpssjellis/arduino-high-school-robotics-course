/*  Blink and Serial
 *  Arduino test program 
 *  By Jeremy Ellis twitter @rocksetta
 *  Aarduino High School Course at
 *  https://github.com/hpssjellis/arduino-high-school-robotics-course
 * 
 *  Update Feb 7th, 2020
 * 
 */

void setup(){  
  
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  
}


void loop() {

  int sensorValue = analogRead(A0);
  Serial.print("A0 Analog Read max = 4095, Actual Value: ");
  Serial.println(sensorValue);

  // Flash LED 3 times
  digitalWrite(LED_BUILTIN, HIGH);   
  delay(100);                      
  digitalWrite(LED_BUILTIN, LOW);    
  delay(100);                    

  digitalWrite(LED_BUILTIN, HIGH);   
  delay(100);                      
  digitalWrite(LED_BUILTIN, LOW);    
  delay(100);      
                
  digitalWrite(LED_BUILTIN, HIGH);   
  delay(100);                      
  digitalWrite(LED_BUILTIN, LOW);    
  delay(3000);    // longer wait 
                  
}
