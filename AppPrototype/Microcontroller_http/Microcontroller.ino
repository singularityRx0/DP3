#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecureBearSSL.h>
#include <Wire.h>

//wifi crendentials
const char* ssid     = "";
const char* password = "";

// REPLACE with your Domain name and URL path or IP address with path
const char* serverName = "http://19/AppPrototype/Microcontroller_http.php";

String device_key = "123";


void setup() {
  Serial.begin(9600);
  
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) { 
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());

}

void loop() {
  //Check WiFi connection status
  if(WiFi.status()== WL_CONNECTED){

    string QR_id = "";
    string start_date = "";
    string end_date = "",
    
    
    //Initialize client library
    WiFiClient client;
    //create HTTPClient instance
    HTTPClient http;
    
    http.begin(client, serverName);
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    
    String httpRequestData = "device_key=" + device_key + "&QR_id=" + QR_id
                          + "&start_date=" + start_date + "&end_date=" + end_date;
    Serial.print("httpRequestData: ");
    Serial.println(httpRequestData);

    int httpResponseCode = http.POST(httpRequestData);
        
    if (httpResponseCode>0) {
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
      String payload = http.getString();
      int payload_int = payload.toInt();
      Serial.println("received payload:\n<<");
      Serial.println(payload);
      switch (payload_int) {
        case 0:
        Serial.print("Entry Denied");
        break;
        case 1:
        Serial.print("Entry Allowed");
        break;
        case 3:
        Serial.print("QR Code Does Not Exist");
        break;
        case 4:
        Serial.print("Device ID not the same");
        default:
        break;
      }
    else {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
    }
    // Free resources
    http.end();
  }
  else {
    Serial.println("WiFi Disconnected");
  }
  //HTTP POST request every 30 seconds
  delay(30000);  
}
