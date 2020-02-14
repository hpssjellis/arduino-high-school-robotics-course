/*
 Control light or any other applicace from Yeelink, Wechat,Temboo/ThingSpeak/DeviceHub of IFTTT by using arduino yun
 This sketch connects an 415 MHz to control light using the Yeelink (iOS,Andriod app and web), wechat, IFTTT(twitter), Blynk and IFTTTDo Button(DeviceHub)
 // https://github.com/faweiz
 // https://portfolium.com/faweiz
 // https://www.linkedin.com/in/faweiz
 // Project Tutital : https://www.hackster.io/faweiz/arduino_yun_light
 
 Version change log
 V1.0 created 11 May, 2015 to support Yeelink
 V1.1 update  12 May, 2015 to support wechat(weline)微信号：ECEFan
 V1.2 update  13 May, 2015 to support Temboo with twitter to read a tweet trigger by IFTTT when we push a DO button. 
 V1.3 update  14 May, 2015 to support ThingSpeak's App "Tweet Control" to read a tweet trigger by IFTTT when we push a DO button. 
 V1.4 update   3 June, 2015 to support 443 MHz RF module
 V1.5 update  11 June, 2015 to use Arduino Yun Bridge to connect this project to Blynk.
 V1.6 update  20 August, 2015 to support IFTTT DO Button on ios and android device by using devicehub.net api
 
 Designer: Fawei Zhang 
 */

// include all Libraries needed:
#include <Process.h>
#include <Bridge.h>
#include <Temboo.h>              // v1.2 Temboo libray header file
#include <RCSwitch.h>            // v1.4 433 MHz libray header file
#include <BlynkSimpleYun.h>     // v1.5 Blynk's Arduino Yun libray file
#include "password.h" // Contains Yeelink/Weline/Temboo/Thingspeak/Blynk account info

/* Define the 433 MHz RF Remote conttoller demical code */
#define CH1_ON  4478259
#define CH1_OFF 4478268
#define CH2_ON  4478403
#define CH2_OFF 4478412
#define CH3_ON  4478723
#define CH3_OFF 4478732

RCSwitch mySwitch = RCSwitch();
String dataStringTemp = "";

void setup() {
/* start serial port */
  pinMode(13, OUTPUT);
  Bridge.begin();
  Serial.begin(9600);
/* Wait until a Serial Monitor is connected.  */
  while(!Serial);              // wait for Network Serial to open
         Serial.println(F(" 1. Yeelink\n 2. Wechat\n 3. Temboo\n 4. ThinkSpeak\n 5. Blynk\n 6. DeviceHub\n Please Chose Which Plaform You Want To Control From: "));
/* Blynk */
  Blynk.begin(auth);            // Here your Arduino connects to the Blynk Cloud.
  pinMode(5,INPUT);             // Here I used digital 5 as a input button to control the light
/* Main function  */
  void yeelinkData();                  // Get data from Yeelink
  void wechatData();                   // get data from yeelink (ios,android,web, wechat,Temboo,thingSpeak,DeviceHub and IFTTT)
  void TembooData();                   // Get data from Temboo
  void ThinkSpeakData();               // Get data from ThinkSpeak
  void BlynkData();                    // Get data from Blynk
  void DeviceHubData();                // Get data from DeviceHub
/* 433 MHz RF module */ 
  mySwitch.enableTransmit(7);    // Transmitter is connected to Arduino Pin #7 
  mySwitch.setPulseLength(176);  // Optional set pulse length.
}

void loop() { 
   if(Serial.available()>0)
   {
    int num = Serial.read();
       switch(num)
      {
       case '1':
         yeelinkData(num);                  // Get data from Yeelink   
         break;
       case '2':
         wechatData(num);                  // Get data from Yeelink
         break;
       case '3':
         TembooData(num);                  // Get data from Yeelink
         break;
       case '4':  
         ThinkSpeakData(num);                  // Get data from Yeelink
         break;
       case '5':
         BlynkData(num);                  // Get data from Yeelink
         break;
       case '6':
         DeviceHubData(num);                  // Get data from Yeelink
         break;
       }  
    }
}
