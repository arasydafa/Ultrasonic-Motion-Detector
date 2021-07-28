#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>

const char* ssid = ""; 
const char* password = ""; 

#define BOTtoken ""  
#define CHAT_ID1 "" 
#define CHAT_ID2 "" 

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

int motionSensor = 27;
int motionDetected = LOW;
int motion = 0;

void setup() {
  Serial.begin(115200);

  pinMode(motionSensor);

  Serial.print("Wi-Fi : ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  client.setCACert(TELEGRAM_CERTIFICATE_ROOT); 

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("");
  Serial.println("Wi-Fi Connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  bot.sendMessage(CHAT_ID1, "Bot started up", "");
  bot.sendMessage(CHAT_ID2, "Bot started up", "");
}

void loop() {
  motion = digitalRead(motionSensor);
  if (motion == HIGH)
  {
    bot.sendMessage(CHAT_ID1, "Motion detected!", "");
    bot.sendMessage(CHAT_ID2, "Motion detected!", "");
    Serial.print("MotionDetected,Caution\n\r");
    motionDetected = HIGH;
  }
  else if (motion == LOW)
  {
    bot.sendMessage(CHAT_ID1, "No Motion detected!", "");
    bot.sendMessage(CHAT_ID2, "No Motion detected!", "");
    Serial.print("NoMotionDetected,Clear\n\r");
    motionDetected = LOW;
  }
}
