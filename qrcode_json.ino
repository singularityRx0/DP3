#include <Arduino.h>
#include <WiFi.h>
#include <ArduinoJson.h>
#include <ESP32QRCodeReader.h>
#include <esp_now.h>

// REPLACE WITH YOUR RECEIVER MAC Address
uint8_t broadcastAddress[] = {0x58, 0xBF, 0x25, 0xDA, 0xFC, 0x83};

// Structure example to send data
// Must match the receiver structure
typedef struct struct_message {
  const char* QR_id;
  const char* start_date;
  const char* end_date;
} struct_message;

// Create a struct_message called myData
struct_message myData;
ESP32QRCodeReader reader(CAMERA_MODEL_AI_THINKER);
struct QRCodeData qrCodeData;
bool isConnected = false;

esp_now_peer_info_t peerInfo;

// callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}
 
void setup() {
  // Init Serial Monitor
  Serial.begin(115200);
 
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Trasnmitted packet
  esp_now_register_send_cb(OnDataSent);
  
  // Register peer
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  
  // Add peer        
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
  reader.setup();
  //reader.setDebug(true);
  Serial.println("Setup QRCode Reader");

  reader.begin();
  Serial.println("Begin QR Code reader");

  delay(1000);
}
 
void loop() {
  if (reader.receiveQrCode(&qrCodeData, 100)) {
    Serial.println("Found QRCode");
    if (qrCodeData.valid) {
      delay(100);
      // buzzer.beep(100);
      // digitalWrite(LED_GREEN, HIGH);
      // delay(500);
      // digitalWrite(LED_GREEN, LOW);
      Serial.print("Payload: ");
      Serial.println((const char*)qrCodeData.payload);

      StaticJsonDocument<192> doc;
      const char* input = (const char*)qrCodeData.payload;
      DeserializationError error = deserializeJson(doc, input);
      if (error) {
        Serial.print("deserializeJson() failed: ");
        Serial.println(error.c_str());
        return;
      }
      myData.QR_id = doc["QR_id"];            // "3nn0r5nm0ich"
      myData.start_date = doc["start_date"];  // "2023-04-25 19:37:39"
      myData.end_date = doc["end_date"];      // "2023-04-26 19:37:39"
      Serial.println(myData.QR_id);
      esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
      if (result == ESP_OK) {
        Serial.println("Sent with success");
        delay(60000);
      }
      else {
        Serial.println("Error sending the data");
        }
    }

    else if (!qrCodeData.valid) {
      Serial.println("Invalid");
      // digitalWrite(LED_RED, HIGH);
      // delay(500);
      // digitalWrite(LED_RED, LOW);
    }
  }
  delay(1000);
}
