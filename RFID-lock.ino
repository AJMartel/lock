
#include <SPI.h>
#include <MFRC522.h>
#include<Servo.h>

Servo myservo;  
int myuid=4294947523;// enter the your uid here.  

int pos = 0;    

#define SS_PIN 10
#define RST_PIN 9
 
MFRC522 rfid(SS_PIN, RST_PIN); 

MFRC522::MIFARE_Key key; 

 
byte nuidPICC[4];

void setup() { 
  Serial.begin(9600);
    myservo.attach(9);  
    myservo.write(0);
  SPI.begin(); 
  rfid.PCD_Init(); 

  for (byte i = 0; i < 6; i++) {
    key.keyByte[i] = 0xFF;
  }

  //Serial.println(F("This code scan the MIFARE Classsic NUID."));
  //Serial.print(F("Using the following key:"));
  //printHex(key.keyByte, MFRC522::MF_KEY_SIZE);
}
 
void loop() {
  if(rfid.PICC_IsNewCardPresent()) {
  unsigned long uid = getID();
  if(uid != -1){
    Serial.print("UID: "); 
    Serial.println(uid);
  }
  if (uid==myuid)
  {
    Serial.println("OPEN");
    myservo.write(90);
    delay(3000);
    myservo.write(180);
  }
  else 
  {
    Serial.println("access denied");
    }
  }
}


unsigned long getID(){
  if ( ! rfid.PICC_ReadCardSerial()) { 
    return -1;
  }
  unsigned long hex_num;
  hex_num =  rfid.uid.uidByte[0] << 24;
  hex_num += rfid.uid.uidByte[1] << 16;
  hex_num += rfid.uid.uidByte[2] <<  8;
  hex_num += rfid.uid.uidByte[3];
  rfid.PICC_HaltA(); 
  return hex_num;
}
