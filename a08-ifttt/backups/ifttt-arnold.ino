#include <mono.h>           // include mono library

using namespace mono::ui;   // Add mono namespace
using namespace mono::geo;

ButtonView *button;
TextLabelView *statusLbl;
mono::io::Wifi *wifi;
mono::network::HttpPostClient client;
float temp = 0.0;
int lastBatteryLevel = 100;
const char *quotes[] = {
  "I'll be back.",
  "You are one ugly motherfucker.",
  "Hasta la vista, baby.",
  "Remember, Sully, when I promised to kill you last?",

  "Fuck you, asshole.",
  "Consider this a divorce!",
  "Get to the chopper!!",
  "Honey, you shouldn't drink and bake.",

  "Come with me if you want to live.",
  "If it bleeds, we can kill it."
};
int curQuote = 0;
mono::PowerSaver *saver;

void setup() {
  // put your setup code here, to run once:
  saver = new PowerSaver(10000, 60000);

  button = new ButtonView(Rect(20, 80, 176 - 40, 65), "Quote Arnold");
  button->setClickCallback(&handleButton);
  button->show();

  // Text status label
  statusLbl = new TextLabelView(Rect(10,180,156,35), "Not connected");
  statusLbl->setAlignment(TextLabelView::ALIGN_CENTER);
  statusLbl->show();

  wifi = new mono::io::Wifi(YOUR_SSID, YOUR_PASSPHRASE);
  wifi->setConnectedCallback(&networkReady);
  wifi->setConnectErrorCallback(&networkError);

  srand(mono::IApplicationContext::Instance->Temperature->ReadMilliCelcius());
}

void loop() {
  // put your main code here, to run repeatedly:

}

void networkReady()
{
  printf("network ready!\r\n");
  statusLbl->setText("Connected");

  beginPostRequest();
}

void networkError()
{
  statusLbl->setText("Connect Error");
}

void handleButton()
{
  curQuote = rand() % 10;
  if (wifi->isConnected())
  {
    beginPostRequest();
    return;
  }

  wifi->connect();
  statusLbl->setText("Connecting...");
}

void beginPostRequest()
{
  if (!wifi->isConnected()) // bail if network not ready
  {
    statusLbl->setText("not yet ready!");
    return;
  }

  client = mono::network::HttpPostClient(
    "http://maker.ifttt.com/trigger/" YOUR_EVENT_NAME "/with/key/" YOUR_API_KEY,
    "Content-Type: application/json\r\n");
  client.setBodyDataCallback(&httpData);
  client.setBodyLengthCallback(&httpLength);

  temp = mono::IApplicationContext::Instance->Temperature->ReadMilliCelcius() / 1000.0;
  lastBatteryLevel = mono::power::MonoBattery::ReadPercentage();
  client.post();
}

uint16_t httpLength()
{
  // get the fraction part of floating point
  int fracPart = 10*(temp - (int)temp);
  return snprintf(0,0, "{ \"value1\": \"%s\", \"value2\": %i.%i, \"value3\": %i}", quotes[curQuote], (int)temp, fracPart, lastBatteryLevel);
}

void httpData(char *data)
{
  // get the fraction part of floating point
  int fracPart = 10*(temp - (int)temp);
  snprintf(data,httpLength()+1, "{ \"value1\": \"%s\", \"value2\": %i.%i, \"value3\": %i}", quotes[curQuote], (int)temp, fracPart, lastBatteryLevel);
}
