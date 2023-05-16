#include <Arduino.h>
#include <WiFi.h>
#include <ArduinoJson.h>
#include <ESP32QRCodeReader.h>
#include <ezBuzzer.h>

#define WIFI_SSID "honey "
#define WIFI_PASSWORD "christabel"

const int BUZZER_PIN = 12;
const int LED_RED = 13; //4 INTERNAL led
const int LED_GREEN = 14;

ESP32QRCodeReader reader(CAMERA_MODEL_AI_THINKER);
struct QRCodeData qrCodeData;
bool isConnected = false;

ezBuzzer buzzer(BUZZER_PIN);

bool connectWifi()
{
  if (WiFi.status() == WL_CONNECTED)
  {
    return true;
  }

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  int maxRetries = 10;
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
    maxRetries--;
    if (maxRetries <= 0)
    {
      return false;
    }
  }
  Serial.println("");
  Serial.println("WiFi connected");
  return true;
}

void setup()
{
  Serial.begin(115200);
  Serial.println();

  pinMode(BUZZER_PIN, OUTPUT);
  
  pinMode(LED_RED, OUTPUT);
  digitalWrite(LED_RED, LOW);

  pinMode(LED_GREEN, OUTPUT);
  digitalWrite(LED_GREEN, LOW);

  reader.setup();
  //reader.setDebug(true);
  Serial.println("Setup QRCode Reader");

  reader.begin();
  Serial.println("Begin QR Code reader");

  delay(1000);
}

void loop()
{
  buzzer.loop();
  bool connected = connectWifi();
  if (isConnected != connected)
  {
    isConnected = connected;
  }
  if (reader.receiveQrCode(&qrCodeData, 100))
  {
    Serial.println("Found QRCode");
    if (qrCodeData.valid)
    {
      delay(100);
      buzzer.beep(100);
      digitalWrite(LED_GREEN, HIGH);
      delay(500);
      digitalWrite(LED_GREEN, LOW);
      Serial.print("Payload: ");
      Serial.println((const char *)qrCodeData.payload);

      StaticJsonDocument<192> doc;
      const char* input =(const char *)qrCodeData.payload;
      DeserializationError error = deserializeJson(doc, input);

      if (error) 
      {
        Serial.print("deserializeJson() failed: ");
        Serial.println(error.c_str());
        return;
      }

      const char* QR_id = doc["QR_id"]; // "3nn0r5nm0ich"
      const char* start_date = doc["start_date"]; // "2023-04-25 19:37:39"
      const char* end_date = doc["end_date"]; // "2023-04-26 19:37:39"
      Serial.println(QR_id);
    }

    else if (!qrCodeData.valid)
    {
      Serial.println("Invalid");
      digitalWrite(LED_RED, HIGH);
      delay(500);
      digitalWrite(LED_RED, LOW);
    }
  }
  delay(300);
}
