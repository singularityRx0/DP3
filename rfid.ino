  5/*
 *  Created by Aizat Wafri       // B0 4C E0 32
    58:BF:25:DA:FC:83
*/

#define SS_PIN 16  //D0
#define RST_PIN 5 //D1

#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>
#include <espnow.h>
#include <ESP8266WiFi.h>

Servo servo;

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
int statuss = 0;
int out = 0;
String uid1 = "";

uint8_t broadcastAddress[] = {0x58, 0xBF, 0x25, 0xDA, 0xFC, 0x83};

void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus) {
  Serial.print("Last Packet Send Status: ");
  if (sendStatus == 0){
    Serial.println("Delivery success");
  }
  else{
    Serial.println("Delivery fail");
  }
}

void setup() 
{
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522

  servo.attach(2);  //D4
  servo.write(0);
  delay(2000);

  WiFi.mode(WIFI_STA);

  if (esp_now_init() != 0) {
  Serial.println("Error initializing ESP-NOW");
  // return;

  esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);

  esp_now_register_send_cb(OnDataSent);

  esp_now_add_peer(broadcastAddress, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);

  esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
}
}
void loop() 
{
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
  Serial.println();
 // Serial.print(" UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
    //  Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    //  Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  content.toUpperCase();
  uid1 = content;
  Serial.println(uid1);
  //Serial.println();
  if (content.substring(1) == "B0 4C E0 32") //change UID of the card that you want to give access
  {
     Serial.println(" Access Granted ");
    // delay(1000);
     Serial.println();
    for(int i=0; i<4; i++)
    {
      servo.write(90);
      delay(1000);
      servo.write(0);
      delay(1000);
    }
    
    statuss = 1;
  }
  
  else   {
    Serial.println(" Access Denied ");
    delay(3000);
  }
} 
