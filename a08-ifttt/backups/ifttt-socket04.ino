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

char server[] = "8080-da399a05-9fc7-4a80-bcaa-217c4eacb71c.ws-us02.gitpod.io";    

///////////////////////// above is important  ////////////////////////////////////////////////////


// Initialize the Ethernet client library
// with the IP address and port of the server
// that you want to connect to (port 80 is default for HTTP):
//WiFiClient client;
WiFiSSLClient client;

void setup() {
  pinMode(LED_BUILTIN,OUTPUT);
  //Initialize serial and wait for port to open:
  Serial.begin(9600);


  // comment next 3 lines for auto start
  //while (!Serial) {
  // ; // wait for serial port to connect. Needed for native USB port only
  //}

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
  //if (client.connect(server, 80)) {
  if (client.connect(server, 443)) {
    Serial.println("connected to server");
    // Make a HTTP request:
    client.println("GET / HTTP/1.1");
    client.println("Host: "+String(server));
    client.println("Upgrade: websocket");
    client.println("Connection: Upgrade");
    client.println("Sec-WebSocket-Key: dGhlIHNhbXBsZSBub25jZQ==");
    client.println("Sec-WebSocket-Version: 13");
    client.println();   
  }
}

void loop() {
  String currentLine = "";  
  boolean currentLineIsBlank = true;  
  // if there are incoming bytes available
  // from the server, read them and print them:
  while (client.available()) {
    char c = client.read();
    Serial.write(c);
    if (c == '\n' && currentLineIsBlank) {
       // Print webpage if needed
       // client.println("HTTP/1.1 200 OK");
       // client.println("Content-Type: text/html");
       // client.println("Connection: close");  // the connection will be closed after completion of the response
       // client.println("Refresh: 30");  // refresh the page automatically every 30 sec
       // client.println();
    }

  if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        } else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
          currentLine += c;      // add it to the end of the currentLine
        }


    
        if (currentLine.endsWith("led-on")) {
          digitalWrite(LED_BUILTIN, 1);               // GET /led-on turns the LED on
        }
        
        if (currentLine.endsWith("led-off")) {
          digitalWrite(LED_BUILTIN, 0);                // GET /led-off turns the LED off
        }
                if (currentLine.endsWith("A")) {
          digitalWrite(LED_BUILTIN, 1);               // GET /led-on turns the LED on
        }
        
        if (currentLine.endsWith("B")) {
          digitalWrite(LED_BUILTIN, 0);                // GET /led-off turns the LED off
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
