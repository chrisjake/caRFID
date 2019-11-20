//This sketch was based upon another one (possibly multiple ones) I found when looking at others projects. Unfortunately I can't remember who to credit :S. If you recognise any of the code below, let me know and I'll credit you appropriately.

#include <Wire.h>                     //Lets us use I2C as our communication protocol
#include <Adafruit_NFCShield_I2C.h>   //Adafruit library to use this reader.
Adafruit_NFCShield_I2C nfc(2, 3);     //Pins that we are initialising the reader on. Default, I think.

int cardnum = 0;                       //Int to store the ID of the tag
byte success;                          //Byte value to detect read
byte uid[] = { 0, 0, 0, 0, 0, 0, 0 };  // Buffer to store the returned UID
byte uidLength;                        // Length of the device ID. (4 or 7 bytes depending on ISO14443A card type)    

void setup(void) {
  Serial.begin(115200);                //Serial for debugging
  nfc.begin();
  pinMode(8, OUTPUT);
  pinMode(10, OUTPUT);
  Serial.print("Boot");
}

void loop(){
  readtag();
  if (cardnum == 0xE5, 0x96, 0x25, 0xD4){               //Tag ID goes here as a digit. This if statement runs if the tag ID read matches the tag listed here. You can list multiple tags here if you like - use or statements
    cardnum = 0;
    lockcycle();                        
  }
}

void readtag(){                          //This function reads the tag and writes the numbers into the byte variable uid
  success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength);
  cardnum = uid[3];
  cardnum <<= 8; cardnum |= uid[2];
  cardnum <<= 8; cardnum |= uid[1];
  cardnum <<= 8; cardnum |= uid[0];
  Serial.println(cardnum);

}

void lockcycle(){                       //This function triggers the switching circuit
  Serial.println("Correct");            //debugging
  digitalWrite(8, HIGH);        //triggers the pin which to unlock the gate on the serial circuit
  delay(60);                            //you may need to change wait time depending on your car/parts
  digitalWrite(8, LOW);         //Stops triggering the unlock circuit
  delay(20000);                         //Waits 20s
  digitalWrite(10, HIGH);          //Relocks the car
  delay(60);
  digitalWrite(10, LOW);  
  
}
  
