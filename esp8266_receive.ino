#include <espnow.h>
#include <ESP8266WiFi.h>

// Structure example to receive data
// Must match the sender structure
typedef struct struct_message {
 char QR_id[48];
  char start_date[48];
  char end_date[48];
} struct_message;

// Create a struct_message called myData
struct_message myData;

// callback function that will be executed when data is received
void OnDataRecv(uint8_t * mac, uint8_t *incomingData, uint8_t len) {
  memcpy(&myData, incomingData, sizeof(myData));
  Serial.print("Bytes received: ");
  Serial.println(len);
  Serial.print("QR id: ");
  Serial.println(myData.QR_id);
  Serial.print("Start date: ");
  Serial.println(myData.start_date);
  Serial.print("End date: ");
  Serial.println(myData.end_date);
  Serial.println();
}
 
void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);
  
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != ERR_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  
  // Once ESPNow is successfully Init, we will register for recv CB to
  // get recv packer info
  esp_now_register_recv_cb(OnDataRecv);
}
 
void loop() {

}