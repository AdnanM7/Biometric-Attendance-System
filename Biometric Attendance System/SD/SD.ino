/*
                            *
                            * Project Name:   Biometric Attendance System
                            * Author List:    Adnan Mujawar
                            *     
                            * Filename:       Task9: SD Card Initialisation
                            * Functions:    
                            * Global Variables: 
                            *
                            */#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <SD.h>
#include <Adafruit_Fingerprint.h> 

#define mySerial Serial1
#define buzzer 8
LiquidCrystal_I2C lcd(0x27,20,4);
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial); 
 
uint8_t id;
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
  pinMode(buzzer,OUTPUT);
  pinMode(chipSelect,OUTPUT);
  keypad.setDebounceTime(200);
  delay(1000);
 
  lcd.init();
  lcd.backlight();
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
    lcd.print("R&D CLUB");
    delay(2000);
 }
   
  while (!Serial);  // For Yun/Leo/Micro/Zero/...  
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

  
void loop() {
  // put your main code here, to run repeatedly:
 lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("A - Take Attendance");
    lcd.setCursor(0,1);
    lcd.print("B - Register");  
    delay(1000);
 keypressed = keypad.getKey();
 if (keypressed =='A'){
    uint8_t userId = -1;
    lcd.print("Attendance Process");
    

    Serial.println("Waiting for valid finger...");
    for(int i=0;i<1;i++)
    {
      Status = 0;
      lcd.clear();
      lcd.print("Place Finger");
      delay(2000);

      userId = getFingerprintIDez();
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

    finger.getTemplateCount();  
    Serial.print("Sensor contains "); 
    Serial.print(finger.templateCount); 
    Serial.println(" templates");  
    id = finger.templateCount + 1;
    Serial.println(id); 
    getFingerprintEnroll();
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
    
    
 
    
