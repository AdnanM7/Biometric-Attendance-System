/*
                            *
                            * Project Name:   Biometric Attendance System
                            * Author List:    Adnan Mujawar
                            *     
                            * Filename:       Task6: Operations 
                            * Functions:    
                            * Global Variables: 
                            
                            */
#include <Wire.h> 
#include <LiquidCrystal.h>

const int rs = 12, en = 13, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

#include <SPI.h>
#include <SD.h>
#include <SoftwareSerial.h>
SoftwareSerial fingerPrint(10,11);  //connections of fingerprint module
#include "Adafruit_Fingerprint.h"
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&fingerPrint);

unsigned int id;


String username;
File myFile;
int Status = 0;
const int chipSelect = 53;

#include "RTClib.h" 
RTC_DS1307 rtc;

#include <Keypad.h>
//define the keypad
const byte ROWS = 4;
const byte COLS = 4;
char keypressed;
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'S','0','P','D'}
};
byte rowPins[ROWS] = {31,33,35,37};
byte colPins[COLS] = {43,45,47,49};

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

DateTime now;



void setup() {
  // put your setup code here, to run once:
  
  pinMode(chipSelect,OUTPUT);
  keypad.setDebounceTime(200);
  delay(1000);
 
  
  
  lcd.clear();
  Serial.begin(9600);
  {lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(" MCOE Project Libra ");
    lcd.setCursor(0,1);
    lcd.print("A Biometric Based");
    lcd.setCursor(0,2);
    lcd.print("Student Attendance");
    lcd.setCursor(0,3);
    lcd.print("System");
    delay(4000);
    lcd.clear();
    lcd.print("An Initiative of:");
    lcd.setCursor(0,1);
    lcd.print("Adnan Mujawar");
    delay(2000);
 }
   
  while (!Serial); 
  delay(100);  
  Serial.println("\n\nAdafruit finger detect test");  
  
  finger.begin(57600);  
    
    
  if (finger.verifyPassword()) {  
    Serial.println("Found fingerprint sensor!");  
  } else {  
    Serial.println("Did not find fingerprint sensor :(");  
    while (1) { delay(1); }  
  }   


  Serial.print("Initializing SD card...");

  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    while (1);
  }
  Serial.println("card initialized.");
  if (! rtc.begin())
       Serial.println("Couldn't find RTC");
    // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    if (! rtc.isrunning())
    {
    Serial.println("RTC is NOT running!");
   
 

  
}
}

unsigned int readnumber(void) {
  unsigned int num = 0;
  
  while (num == 0) {
    while (! Serial.available());
    num = Serial.parseInt();
  }
  return num;
}
  
void loop() {
  // put your main code here, to run repeatedly:
 lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("A - Take Attendance");
    lcd.setCursor(0,1);
    lcd.print("B - Register");
    lcd.setCursor(0,2);
    lcd.print("D - Delete Id");
    
      
    delay(1000);
 keypressed = keypad.getKey();
 if (keypressed =='A'){
    unsigned int userId = -1;
    lcd.print("Attendance Process");
     now = rtc.now();
     myFile = SD.open("test.txt", FILE_WRITE);

        // if the file opened okay, write to it:
        if (myFile) {
          myFile.print("Time: ");
          myFile.print(now.hour(), DEC);
          myFile.print(now.minute(), DEC);
          myFile.print(now.second(), DEC);
          myFile.print(" ");
          myFile.print("Date: ");
          myFile.print(now.day(), DEC);
          myFile.print(now.month(), DEC);
          myFile.print(now.year(), DEC);
          myFile.print(" ");
          myFile.close();
        }
             

    Serial.println("Waiting for valid finger...");
    for(int i=0;i<1;i++)
    {
      Status = 0;
      lcd.clear();
      lcd.print("Place Finger");
      delay(2000);

      
      if(userId >=1 && Status != 1)
      {
        
        lcd.clear();
        lcd.setCursor(3,0);
        lcd.print("Present");
        delay(2000);

        // Storing data in SD card

        String ID = String(userId);
 
        myFile = SD.open("test.txt", FILE_WRITE);

        // if the file opened okay, write to it:
        if (myFile) {
          
          myFile.print("User ID ");
          myFile.println(ID);
          // close the file:
          myFile.close();
          Serial.println("done.");
          } else {
          // if the file didn't open, print an error:
          Serial.println("error opening test.txt");
          } 
      }
     }   
 }
  if (keypressed =='B'){
    lcd.setCursor(3,0);
    lcd.print("Registration Process");
    lcd.print("Please type in the ID # (from 1 to 127) you want to delete...");
    uint8_t id = readnumber();
     if (id == 0) {// ID #0 not allowed, try again!
       return; 
    
    
    getFingerprintEnroll();
    
    
     
    
  }
  }
 if(keypressed == 'D')
 {
  Serial.println("To Delete Whole Database, press * key");
  Serial.println("Please type in the ID # (from 1 to 127) you want to delete...");
  unsigned int id = readnumber();
  if (id == 0) {// ID #0 not allowed, try again!
     return;
  }

  Serial.print("Deleting ID #");
  Serial.println(id);
  
  deleteFingerprint(id);
  


if(keypressed == '*'){
  finger.emptyDatabase();
  Serial.println("Database cleared");
}
}
}
// #################### Fingerprint Enroll Function ############################
uint8_t getFingerprintEnroll() {
 
  int p = -1;
  Serial.print("Waiting for valid finger to enroll as #");
  Serial.println(id);
  lcd.clear();
  lcd.setCursor(4,0);
  lcd.print("Place the"); 
  lcd.setCursor(5,1);
  lcd.print("finger "); 
  
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
    switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image taken");
      break;
    case FINGERPRINT_NOFINGER:
      Serial.println(".");
      break;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      break;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
      break;
    default:
      Serial.println("Unknown error");
      break;
    }
  }

  // OK success!

  p = finger.image2Tz(1);
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }
  
  Serial.println("Remove finger");
  lcd.clear();
  lcd.print(" Remove finger "); 
  delay(2000);
  p = 0;
  while (p != FINGERPRINT_NOFINGER) {
    p = finger.getImage();
  }
  Serial.print("ID "); Serial.println(id);
  p = -1;
  Serial.println("Place same finger again");
  lcd.clear();
  lcd.setCursor(3,0);
  lcd.print("Place same"); 
  lcd.setCursor(3,1);
  lcd.print("finger again"); 
  
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
    switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image taken");
      break;
    case FINGERPRINT_NOFINGER:
      Serial.print(".");
      break;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      break;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
      break;
    default:
      Serial.println("Unknown error");
      break;
    }
  }

  // OK success!

  p = finger.image2Tz(2);
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }
  
  // OK converted!
  Serial.print("Creating model for #");  Serial.println(id);
  
  p = finger.createModel();
  if (p == FINGERPRINT_OK) {
    Serial.println("Prints matched!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_ENROLLMISMATCH) {
    Serial.println("Fingerprints did not match");
    return p;
  } else {
    Serial.println("Unknown error");
    return p;
  }   
  
  Serial.print("ID "); Serial.println(id);
  p = finger.storeModel(id);
  if (p == FINGERPRINT_OK) {
    Serial.println("Stored!");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Stored!"); 
    lcd.setCursor(0,1);
    lcd.print("ID ");lcd.print(id); 
    delay(3000);
    
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_BADLOCATION) {
    Serial.println("Could not store in that location");
    return p;
  } else if (p == FINGERPRINT_FLASHERR) {
    Serial.println("Error writing to flash");
    return p;
  } else {
    Serial.println("Unknown error");
    return p;
  }
  lcd.clear();   
}

// ##################  Fingerprint Search   ###########################

int getFingerprintIDez() {
    
    uint8_t p = finger.getImage();
    if (p != FINGERPRINT_OK){
      lcd.clear();
      lcd.setCursor(3,0);
      lcd.print("No Finger ");
      lcd.setCursor(3,1);
      lcd.print("found");
      delay(2000);
      Status = 1;
      return -1;  
    }
        

    p = finger.image2Tz();
    if (p != FINGERPRINT_OK){
      lcd.clear();
      lcd.setCursor(3,0);
      lcd.print("No Finger ");
      lcd.setCursor(3,1);
      lcd.print("found");
      delay(2000);      
      Status = 1;
      return -1;
    }

    p = finger.fingerFastSearch();
    if (p != FINGERPRINT_OK){
      Serial.println("Error Finger");
      
      lcd.clear();
      lcd.setCursor(3,0);
      lcd.print("No Finger ");
      lcd.setCursor(3,1);
      lcd.print("found");
      delay(2000);
      Status = 1;
      return -1;
      
    }

   
 
  Serial.print("Found ID #"); Serial.print(finger.fingerID); 
  Serial.print(" with confidence of "); Serial.println(finger.confidence);
  return finger.fingerID; 

  }
//########################Delete ID##############################
    
 unsigned int deleteFingerprint(unsigned int id) {
  unsigned int p = -1;
  
  p = finger.deleteModel(id);

  if (p == FINGERPRINT_OK) {
    Serial.println("Deleted!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_BADLOCATION) {
    Serial.println("Could not delete in that location");
    return p;
  } else if (p == FINGERPRINT_FLASHERR) {
    Serial.println("Error writing to flash");
    return p;
  } else {
    Serial.print("Unknown error: 0x"); Serial.println(p, HEX);
    return p;
  }   
 }
    
