#include <espnow.h>
#include <ESP8266HTTPClient.h>
#include <WIFIClientSecureBearSSL.h>
#include <ESP8266WiFi.h>


//wifi credentials
// const char* ssid = "Galaxy S20 Ultra 5Gff9a";
// const char* password = "05232000lzh";
const char* ssid = "honey ";
const char* password = "christabel";

String device_key = "123";

//APIs
const char* QR_valid = "http://192.168.215.15/dp3/Microcontroller_http.php";
const char* QR_log = "http://192.168.215.15/dp3/Microcontroller_QRlog.php";

// Structure example to receive data
// Must match the sender structure
typedef struct struct_message {
 char QR_id[48];
  char start_date[48];
  char end_date[48];
} struct_message;

// Create a struct_message called myData
struct_message myData;
const struct struct_message empty_struct = {0};

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

}
 
void setup() {
  // Initialize Serial Monitor
  Serial.begin(9600);

  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
  delay(500);
  Serial.print(".");
  }


  Serial.println("");
  Serial.print("Connected to WiFi network");
  Serial.print(WiFi.localIP());
  
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
 String QR_id = myData.QR_id;
  String start_date = myData.start_date;
  String end_date = myData.end_date;
  
  //Initialize client library
  WiFiClient client;
  
  //create http client
  HTTPClient http;
  
  
  http.begin(client, QR_valid);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  
  String httpRequestData = "device_key=" + device_key + "&QR_id=" + QR_id + "&start_date=" + start_date + "&end_date=" + end_date;
  Serial.print("httpRequestData: ");
  Serial.println(httpRequestData);
  
  int httpResponseCode_QR = http.POST(httpRequestData);
  
  if (httpResponseCode_QR >0 ) {
   Serial.print("HTTP Reponse code: ");
   Serial.println(httpResponseCode_QR);
   String payload = http.getString();
   int payload_int = payload.toInt();
   Serial.print("Recived payload: \n <<");
   Serial.println(payload_int);
   
    switch (payload_int) {
      case 0 :
      Serial.print("Entry Denied. QR Code Already Used For Entry");
       break;
      case 1:
      Serial.print("Entry Allowed");
      break;
      case 2:
      Serial.print("QR Code Expired");
      break;
      case 3:
      Serial.print("QR Code Does Not Exist");
      break;
      case 4:
      Serial.print("Device ID Not The Same");
      break;
      case 5:
      Serial.print("Exit Allowed");
      break;     
    }
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode_QR);
   }
  http.end();
  memset(&myData, 0, sizeof(myData));
  myData = empty_struct;
  delay(2000);

 

}