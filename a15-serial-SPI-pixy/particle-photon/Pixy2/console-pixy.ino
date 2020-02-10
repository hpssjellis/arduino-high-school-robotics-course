// a15-serial-SPI-pixy.ino
// By Jeremy Ellis
// MIT License



int wow = 2;   // just seems to need an integer

#include "Pixy2.h"
#include "TPixy2.h"

// SPI pins on the photon
// See connection images on github at 
//   https://github.com/hpssjellis/particle.io-photon-high-school-robotics/tree/master/a15-serial-SPI


// VIN
// GND
// MOSI A5
// MISO A4
// SCK A3


Pixy2 pixy;                          // Create our pixy object

// Setup - Runs Once @ Startup
void setup() {   


    RGB.brightness(1);    // 1=very low light, 255 = max


    pixy.init();                    // Initalize the pixy object
}

// Loop - Runs over and over
void loop(){ 



   // uint16_t    blocks;                       // Create an unsigned int to hold the number of found blocks
    char        buf[50];                      // Create a buffer for printing over serial
    int         myPixyInt;

    pixy.ccc.getBlocks();     // Do the pixy stuff. Grab the numbers of blocks the pixy finds

  // If we have some blocks increment the frame counter (i) and if enough frames have passed print out data about the found blocks to the serial port
  if (pixy.ccc.numBlocks) {


    myPixyInt = pixy.ccc.blocks[0].m_x;    // x location of the main object    0 - 320

   // myPixyInt = pixy.blocks[0].y;
   // myPixyInt = pixy.blocks[0].width;
   // myPixyInt = pixy.blocks[0].height;




   if (myPixyInt <= 10) {    //object really far left

             Particle.publish("Pixy", "Object  far left", 60, PRIVATE);  
    }  


    if (myPixyInt > 10 && myPixyInt <= 100) {    // Object on the far left, blink really fast

        Particle.publish("Pixy", "Object on left", 60, PRIVATE);  
    }  


    if (myPixyInt > 100 && myPixyInt <= 200) {    // Object on near middle, blink slow

        Particle.publish("Pixy", "Object In the middle", 60, PRIVATE);  
    }  


    if (myPixyInt > 200 && myPixyInt <= 300) {    // Object on Right, blink really slow

        Particle.publish("Pixy", "Object on Right", 60, PRIVATE);  
    }  


    if (myPixyInt > 300 ) {    // Object on far right, leave LED on

        Particle.publish("Pixy", "Object Far Right", 60, PRIVATE);  
    }  



  }  else {  // no blocks seen by camera
      
              Particle.publish("Pixy", "No Object", 60, PRIVATE);  
      
          }
      
      
   delay(5000); // just for the heck of it slow things down a bit
}   // end loop


