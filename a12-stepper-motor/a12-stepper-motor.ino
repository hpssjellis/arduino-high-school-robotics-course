// a12-stepper-motor
// By Jeremy Ellis
// MIT license

// Connect your stepper driver and run the program
// Change the direction and see if it works.
// Then wirte your own code to control the stepper

void setup() {
   pinMode(D2, OUTPUT);  // Direction
   pinMode(D3, OUTPUT);  // Step
}

void loop() {
    digitalWrite(D2, 0);  // pick a direction
    
    digitalWrite(D3, 1);  // do a step by setting the pulse high
    delay(3);             // wait 3 ms
    
    digitalWrite(D3, 0);  // a pulse needs to come donwn so set it low.
    delay(3);             // wait 3 ms
}
