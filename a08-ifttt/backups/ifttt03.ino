/*

 ** REMOVE SENSITIVE MATERIAL BEFORE PUBLISHING!! **
 * If you see this with password or IfTTT key in it, PLEASE
 * contact me...
 * http://sheepdogguides.com/ctact.htm

 SendIfTTTTriggerCode
 See messages to serial monitor for official name, version.
     (search on "gotoVers"

 Lightly adapted from....

 http://randomnerdtutorials.com/door-status-monitor-using-the-esp8266/

 Example created by Rui Santos

 All the resources for this project:
 http://randomnerdtutorials.com/

 Rui said "Based on some ESP8266 code examples"
*/

#include <ESP8266WiFi.h>

WiFiServer server(1203);

//THREE LINES ADDED BY TKB TO BASIC DEMO....
//Block 1 of 2 to set static IP address
IPAddress ip(192, 168, 0, q-FixThis);
IPAddress gateway(192,168,0,1);//These probably the same in most cases
IPAddress subnet(255,255,255,0);These probably the same in most cases


//////////////////////
// WiFi Definitions //
//////////////////////
//Tweak next two for your WiFi environment, and take
//  care not to tell people who shouldn't know
//  what settings you've supplied to the Thing...
const char* ssid = "q-FixThis";
const char* password = "q-FixThis";

//Tweak next with the name of the "This" element you
//  are creating. (You get to choose the name, but what's
//  here, and what's provided for in your IfTTT account
//  must match,.... and.....
//The "key" for the trigger. (This will be discussed later
//  in the essay this listing appears in.)
const char* apiKey = "q-FixThis";
const char* triggerName = "q-FixThis";


const char* host = "maker.ifttt.com";

int button_pin = 4;
int OutPutWithLED = 5;//(Use 5 to drive onboard LED of Sparkfun ESP Thing.)
volatile int state = false;
volatile int flag = false;
//"Door" used throughout in places where "switch" might have fit context better
const char* door_state = "closed";//Assumed switch to connect button_pin to ground is OPEN
  //when program initiates. <<double check this one! <<

unsigned long previousMillis = 0;
const long interval = 3000;

void changeDoorStatus() //This happens after interrupt...
   {
    unsigned long currentMillis = millis();

    if(currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;

        state = !state;
        if(state) {
            door_state = "opened";//was "opened
        }
        else{
            door_state = "closed";
        }
        flag = true;
        Serial.println(state);
        Serial.println(door_state);
    }

}// end of changeDoorStatus()


void setup() {
    digitalWrite(OutPutWithLED,HIGH);
    Serial.begin(9600);
    delay(100);
    Serial.println("Preparing the Door Status Monitor project...");
    //gotoVers (target for searches)
    Serial.println("Program: SendIfTTTTriggerCode");
    Serial.println("(I.e. this program will send the trigger code to make an IfThisThenThat recipe happen.");
    Serial.println("Version: 11 Feb 17");
    Serial.println("(Started 10 Feb 17... my first IfTTT day.)");
    Serial.println("Inspired by a note in a routine Sparkfun mailshot.");
    Serial.println("-");
    Serial.println("This code almost the same as example in...");
    Serial.println("http://randomnerdtutorials.com/door-status-monitor-using-the-esp8266/");
    Serial.println("Preparing the Door Status Monitor project...");
    Serial.println("-");

    pinMode(button_pin, INPUT_PULLUP);
    pinMode(OutPutWithLED, OUTPUT);

    //My thanks to...
    //http://randomnerdtutorials.com/door-status-monitor-using-the-esp8266/
    //... and a tip of the hat to Jeremy Rudge, who would be so pleased, for
    //"introducing" me to interrupts. I've never used one in a program before!
    //And to...
    //https://learn.sparkfun.com/tutorials/esp32-thing-hookup-guide
    //... for, in respect of the Sparkfun ESP8266:
    //"Arduino core also supports interrupts on any pin with the attachInterrupt() function."

    attachInterrupt(digitalPinToInterrupt(button_pin), changeDoorStatus, FALLING); //Was "CHANGE". Interrupts: Very cool. Story for another day.

    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    //ADDED TO DEMO BY TKB... 2 of 2 to set static IP address
    WiFi.config(ip, gateway, subnet);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}

void loop() {
      if(flag){
          Serial.print("Connecting to ");
          Serial.println(host);

          WiFiClient client;
          const int httpPort = 80;//This is port at destination... not of sending ESP8266
          if (!client.connect(host, httpPort)) {
            Serial.println("connection failed");
            return;
            }//of "if (!client.connect(host, httpPort))

          digitalWrite(OutPutWithLED,LOW);//TKB addition... to confirm to user
             //that a POST is happening.

          String url = "/trigger/";
          url +=triggerName;
          url +="/with/key/";
          url += apiKey;

          Serial.print("Requesting URL: ");
          Serial.println(url);
          client.print(String("POST ") + url + " HTTP/1.1\r\n" +
                       "Host: " + host + "\r\n" +
                       "Content-Type: application/x-www-form-urlencoded\r\n" +
                       "Content-Length: 13\r\n\r\n" +
                       "value1=" + door_state + "\r\n");
          flag = false;
          digitalWrite(OutPutWithLED,HIGH);
      } //end of if(flag)...
      delay(10);
}//of Loop
