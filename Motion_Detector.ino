 /*
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/telegram-esp32-motion-detection-arduino/

  Project created using Brian Lough's Universal Telegram Bot Library: https://github.com/witnessmenow/Universal-Arduino-Telegram-Bot
*/

#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>

// Replace with your network credentials
const char* ssid = "NVA_VERICH";
const char* password = "Ve22012014";

// Initialize Telegram BOT
#define BOTtoken "1871592545:AAE04y1m0i0NlmyZ-ktky_g7uZYvF5I4yGE"  // your Bot Token (Get from Botfather)

// Use @myidbot to find out the chat ID of an individual or a group
// Also note that you need to click "start" on a bot before it can
// message you
#define CHAT_ID1 "790761537"
#define CHAT_ID2 "892526854"

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

int motionSensor = 27; // PIR Motion Sensor
int motionDetected = LOW;
int motion = 0;

//// Indicates when motion is detected
//void IRAM_ATTR detectsMovement() {
//  //Serial.println("MOTION DETECTED!!!");
//  motionDetected = true;
//}

void setup() {
  Serial.begin(115200);

  // PIR Motion Sensor mode INPUT_PULLUP
  pinMode(motionSensor, INPUT_PULLUP);
  // Set motionSensor pin as interrupt, assign interrupt function and set RISING mode
  //attachInterrupt(digitalPinToInterrupt(motionSensor), detectsMovement, RISING);

  // Attempt to connect to Wifi network:
  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  client.setCACert(TELEGRAM_CERTIFICATE_ROOT); // Add root certificate for api.telegram.org

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("");
  Serial.println("WiFi connected");
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
