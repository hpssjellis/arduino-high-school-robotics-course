/*
 * socket.ino
 * 
 * created 13 July 2010
 * by dlf (Metodo2 srl)
 * modified 31 May 2012
 * by Tom Igoe
 * 
 * modified By Jeremy Ellis 
 * twitter @rocksetta
 * Webpage http://rocksetta.com
 * Arduino High School Robotics Course at
 * https://github.com/hpssjellis/arduino-high-school-robotics-course
 * 
 *  Update Feb 12th, 2020
 *  Specifically for the Arduino Nano 33 IoT
 *
 */


#include <SPI.h>
#include <WiFiNINA.h>

#include "arduino_secrets.h" 
///////please enter your sensitive data in the Secret tab/arduino_secrets.h
char ssid[] = SECRET_SSID;        // your network SSID (name)
char pass[] = SECRET_PASS;    // your network password (use for WPA, or use as key for WEP)
int keyIndex = 0;            // your network key Index number (needed only for WEP)

int status = WL_IDLE_STATUS;
// if you don't want to use DNS (and reduce your sketch size)
// use the numeric IP instead of the name for the server:
//IPAddress server(74,125,232,128);  // numeric IP for Google (no DNS)


///////////////////////// Node Websocket server url without http:// or ending /         ////////

//   so https://myURL/

//   becomes

//   myURL

char server[] = "maker.ifttt.com/trigger/fred_go/with/key/oXc27wPXXHjvmCKJxrFnJm0k2R2NeG3ozAXgjmyZcI6";    

///////////////////////// above is important  ////////////////////////////////////////////////////



// Initialize the Ethernet client library
// with the IP address and port of the server
// that you want to connect to (port 80 is default for HTTP):
WiFiClient client;
//WiFiSSLClient client;

void setup() {
  pinMode(LED_BUILTIN,OUTPUT);
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // check for the WiFi module:
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    // don't continue
    while (true);
  }

  String fv = WiFi.firmwareVersion();
  if (fv < WIFI_FIRMWARE_LATEST_VERSION) {
    Serial.println("Please upgrade the firmware");
  }

  // attempt to connect to Wifi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    delay(10000);
  }
  Serial.println("Connected to wifi");
  printWifiStatus();

  Serial.println("\nStarting connection to server...");
  // if you get a connection, report back via serial:  
  if (client.connect(server, 80)) {
  //if (client.connect(server, 443)) {
    Serial.println("connected to server");
    // Make a HTTP request:
    client.println("GET /?value1=tom&value2=mary&value3=joe HTTP/1.1");
    client.println("Host: maker.ifttt.com");
    //client.println("Connection: close");
    client.println("Connection: keep-alive");
   // client.println("Keep-Alive: timeout=30, max=100");
    client.println();   
  }
}

void loop() {
  // if there are incoming bytes available
  // from the server, read them and print them:
  while (client.available()) {
    char c = client.read();
    Serial.write(c);
    if (c == 'A') {                    // can use any single letter or character
       digitalWrite(LED_BUILTIN, 1);               
       Serial.println();
    }    
    if (c == 'B') {
       digitalWrite(LED_BUILTIN, 0);               
       Serial.println();
    }
  }

  // if the server's disconnected, stop the client:
  if (!client.connected()) {
    Serial.println();
    Serial.println("disconnecting from server.");
    client.stop();

    // do nothing forevermore:
    while (true);
  }
}


void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your board's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}
