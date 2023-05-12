#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <esp32cam.h>
#include <ArduCAM.h>
#include <Wire.h>
#include "qrcode-esp32.h"

// Replace with your network credentials
const char* ssid = "Hotspot Xiaomi";
const char* password = "makanmakan24";

WebServer server(80);

void setup() {
  Serial.begin(115200);
  Serial.println();
  
  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.print(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("WiFi connected, IP address: ");
  Serial.println(WiFi.localIP());
  
  // Initialize camera module
  ESP32_Camera.begin();
  ESP32_Camera.setFrameSize(IMG_640x480);
  ESP32_Camera.setQuality(10);
  ESP32_Camera.setContrast(0);
  ESP32_Camera.setBrightness(0);
  ESP32_Camera.setSaturation(0);
}

void loop() {
  server.handleClient();
  
  // Capture image from camera
  camera_fb_t* fb = ESP32_Camera.capture();
  if (!fb) {
    Serial.println("Camera capture failed");
    return;
  }
  
  // Decode QR code from image
  uint8_t* img = fb->buf;
  size_t len = fb->len;
  qr_code_t qrcode;
  if (QRCodeESP32_decode(img, len, &qrcode) == ESP_OK) {
    Serial.println("QR code detected!");
    Serial.println(qrcode.payload);
  }
  
  // Free memory used by image buffer
  ESP32_Camera.release(fb);
  
  delay(1000);
}

