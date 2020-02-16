/*
  WiFi Web Server

 A simple web server that shows the value of the analog input pins.

 This example is written for a network using WPA encryption. For
 WEP or WPA, change the Wifi.begin() call accordingly.

 Circuit:
 * Analog inputs attached to pins A0 through A5 (optional)

 created 13 July 2010
 by dlf (Metodo2 srl)
 modified 31 May 2012
 by Tom Igoe

 */

#include <SPI.h>
#include <WiFiNINA.h>


#include "arduino_secrets.h" 
///////please enter your sensitive data in the Secret tab/arduino_secrets.h
char ssid[] = SECRET_SSID;        // your network SSID (name)
char pass[] = SECRET_PASS;    // your network password (use for WPA, or use as key for WEP)





​

//#define AP_NAME "spdla"

//#define AP_PASSWORD "votmdnjem"

#define IFTTT_HOST "maker.ifttt.com"

#define IFTTT_KEY "zler456465346534"
#define EVENT_NAME "test-program"
​
​
void setup(){
Serial.begin(9600);
//WiFi.mode(WIFI_STA);
//WiFi.begin(AP_NAME, AP_PASSWORD);
​ WiFi.begin(ssid, pass);
while(WiFi.status() != WL_CONNECTED){
delay(1000);
Serial.println("WiFi connecting ...");
}
​
Serial.println("Connected to AP");
Serial.println(WiFi.localIP());
​
send_event(EVENT_NAME);
}
​
void loop(){
//Serial.println("aa");
delay(1000);
}
​
void send_event(const char *event){
Serial.print("Connection to ");
Serial.println(IFTTT_HOST);
​
WiFiClient client;
const int httpPort = 80;
if(!client.connect(IFTTT_HOST, httpPort)){
Serial.print("Connection failed");
return;
}
​
String url = "/trigger/";
url += event;
url += "/with/key/";




url += IFTTT_KEY;






String mJson = String("{\"value1\":\"") + "TES Gom EE~\"}";

Serial.print("Requesting URL: ");

Serial.println(url);

client.println(String("POST ") + url + " HTTP/1.1");

client.println(String("Host: ") + IFTTT_HOST);

client.println("Content-Type: application/json");

client.print("Content-Length: ");

client.println(mJson.length());

client.println();

client.println(mJson);

while(client.connected()){

if(client.available()){

String line = client.readStringUntil('\r');

Serial.print(line);

}else{

delay(50);

};

};

Serial.println();

Serial.println("closing connection");

client.stop();

}
