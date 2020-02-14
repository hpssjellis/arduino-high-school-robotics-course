#include <ESP8266WiFi.h>

//static const uint8_t D0   = 16;
//static const uint8_t D1   = 5;
//static const uint8_t D2   = 4;
//static const uint8_t D3   = 0;
//static const uint8_t D4   = 2;
//static const uint8_t D5   = 14;
//static const uint8_t D6   = 12;
//static const uint8_t D7   = 13;
//static const uint8_t D8   = 15;
//static const uint8_t D9   = 3;
//static const uint8_t D10  = 1;

int inPin = 16;   // pushbutton connected to digital pin 0   
int val = 0;     // variable to store the read value
//Include the SSL client
#include <WiFiClientSecure.h>

char ssid[] = "<SSID>";       // your network SSID (name)
char password[] = "<PASSWORD>";  // your network key

//Add a SSL client
WiFiClientSecure client;


void setup() {

  pinMode(inPin, INPUT);      // sets the digital pin 1 as input

   Serial.begin(115200);

  // Set WiFi to station mode and disconnect from an AP if it was Previously
  // connected
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  // Attempt to connect to Wifi network:
  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }


Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  IPAddress ip = WiFi.localIP();
  Serial.println(ip);

}

String MicrosoftFlow() {
 
  char host[] = "prod-37.westus.logic.azure.com";

  if (client.connect(host, 443)) {
    Serial.println("connected");

    String URL = "/workflows/<ID>/triggers/manual/paths/invoke?api-version=2016-06-01&sp=%2Ftriggers%2Fmanual%2Frun&sv=1.0&sig=<ID>";

    Serial.println(URL);

    client.println("GET " + URL + " HTTP/1.1");
    client.print("Host: "); client.println(host);
    client.println("User-Agent: arduino/1.0");
    client.println("");
    }
}

void loop() {
  
  
  val = digitalRead(inPin);  // read input value
  delay(200);
  //Serial.println(val);

  if(val==HIGH){
    MicrosoftFlow();
    delay(1000);
    setup(); 
    }
  
}
