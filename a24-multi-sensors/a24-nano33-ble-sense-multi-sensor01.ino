/*
  nano-33-sense-serial-example.ino
  Copyright (c) 2020 Dale Giancono. All rights reserved..
  This program outputs all raw sensor data from the Arduino Nano 33 BLE 
  Sense board via serial at a 20Hz rate. It also calculates the RMS 
  value of the microphone buffer and outputs that data. It is intended
  as a quick way to become familiar with some of the sensor libraries 
  available with the Nano 33 BLE Sense, and highlight some of the 
  difficulties when using a super loop architecture with this board.
  
  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.
  
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  
  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

/**********/
/*INCLUDES*/
/**********/

/* For MP34DT05 microphone */
#include <PDM.h>

/* For LSM9DS1 9-axis IMU sensor */
#include <Arduino_LSM9DS1.h>

/* For APDS9960 Gesture, light, and proximity sensor */
#include <Arduino_APDS9960.h>

/* For LPS22HB barometric barometricPressure sensor */
#include <Arduino_LPS22HB.h>

/* For HTS221 Temperature and humidity sensor */
#include <Arduino_HTS221.h>


/********/
/*MACROS*/
/********/
/* Set these macros to true with you want the output plotted in a way that
 * can be viewed with serial plotter. Having them all true creates a pretty
 * meaningless graph, as the scaling will be way off for each sensor, and there
 * will be too much data to view */
#define SERIAL_PLOT_MP34DT05    (true)
#define SERIAL_PLOT_LSM9DS1     (true)
#define SERIAL_PLOT_APDS9960    (true)
#define SERIAL_PLOT_LPS22HB     (true)
#define SERIAL_PLOT_HTS221      (true)
#define SERIAL_MONITOR_AND_SLOW (true)

/* This value was also used in the PDM example, seems like a good enough reason to
 * continue using it. With this value and 16kHz sampling frequency, the RMS sampling
 * period will be 16mS */
//#define MICROPHONE_BUFFER_SIZE_IN_WORDS (256U)
//#define MICROPHONE_BUFFER_SIZE_IN_BYTES (MICROPHONE_BUFFER_SIZE_IN_WORDS * sizeof(int16_t))


// buffer to read samples into, each sample is 16-bits
short sampleBuffer[256];

// number of samples read
volatile int samplesRead;

/******************/
/*LOCAL VARIABLES*/
/******************/

/******************/
/*GLOBAL VARIABLES*/
/******************/

/* MP34DT05 Microphone data buffer with a bit depth of 16. Also a variable for the RMS value */
//int16_t microphoneBuffer[MICROPHONE_BUFFER_SIZE_IN_WORDS];
////int16_t microphoneRMSValue;
/* variables to hold LSM9DS1 accelerometer data */
float accelerometerX, accelerometerY, accelerometerZ;
/* variables to hold LSM9DS1 gyroscope data */
float gyroscopeX, gyroscopeY, gyroscopeZ;
/* variables to hold LSM9DS1 magnetic data */
float magneticX, magneticY, magneticZ;
/* variables to hold LPS22HB  barometric pressure data */
float barometricPressure;
/* variables to hold APDS9960 proximity, gesture and colour data */
int proximity, gesture, colourR, colourG, colourB;
/* variables to hold HTS221 temperature and humidity data */
float temperature, humidity;

/* Used to count 1000ms intervals in loop() */
int oldMillis;
int newMillis;

long myAverageSound = 0;
long myTotalSounds = 0;
long myMappedSound = 0;
/* Used as a simple flag to know when microphone buffer is full and RMS value
 * can be computed. */
//bool microphoneBufferReadyFlag;

/****************************/
/*LOCAL FUNCTION PROTOTYPES*/
/****************************/

/****************************/
/*GLOBAL FUNCTION PROTOTYPES*/
/****************************/
/* This function is called each time PDM data is available. It will be used to fill the
 * microphone buffer that we will then use to calculate RMS values */
//void Microphone_availablePDMDataCallback(void);
/* This function computes the RMS value based on the data contained within the microphoneBuffer
 * If the microphone buffer has a word length of 256, and the sample rate for the microphone is 16kHz,
 * then this RMS value is taken over (1/16000)*256 = 16mS */
//void Micophone_computeRMSValue(void);

/****************************/
/*IMPLEMENTATION*/
/****************************/
void setup()
{
  /* Serial setup for UART debugging */
  Serial.begin(115200);
  /* Wait for serial to be available */
  //while(!Serial);   // this confuses students

  /* PDM setup for MP34DT05 microphone */
  /* configure the data receive callback to transfer data to local buffer */
 // PDM.onReceive(Microphone_availablePDMDataCallback);
  /* Initialise single PDM channel with a 16KHz sample rate (only 16kHz or 44.1kHz available */
 // if (!PDM.begin(1, 16000))
  //{
  //  Serial.println("Failed to start PDM!");
    /* Hacky way of stopping program executation in event of failure. */
  //  while(1);
 // }
  //else
//  {
    /* Gain values can be from 0 to 80 (around 38db). Check out nrf_pdm.h
     * from the nRF528x-mbedos core to confirm this. */
    /* This has to be done after PDM.begin() is called as begin() always
     *  sets the gain as the default PDM.h value (20).
     */
 //   PDM.setGain(50);
 // }



  // configure the data receive callback
  PDM.onReceive(onPDMdata);

  // optionally set the gain, defaults to 20
  // PDM.setGain(30);

  // initialize PDM with:
  // - one channel (mono mode)
  // - a 16 kHz sample rate
  if (!PDM.begin(1, 16000)) {
    Serial.println("Failed to start PDM!");
    while (1);
  }


  
  /* IMU setup for LSM9DS1*/
  /* default setup has all sensors active in continous mode. Sample rates
   *  are as follows: magneticFieldSampleRate = 20Hz, gyroscopeYroscopeSampleRate = 109Hz,
   * accelerationSampleRate = 109Hz */
  if (!IMU.begin())
  {
    Serial.println("Failed to initialize IMU!");
    /* Hacky way of stopping program executation in event of failure. */
    while(1);
  }


  /* Set sensitivity from 0 to 100. Higher is more sensitive. In
   * my experience it requires quite a bit of experimentation to
   * get this right, as if it is too sensitive gestures will always
   * register as GESTURE_DOWN or GESTURE_UP and never GESTURE_LEFT or
   * GESTURE_RIGHT. This can be called before APDS.begin() as it just
   * sets an internal sensitivity value.*/
  APDS.setGestureSensitivity(50);
  if (!APDS.begin())
  {
    Serial.println("Error initializing APDS9960 sensor.");
    /* Hacky way of stopping program executation in event of failure. */
    while(1);
  }
  /* As per Arduino_APDS9960.h, 0=100%, 1=150%, 2=200%, 3=300%. Obviously more
   * boost results in more power consumption. */
  APDS.setLEDBoost(0);

  /* Barometric sensor setup for LPS22HB*/
  if (!BARO.begin())
  {
    Serial.println("Failed to initialize barometricPressure sensor!");
    while (1);
  }

  /* Temperature/Humidity sensor setup for HTS221*/
  if (!HTS.begin())
  {
    Serial.println("Failed to initialize humidity temperature sensor!");
    /* Hacky way of stopping program executation in event of failure. */
    while(1);
  }

  /* Initialise timing variables. */
  oldMillis = 0;
  newMillis = 0;
  /* Initialise micophone buffer ready flag */
 // microphoneBufferReadyFlag = false;
}

void loop()
{


  // wait for samples to be read
  if (samplesRead) {   
    myAverageSound = 0;
    myTotalSounds = 0;
    myMappedSound = 0;

    // print samples to the serial monitor or plotter

    for (int i = 0; i < samplesRead; i++) {
      //Serial.println(sampleBuffer[i]);
      myTotalSounds +=  sampleBuffer[i];
    }
    myAverageSound = (myTotalSounds / samplesRead);
    // clear the read count
    samplesRead = 0;
  }

  
  /* The sensors that use I2C must be checked to see if data is available, so
   *  this is checked each loop. This include the IMU and Gesture/light/proximity
   *  sensors. Other sensors (barometric pressure and temperature/humidity)
   *  will give a value when we ask for it. These values are requested each
   *  1000ms using millis() in a hacky way, but it works.
   *
   *  Data is output via serial every 50ms (20Hz). There is no good way to plot of
   *  the data from the sensors together due the differing sample rates, but this
   *  represented a decent compromise as changes will still be observable in all
   *  sensor data.
   */

  /* Get the new millis() value which helps time serial plotting and getting
   * of pressure, temperature, and humidity values. */
  newMillis = millis();

  /* Every 50ms plot all data to serial plotter. */
  if((newMillis - oldMillis) % 50)
  {
#if (SERIAL_PLOT_MP34DT05 == true)
   // Serial.printf("%d,", microphoneRMSValue);
   // Serial.printf("%f,", myTotalSounds);
   // Serial.printf("%d,", myAverageSound);
    
   //map(value, fromLow, fromHigh, toLow, toHigh)
   myMappedSound = map(myAverageSound, -1000, 1000, -100, 300);
   Serial.printf("%d,", myMappedSound);
    
#endif
#if (SERIAL_PLOT_LSM9DS1 == true)
    Serial.printf("%f,%f,%f,", accelerometerX, accelerometerY, accelerometerZ);
    Serial.printf("%f,%f,%f,", gyroscopeX, gyroscopeY, gyroscopeZ);
    Serial.printf("%f,%f,%f,", magneticX, magneticY, magneticZ);
#endif
#if (SERIAL_PLOT_APDS9960 == true)

    Serial.printf("%f,", barometricPressure);
#endif
#if (SERIAL_PLOT_LPS22HB == true)
    Serial.printf("%d,%d,%d,%d,%d,", proximity, gesture, colourR, colourG, colourB);
#endif
#if (SERIAL_PLOT_HTS221 == true)
    Serial.printf("%f, %f", temperature, humidity);
#endif
    Serial.println();
  }

  /* Every 1000ms get the pressure, temperature, and humidity data */
  if((newMillis - oldMillis) > 1000)
  {
    barometricPressure = BARO.readPressure();
    temperature = HTS.readTemperature();
    humidity = HTS.readHumidity();
    oldMillis = newMillis;
  }


  /* If new acceleration data is available on the LSM9DS1 get the data.*/
  if(IMU.accelerationAvailable())
  {
    IMU.readAcceleration(accelerometerX, accelerometerY, accelerometerZ);
  }
  /* If new gyroscope data is available on the LSM9DS1 get the data.*/
  if(IMU.gyroscopeAvailable())
  {
    IMU.readGyroscope(gyroscopeX, gyroscopeY, gyroscopeZ);
  }
  /* If new magnetic data is available on the LSM9DS1 get the data.*/
  if (IMU.magneticFieldAvailable())
  {
    IMU.readMagneticField(magneticX, magneticY, magneticZ);
  }
  /* If new proximity data is available on the APDS9960 get the data.*/
  if (APDS.proximityAvailable())
  {
    proximity = APDS.readProximity();
  }
  /* If new colour data is available on the APDS9960 get the data.*/
  if (APDS.colorAvailable())
  {
    APDS.readColor(colourR, colourG, colourB);
  }
  /* If new gesture data is available on the APDS9960 get the data.*/
  if (APDS.gestureAvailable())
  {
    gesture = APDS.readGesture();
  }




#if (SERIAL_MONITOR_AND_SLOW == true)
  delay(4000);
  Serial.println();
  Serial.println("------------------------------------------------------------");
  Serial.println("PDM microphone Average: " + String(myMappedSound));
  Serial.println("accelerometerX: " + String(accelerometerX,4) + ", accelerometerY: " + String(accelerometerY,4)+", accelerometerZ: " + String(accelerometerZ,4)  );

  Serial.println("gyroscopeX: " + String(gyroscopeX) + ", gyroscopeY: " + String(gyroscopeY)+", gyroscopeZ: " + String(gyroscopeZ)  );
  Serial.println("magneticX: " + String(magneticX) + ", magneticY: " + String(magneticY)+", magneticZ: " + String(magneticZ)  );
  Serial.println("barometricPressure: " + String(barometricPressure));

  Serial.println("proximity: " + String(proximity) + ", gesture: " + String(gesture)  );
  Serial.println("GESTURE_UP: " + String(GESTURE_UP) + ", GESTURE_DOWN: " + String(GESTURE_DOWN)  );
  Serial.println("GESTURE_LEFT: " + String(GESTURE_LEFT) + ", GESTURE_RIGHT: " + String(GESTURE_RIGHT)  );
  
  Serial.println("colourR: " + String(colourR) + ", colourG: " + String(colourG)+", colourB: " + String(colourB)  );
  Serial.println("temperature: " + String(temperature) + ", humidity: " + String(humidity)  );

  Serial.println();
  Serial.println();
  Serial.println("------------------------------------------------------------");
  Serial.println("Raw data below:");




#endif


  /* If the microphone buffer is full, compute the RMS value */
 // if(microphoneBufferReadyFlag)
//  {
 //   Micophone_computeRMSValue();
 //   microphoneBufferReadyFlag = false;
 // }

// delay(5000);
}   // end main loop



void onPDMdata() {
  // query the number of bytes available
  int bytesAvailable = PDM.available();

  // read into the sample buffer
  PDM.read(sampleBuffer, bytesAvailable);

  // 16-bit, 2 bytes per sample
  samplesRead = bytesAvailable / 2;
}



/*

void Microphone_availablePDMDataCallback()
{
  // query the number of bytes available
  int bytesAvailable = PDM.available();

  if(bytesAvailable == MICROPHONE_BUFFER_SIZE_IN_BYTES)
  {
    PDM.read(microphoneBuffer, bytesAvailable);
    microphoneBufferReadyFlag = true;
  }
}

void Micophone_computeRMSValue(void)
{
  arm_rms_q15((q15_t*)microphoneBuffer, MICROPHONE_BUFFER_SIZE_IN_WORDS, (q15_t*)&microphoneRMSValue);
}


*/
