 /*
                            *
                            * Project Name:   Biometric Attendance System
                            * Author List:    Adnan Mujawar
                            *     
                            * Filename:       Task:4 LCD 
                            * Functions:    
                            * Global Variables: 
                            *
                            */
#include <SD.h>

#include <SPI.h>

const int chipSelect = 4;

#include <SoftwareSerial.h>

#include<EEPROM.h>

#include <Wire.h>

#include<LiquidCrystal.h>
const int rs = 12, en = 13, d4 = 5, d5 = 4, d6 = 3, d7 = 2;  //Connections of LCD
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

SoftwareSerial fingerPrint(10,11);  //connections of fingerprint module


#include "RTClib.h" 
RTC_DS1307 rtc;

#include "Adafruit_Fingerprint.h"
uint8_t id;
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&fingerPrint);

#include <Keypad.h>

float userset = 0;
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'S','0','P','D'}
};
byte rowPins[ROWS] = {31,33,35,37};
byte colPins[COLS] = {43,45,47,49};

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

#define buzzer 8
#define records 4  // 5 for 5 user
#define indFinger 10
int user1,user2,user3,user4,user5,user6,user7,user8,user9,user10,user11,user12,user13,user14,user15,user16,user17,user18,user19,user20,user21,user22,user23,user24,user25,user26,user27,user28,user29,user30,user31,user32,user33,user34,user35,user36,user37,user38,user39,user40,user41,user42,user43,user44;

DateTime now;

File myFile;

void setup()
{
    delay(1000);
    lcd.begin(20,4);
    Serial.begin(9600);
    while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
    Serial.print("Initializing SD card...");
    pinMode(53, OUTPUT);

  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    while (1);
  }
  Serial.println("card initialized.");
    myFile = SD.open("attend.txt", FILE_WRITE);
  

    keypad.setDebounceTime(20);
    char key = keypad.getKey();
    lcd.print("press # to prgram");
    if (key == '#')
    { 
      lcd.clear();
      lcd.print("press");
      lcd.setCursor(0,2);
      lcd.print("A:Enroll  B:Delete");
      lcd.setCursor(0,3);
      lcd.print("C:Up  D:Down");
      lcd.setCursor(0,4);
      lcd.print("*: Match");
      delay(2000);
      
    }
    if (key == 'A')
    {
      digitalWrite(buzzer, HIGH);
      delay(500);
      digitalWrite(buzzer, LOW);
      lcd.clear();
      lcd.print("Please wait");
      lcd.setCursor(0,1);
      lcd.print("Downloding Data");

      Serial.println("Please wait");
      Serial.println("Downloding Data..");
      Serial.println();

      Serial.print("S.No.         ");
      for(int i=0;i<records;i++)
      {
              digitalWrite(buzzer, HIGH);
      delay(500);
      digitalWrite(buzzer, LOW);
        Serial.print("         User ID");
        Serial.print(i+1);
        Serial.print("                   ");
      }
      Serial.println();
      int eepIndex=0;
      for(int i=0;i<30;i++)
      {
        if(i+1<10)
        Serial.print('0');
        Serial.print(i+1);
        Serial.print("          ");
        eepIndex=(i*7);
        download(eepIndex);
        eepIndex=(i*7)+210;
        download(eepIndex);
        eepIndex=(i*7)+420;
        download(eepIndex);
        eepIndex=(i*7)+630;
        download(eepIndex);
      //  eepIndex=(i*7)+840;   // 5th user
      //  download(eepIndex);
        Serial.println();
      }
    }
    if (key == 'B')
    {
      lcd.clear();
      lcd.print("Please Wait");
      lcd.setCursor(0,1);
      lcd.print("Reseting.....");
      for(int i=1000;i<1005;i++)
      EEPROM.write(i,0);
      for(int i=0;i<841;i++)
      EEPROM.write(i, 0xff);
      lcd.clear();
      lcd.print("System Reset");
      delay(1000);
    }

    
    lcd.clear();
    lcd.print("   Attendance   ");
    lcd.setCursor(0,1);
    lcd.print("     System     ");
    delay(2000);
    lcd.clear();
    lcd.setCursor(0,1);
    lcd.print("Adnan Mujawar");
    delay(2000);
          digitalWrite(buzzer, HIGH);
      delay(500);
      digitalWrite(buzzer, LOW);
  for(int i=1000;i<1000+records;i++)
  {
    if(EEPROM.read(i) == 0xff)
        EEPROM.write(i,0);
   }

    finger.begin(57600);
    Serial.begin(9600);
    lcd.clear();
    lcd.print("Finding Module");
    lcd.setCursor(0,1);
    delay(1000);
    if (finger.verifyPassword())
    {
      Serial.println("Found fingerprint sensor!");
      lcd.clear();
      lcd.print("Found Module ");
      delay(1000);
    }
    else
    {
    Serial.println("Did not find fingerprint sensor :(");
    lcd.clear();
    lcd.print("module not Found");
    lcd.setCursor(0,1);
    lcd.print("Check Connections");
    while (1);
    }

     if (! rtc.begin())
       Serial.println("Couldn't find RTC");

    // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));

    if (! rtc.isrunning())
    {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
       rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
    }
 lcd.setCursor(0,0);
 lcd.print("Press Match to ");
 lcd.setCursor(0,1);
 lcd.print("Start System");
 delay(2000);

 user1=EEPROM.read(1000);
  user2=EEPROM.read(1001);
   user3=EEPROM.read(1002); 
   user4=EEPROM.read(1003);
    user5=EEPROM.read(1004);
    lcd.clear();
    digitalWrite(indFinger, HIGH);
    
}

void loop()
{
    now = rtc.now();
    lcd.setCursor(0,0);
    lcd.print("Time->");
    lcd.print(now.hour(), DEC);
    lcd.print(':');
    lcd.print(now.minute(), DEC);
    lcd.print(':');
    lcd.print(now.second(), DEC);
    lcd.print("    ");
    lcd.setCursor(0,1);
    lcd.print("Date->");
    lcd.print(now.day(), DEC);
    lcd.print('/');
    lcd.print(now.month(), DEC);
    lcd.print('/');
    lcd.print(now.year(), DEC);
    lcd.print("     ");
    delay(500);
    lcd.clear();
    
    delay(500);
    
    int result=getFingerprintIDez();
    if(result>0)
    {
              digitalWrite(indFinger, LOW);
              digitalWrite(buzzer, HIGH);
              delay(100);
              digitalWrite(buzzer, LOW);
              lcd.clear();
              lcd.print("ID:");
              lcd.print(result);
              lcd.setCursor(0,1);
              lcd.print("Please Wait....");
              delay(1000);
              attendance(result);
              lcd.clear();
              lcd.print("Attendance ");
              lcd.setCursor(0,1);
              lcd.print("Registed");
              delay(1000);
        digitalWrite(indFinger, HIGH);
        return;
 }
 void checkKeys();
 delay(300);
}

//     dmyyhms - 7 bytes
void attendance(int id)
{
  int user=0,eepLoc=0;
  if(id == 1)
  {
    eepLoc=0;
    user=user1++;
  }
  else if(id == 2)
  {
    eepLoc=210;
    user=user2++;
  }
  else if(id == 3)
  {
    eepLoc=420;
    user=user3++;
  }
  else if(id == 4)
  {
    eepLoc=630;
    user=user4++;
  }
  /*else if(id == 5)   // fifth user
  {
    eepLoc=840;
    user=user5++;
  }*/
  else 
  return;
  
    int eepIndex=(user*7)+eepLoc;
    myFile.print(eepIndex++, now.hour());
    myFile.print(eepIndex++, now.minute());
    myFile.print(eepIndex++, now.second());
    myFile.print(eepIndex++, now.day());
    myFile.print(eepIndex++, now.month());
    myFile.print(eepIndex++, now.year()>>8 );
    myFile.print(eepIndex++, now.year());

    myFile.print(1000,user1);
    myFile.print(1001,user2);
    myFile.print(1002,user3);
    myFile.print(1003,user4);
  //  EEPROM.write(4,user5);   // figth user
    myFile.close();
}

void checkKeys()

{
    char key = keypad.getKey(); 
    if (key == 'A')
   {
    lcd.clear();
    lcd.print("Please Wait");
    delay(1000);
    while(key=='A');
    Enroll();
   }

   else if(key=='B') 
   {
    lcd.clear();
    lcd.print("Please Wait");
    delay(1000);
    delet();
   }
}

void Enroll()
{
   char key = keypad.getKey(); 
   int count=1;
   lcd.clear();
   lcd.print("Enter Finger ID:");

   while(1)
   {
    lcd.setCursor(0,1);
     lcd.print(count);
     if(key=='C')
     {
       count++;
       if(count>records)
       count=1;
       delay(500);
     }

     else if(key=='D')
     {
       count--;
       if(count<1)
       count=records;
       delay(500);
     }
     else if(key=='B')
     {
          id=count;
          getFingerprintEnroll();
          for(int i=0;i<records;i++)
          {
            if(EEPROM.read(i) != 0xff)
            {
              EEPROM.write(i, id);
              break;
            }
          }
          return;
     }

       else if(key=='A')
     {
          return;
     }
 }
}

void delet()
{
   char key = keypad.getKey(); 
   int count=1;
   lcd.clear();
   lcd.print("Enter Finger ID");

   while(1)
   {
    lcd.setCursor(0,1);
     lcd.print(count);
     if(key=='B')
     {
       count++;
       if(count>records)
       count=1;
       delay(500);
     }

     else if(key=='C')
     {
       count--;
       if(count<1)
       count=records;
       delay(500);
     }
     else if(key=='B')
     {
          id=count;
          deleteFingerprint(id);
          for(int i=0;i<records;i++)
          {
            if(EEPROM.read(i) == id)
            {
              EEPROM.write(i, 0xff);
              break;
            }
          }
          return;
     }

       else  if(key == 'A')
       
     {
          return;
     }
 }
}

uint8_t getFingerprintEnroll()
{
  int p = -1;
  lcd.clear();
  lcd.print("finger ID:");
  lcd.print(id);
  lcd.setCursor(0,1);
  lcd.print("Place Finger");
  delay(2000);
  while (p != FINGERPRINT_OK)
  {
    p = finger.getImage();
    switch (p)
    {
    case FINGERPRINT_OK:
      Serial.println("Image taken");
      lcd.clear();
      lcd.print("Image taken");
      break;
    case FINGERPRINT_NOFINGER:
      Serial.println("No Finger");
      lcd.clear();
      lcd.print("No Finger");
      break;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      lcd.clear();
      lcd.print("Comm Error");
      break;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
      lcd.clear();
      lcd.print("Imaging Error");
      break;
    default:
      Serial.println("Unknown error");
       lcd.clear();
      lcd.print("Unknown Error");
      break;
    }
  }

  // OK success!

  p = finger.image2Tz(1);
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      lcd.clear();
      lcd.print("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
       lcd.clear();
       lcd.print("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
            lcd.clear();
      lcd.print("Comm Error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
            lcd.clear();
      lcd.print("Feature Not Found");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
                  lcd.clear();
      lcd.print("Feature Not Found");
      return p;
    default:
      Serial.println("Unknown error");
                  lcd.clear();
      lcd.print("Unknown Error");
      return p;
  }

  Serial.println("Remove finger");
  lcd.clear();
  lcd.print("Remove Finger");
  delay(2000);
  p = 0;
  while (p != FINGERPRINT_NOFINGER) {
    p = finger.getImage();
  }
  Serial.print("ID "); Serial.println(id);
  p = -1;
  Serial.println("Place same finger again");
   lcd.clear();
      lcd.print("Place Finger");
      lcd.setCursor(0,1);
      lcd.print("   Again");
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
      return;
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
    lcd.print("Stored!");
    delay(2000);
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_BADLOCATION) {
    Serial.println("Could not store in that location");
    return p;
  } else if (p == FINGERPRINT_FLASHERR) {
    Serial.println("Error writing to flash");
    return p;
  }
  else {
    Serial.println("Unknown error");
    return p;
  }
}

int getFingerprintIDez()
{
  uint8_t p = finger.getImage();

  if (p != FINGERPRINT_OK)
  return -1;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)
  return -1;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)
  {
   lcd.clear();
   lcd.print("Finger Not Found");
   lcd.setCursor(0,1);
   lcd.print("Try Later");
   delay(2000);
  return -1;
  }
  // found a match!
  Serial.print("Found ID #");
  Serial.print(finger.fingerID);
  return finger.fingerID;
}

uint8_t deleteFingerprint(uint8_t id)
{
  uint8_t p = -1;
  lcd.clear();
  lcd.print("Please wait");
  p = finger.deleteModel(id);
  if (p == FINGERPRINT_OK)
  {
    Serial.println("Deleted!");
    lcd.clear();
    lcd.print("Figer Deleted");
    lcd.setCursor(0,1);
    lcd.print("Successfully");
    delay(1000);
  }

  else
  {
    Serial.print("Something Wrong");
    lcd.clear();
    lcd.print("Something Wrong");
    lcd.setCursor(0,1);
    lcd.print("Try Again Later");
    delay(2000);
    return p;
  }
}

void download(int eepIndex)
{
            
            if(EEPROM.read(eepIndex) != 0xff)
            {
              Serial.print("T->");
              if(EEPROM.read(eepIndex)<10)
              Serial.print('0');
              Serial.print(EEPROM.read(eepIndex++));
              Serial.print(':');  
              if(EEPROM.read(eepIndex)<10)
              Serial.print('0');
              Serial.print(EEPROM.read(eepIndex++));
              Serial.print(':'); 
              if(EEPROM.read(eepIndex)<10)
              Serial.print('0');
              Serial.print(EEPROM.read(eepIndex++));
              Serial.print("   D->");
              if(EEPROM.read(eepIndex)<10)
              Serial.print('0');
              Serial.print(EEPROM.read(eepIndex++));
              Serial.print('/');
              if(EEPROM.read(eepIndex)<10)
              Serial.print('0');           
              Serial.print(EEPROM.read(eepIndex++));
              Serial.print('/');            
              Serial.print(EEPROM.read(eepIndex++)<<8 | EEPROM.read(eepIndex++));
            }
            else
            {
               Serial.print("---------------------------");
            }

            Serial.print("         ");
}
