#include <WiFi.h>

#include <WiFiClientSecure.h>

 

const char* ssid = "Ashish";

const char* password = "12345678";

 

const char* host = "maker.ifttt.com";

const int httpsPort = 443;

 

 

 

void setup() {

  Serial.begin(115200);

  Serial.println();

  Serial.print("connecting to ");

  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {

    delay(500);

    Serial.print(".");

  }

  Serial.println("");

  Serial.println("WiFi connected");

  Serial.println("IP address: ");

  Serial.println(WiFi.localIP());

 

  WiFiClientSecure client;

  Serial.print("connecting to ");

  Serial.println(host);

  if (!client.connect(host, httpsPort)) {

    Serial.println("connection failed");

    return;

  }

 

 

 

  String url = "/trigger/ESP32/with/key/bpLRs1ckTQS2Bax_mDapmoIHPH-3sTo3G4cx3XXXXXX";

  Serial.print("requesting URL: ");

  Serial.println(url);

 

  client.print(String("GET ") + url + " HTTP/1.1\r\n" +

               "Host: " + host + "\r\n" +

               "User-Agent: BuildFailureDetectorESP32\r\n" +

               "Connection: close\r\n\r\n");

 

  Serial.println("request sent");

  while (client.connected()) {

    String line = client.readStringUntil('\n');

    if (line == "\r") {

      Serial.println("headers received");

      break;

    }

  }

  String line = client.readStringUntil('\n');

 

  Serial.println("reply was:");

  Serial.println("==========");

  Serial.println(line);

  Serial.println("==========");

  Serial.println("closing connection");

}

 

void loop() {

}
