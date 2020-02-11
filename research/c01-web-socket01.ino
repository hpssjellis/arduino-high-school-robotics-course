
#include <WiFiNINA.h>

//TCPClient client;
WiFiClient client;

char server[] = "fastphoton-e2teacher.c9users.io"; // Node server needs to allow users to have read access to your url
String myRandWebSocket = String(rand()*10000+10000); //attempt at random security

bool myUsbSerialDebugOn = true;      // set to true  when hooked up to USB Will block code until keypressed

int connectToMyServer(String myNothing) {

  digitalWrite(LED_BUILTIN, HIGH);
  delay(400);
  digitalWrite(LED_BUILTIN, LOW);

  
  if (client.connect(server, 80)) {
      client.write("GET / HTTP/1.1\r\n");
     // client.write("Host: socket01-e2teacher.c9users.io\r\n");  // note easiest to copy server here
      client.write("Host: ");
      client.write(server);
      client.write("\r\n");  
      client.write("Upgrade: websocket\r\n");
      client.write("Connection: Upgrade\r\n");
      client.write("Sec-WebSocket-Key: dGhlIHNhbXBsZSBub25jZQ==\r\n");
     // client.write("Sec-WebSocket-Key: ");
     // client.write(String(myRandWebSocket));
     // client.write(myRandWebSocket);
     // client.write("==\r\n");
      client.write("Sec-WebSocket-Version: 13\r\n");
      client.write("\r\n");


      if (myUsbSerialDebugOn){
         Serial.println("successfully connected");
       }
       
     
      return 1; // successfully connected

      

  } else {
     if (myUsbSerialDebugOn){
         Serial.println("failed to connect");
      }
     return -1; // failed to connect
  }
  




}



int stopMyServer(String myNothing) {

  digitalWrite(LED_BUILTIN, HIGH);
  delay(100);
  digitalWrite(LED_BUILTIN, LOW);
  delay(100);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(100);
  digitalWrite(LED_BUILTIN, LOW);

    while(client.read() >= 0);    // ignore the rest of the http request
    client.stop();                // shut down the client for next connection

    digitalWrite(LED_BUILTIN, LOW);
    if (myUsbSerialDebugOn){
       Serial.println("successfully disconnected");
    }
    return 1;

}


void setup() {

    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(3, INPUT_PULLDOWN);   // setup a button to D3 to send "A"

   // Spark.function("connect", connectToMyServer);
   // Spark.function("stop", stopMyServer);

      
    randomSeed(analogRead(A0));  
    
    if (myUsbSerialDebugOn){
       Serial.begin(9600);             // Initalize the USB Serial port
   //    while(!Serial.available()) SPARK_WLAN_Loop();
       Serial.println("Hello Computer");
    }

}

void loop() {
       

  
  if (client.connected()) {
      
      
       if ( digitalRead(3) == 1 ){    // read if a button was pressed
       

        IPAddress clientIP = client.remoteIP();
      //  Particle.publish("Remote IP", String(clientIP), 60, PRIVATE);   
        client.write(byte(129));  // tells websockey using Frames
        client.write(byte(1));    // sending only 1 byte. works up to 125 bytes
        client.write("A");        // sending the one byte. any Ascii code !
        if (myUsbSerialDebugOn){
            Serial.print("A");
        }     
     //   Particle.publish("client write", "A", 60, PRIVATE);  
        delay(2);
      }     
      
      
    if (client.available()) {
     
     
     

  
       
        char myIncoming = client.read();

        
        
        if (myIncoming == 'A'){ digitalWrite(LED_BUILTIN, HIGH);}
        if (myIncoming == 'B'){ digitalWrite(LED_BUILTIN, LOW);}
     //   if (myIncoming == 'C'){ RGB.brightness(5); }
      //  if (myIncoming == 'D'){ RGB.brightness(100); }
     //   if (myIncoming == 'E'){ RGB.brightness(250); }
        
        if (myUsbSerialDebugOn){
            Serial.print(myIncoming);
        }  
  

      
      }   
    }
}
