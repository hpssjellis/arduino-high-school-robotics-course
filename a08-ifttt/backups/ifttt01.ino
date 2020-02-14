#include <WiFiNINA.h> // UNO WiFi Rev.2

​

#define AP_NAME "spdla"

#define AP_PASSWORD "votmdnjem"

#define IFTTT_HOST "maker.ifttt.com"

#define IFTTT_KEY "zl

#define EVENT_NAME "dlqpsxm"

​

​

void setup(){

Serial.begin(9600);

//WiFi.mode(WIFI_STA);

WiFi.begin(AP_NAME, AP_PASSWORD);

​

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

​

String mJson = String("{\"value1\":\"") + "TES Gom EE~\"}";

Serial.print("Requesting URL: ");

Serial.println(url);

​

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

}

​

Serial.println();

Serial.println("closing connection");

client.stop();

}
