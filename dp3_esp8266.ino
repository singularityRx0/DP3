#include <espnow.h>
#include <ESP8266HTTPClient.h>
#include <WIFIClientSecureBearSSL.h>
#include <ESP8266WiFi.h>
#include <Servo.h>
#include <SPI.h>
#include <MFRC522.h>



#define SS_PIN 16  //D0 sda
#define RST_PIN 5 //D1
#define GREEN_LED 0 // d3
#define RED_LED 4 // d2
#define SERVO_PIN 2 // d4
#define BUZZER  5// d1
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
int statuss = 0;
int out = 0;
//String uid1 = "";
String content;

//wifi credentials
// const char* ssid = "Galaxy S20 Ultra 5Gff9a";
// const char* password = "05232000lzh";
//const char* ssid = "honey ";
//const char* password = "christabel";
 //d4
//reserve d3 (gpio0) and d2(gpio4) for led
// d3 green led d2 red led
//D1 for buzzer

Servo myservo;
const char* ssid = "guanTou";
const char* password = "wobuyaoar";

String device_key = "123";

//APIs
const char* QR_valid = "http://192.168.43.99/AppPrototype/Microcontroller_http.php";
const char* QR_log = "http://192.168.43.99/AppPrototype/Microcontroller_QRlog.php";
const char* rfid = "http://192.168.43.99/AppPrototype/RFID_http.php";
// Structure example to receive data
// Must match the sender structure
typedef struct struct_message {
 char QR_id[48];
  char start_date[48];
  char end_date[48];

  char uid[48]; 
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

  // Serial.print("Device Key: ");
  // Serial.println(myData.device_key);
  Serial.print("UID: ");
  Serial.println(myData.uid);
}
 
void setup() {
  // Initialize Serial Monitor

  Serial.begin(9600);
    SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  myservo.attach(SERVO_PIN);

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


  pinMode(GREEN_LED, OUTPUT); // grenled
  pinMode(RED_LED, OUTPUT);// red led
  pinMode(BUZZER, OUTPUT);
} // end of void setup()


 
void loop() {
  String QR_id = myData.QR_id;
  String start_date = myData.start_date;
  String end_date = myData.end_date;
  
 // String device_key = myData.device_key; 
  String uid = myData.uid;
  //Initialize client library
  WiFiClient client;
  
  //create http client
  HTTPClient http;
  
  //QR_valid
  http.begin(client, QR_valid);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  String httpRequestData = "&device_key=" + device_key + "&QR_id=" + QR_id + "&start_date=" + start_date + "&end_date=" + end_date;
  Serial.print("httpRequestData: ");
  Serial.println(httpRequestData);


// QR_log
  http.begin(client, QR_log);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  String httpRequestLog = "&device_key=" + device_key + "&QR_id=" + QR_id + "&start_date=" + start_date + "&end_date=" + end_date; 
  Serial.print("httpRequestLog: ");
  Serial.println(httpRequestLog);


// uid 
  http.begin(client, rfid);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  String httpRequest_uid = "&device_key=" + device_key + "&uid" + uid;
  Serial.print("httpRequest_uid: ");
  Serial.println(httpRequest_uid);

  int httpResponseCode_uid = http.POST(httpRequest_uid); // uid
  int httpResponseCode_QRLog = http.POST(httpRequestLog);
  int httpResponseCode_QR = http.POST(httpRequestData);
  


  if (httpResponseCode_QR >0 || httpResponseCode_QRLog > 0 ) {
   Serial.print("HTTP Response code: ");
   Serial.println(httpResponseCode_QR);
   String payload = http.getString();
   int payload_int = payload.toInt();
   Serial.print("Recived payload: \n <<");
   Serial.println(payload_int);
   
    switch (payload_int) {
      case 0 :
      {
      Serial.println("Entry Denied. QR Code Already Used For Entry");
      digitalWrite(RED_LED,HIGH);

       break;
      }
      case 1:
      {
      Serial.println("Entry Allowed");
      myservo.write(0);
     // digitalWrite();
      delay(3000);
      myservo.write(90);
      delay(3000);
      break;
      }
      case 2:
      Serial.println("QR Code Expired");
      break;
      case 3:
      Serial.println("QR Code Does Not Exist");
      break;
      case 4:
      Serial.println("Device ID Not The Same");
      break;
      case 5:
      Serial.println("Exit Allowed");
      myservo.write(0);
      delay(3000);
      myservo.write(90);
      delay(3000);
      break;     
    }
  }
  if (httpResponseCode_QR < 0){
    Serial.print("Error code: ");
    Serial.println(httpResponseCode_QR);
  }
  if(httpResponseCode_QRLog < 0){
    Serial.print("Error code: ");
    Serial.println(httpResponseCode_QRLog);
  }
  // else if (httpResponseCode_QRLog > 0){
  // Serial.print("HTTP Reponse code: ");
  //  Serial.println(httpResponseCode_QRLog);
  //  String payload = http.getString();
  //  int payload_int = payload.toInt();
  //  Serial.print("Recived payload: \n <<");
  //  Serial.println(payload_int);



  // }
  // else {
  //   Serial.print("Error code: ");
  //   Serial.println(httpResponseCode_QR);

  //   Serial.print("Error Code: ");
  //   Serial.println(httpResponseCode_QRLog);
  //  }


 // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  //Serial.println();
 // Serial.print(" UID tag :");
  
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
    //  Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    //  Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  content.toUpperCase();
  //uid1 = content;
  Serial.println(content);
  content = "";
  
 mfrc522.PICC_HaltA();
 mfrc522.PCD_StopCrypto1();


if (httpResponseCode_uid > 0){
Serial.print("HTTP Response code_uid: ");
Serial.println(httpResponseCode_uid);
String x = http.getString();
int payload2_int = x.toInt();

switch(payload2_int){
      case 0:
      Serial.println("Card ID does not exist");
      break;
      case 1:
      Serial.println("Card ID found, Entry allowed.");
      break;
      case 2:
      Serial.println("Card ID found, Please exit.");
      break;
      case 3:
      Serial.println("Device ID not the same");
      break;
}

}
else{
    Serial.print("Error code: ");
    Serial.println(httpResponseCode_uid); // > 3 or < 0 means error
}

  http.end();
  memset(&myData, 0, sizeof(myData));
  myData = empty_struct;
  delay(2000);

 

} // end of void loop()
