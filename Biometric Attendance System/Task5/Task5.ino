/*
                            *
                            * Project Name:   Biometric Attendance System
                            * Author List:    Adnan Mujawar
                            *     
                            * Filename:       Task:5 Sensors Initialization
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
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&fingerPrint);

uint8_t id;

#define buzzer 8
#define records 44  
#define indFinger 10
int user1,user2,user3,user4,user5,user6,user7,user8,user9,user10,user11,user12,user13,user14,user15,user16,user17,user18,user19,user20,user21,user22,user23,user24,user25,user26,user27,user28,user29,user30,user31,user32,user33,user34,user35,user36,user37,user38,user39,user40,user41,user42,user43,user44;
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
delay(1000);
  lcd.begin(20,4);
  Serial.begin(9600);
  pinMode(buzzer,OUTPUT);
  pinMode(indFinger, OUTPUT);
   
  keypad.setDebounceTime(200);
   {  lcd.clear();
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
      lcd.print("Module Found");
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
   
    {
       lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("A - Enroll");
    lcd.setCursor(0,1);
    lcd.print("B - up");  
    lcd.setCursor(0,2);
    lcd.print("C - Down");
    lcd.setCursor(0,3);
    lcd.print("D - More options");
    delay(1000);
    Serial.begin(9600);
    }
    }
  keypressed = keypad.getKey();
  if (keypressed =='A'){ 
   digitalWrite(buzzer, HIGH);
      delay(500);
      digitalWrite(buzzer, LOW);
      lcd.clear();
      lcd.print("Waiting...");
      lcd.setCursor(0,1);
      lcd.print("Data Downloading");
      Serial.println("Waiting...");
      Serial.println("Data Downloading");
      Serial.println();
      Serial.print("S.N.         ");
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
        eepIndex=(i*7);    //1
        download(eepIndex);
        eepIndex=(i*7)+210; //2
        download(eepIndex);
        eepIndex=(i*7)+420; //3
        download(eepIndex);
        eepIndex=(i*7)+630; //4
        download(eepIndex);
        eepIndex=(i*7)+840; //5
        download(eepIndex);
        eepIndex=(i*7)+1050; //6
        download(eepIndex);
        eepIndex=(i*7)+1260; //7
        download(eepIndex);
        eepIndex=(i*7)+1470; //8
        download(eepIndex);
        eepIndex=(i*7)+1680; //9
        download(eepIndex);
        eepIndex=(i*7)+1890; //10
        download(eepIndex);
        eepIndex=(i*7)+2100; //11
        download(eepIndex);
        eepIndex=(i*7)+2310; //12
        download(eepIndex);
        eepIndex=(i*7)+2520; //13
        download(eepIndex);
        eepIndex=(i*7)+2730; //14
        download(eepIndex);
        eepIndex=(i*7)+2940; //15
        download(eepIndex);
        eepIndex=(i*7)+3150; //16
        download(eepIndex);
        eepIndex=(i*7)+3360; //17
        download(eepIndex);
        eepIndex=(i*7)+3570; //18
        download(eepIndex);
        eepIndex=(i*7)+3780; //19
        download(eepIndex);
        eepIndex=(i*7)+3990; //20
        download(eepIndex);
        eepIndex=(i*7)+4200; //21
        download(eepIndex);
        eepIndex=(i*7)+4410; //22
        download(eepIndex);
        eepIndex=(i*7)+4620; //23
        download(eepIndex);
        eepIndex=(i*7)+4830; //24
        download(eepIndex);
        eepIndex=(i*7)+5040; //25
        download(eepIndex);
        eepIndex=(i*7)+5250; //26
        download(eepIndex);
        eepIndex=(i*7)+5460; //27
        download(eepIndex);
        eepIndex=(i*7)+5670; //28
        download(eepIndex);
        eepIndex=(i*7)+5880; //29
        download(eepIndex);
        eepIndex=(i*7)+6090; //30
        download(eepIndex);
        eepIndex=(i*7)+6300; //31
        download(eepIndex);
        eepIndex=(i*7)+6510; //32
        download(eepIndex);
        eepIndex=(i*7)+6720; //33
        download(eepIndex);
        eepIndex=(i*7)+6930; //34
        download(eepIndex);
        eepIndex=(i*7)+7140; //35
        download(eepIndex);
        eepIndex=(i*7)+7350; //36
        download(eepIndex);
        eepIndex=(i*7)+7560; //37
        download(eepIndex);
        eepIndex=(i*7)+7770; //38
        download(eepIndex);
        eepIndex=(i*7)+7980; //39
        download(eepIndex);
        eepIndex=(i*7)+8190; //40
        download(eepIndex);
        eepIndex=(i*7)+8400; //41
        download(eepIndex);
        eepIndex=(i*7)+8610; //42
        download(eepIndex);
        eepIndex=(i*7)+8820; //43
        download(eepIndex);
        eepIndex=(i*7)+9030; //44
        download(eepIndex);  //to add more use eepIndex=(i*7)+(n-1)*210;
        
        Serial.println();  
      }
  }
      if(keypressed == 'D'){
        lcd.clear();
      lcd.print("Waiting...");
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
      lcd.print("Module Found");
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
    }

 delay(2000);
 user1=EEPROM.read(1000); user2=EEPROM.read(1001); user3=EEPROM.read(1002); user4=EEPROM.read(1003);
 user5=EEPROM.read(1004); user6=EEPROM.read(1006); user7=EEPROM.read(1007); user8=EEPROM.read(1008);
 user9=EEPROM.read(1009); user10=EEPROM.read(1010); user11=EEPROM.read(1011);user12=EEPROM.read(1012);
 user13=EEPROM.read(1013);user14=EEPROM.read(1014); user15=EEPROM.read(1015);user16=EEPROM.read(1016);
 user17=EEPROM.read(1017);user18=EEPROM.read(1018);user19=EEPROM.read(1019);user20=EEPROM.read(1020);
 user21=EEPROM.read(1021);user22=EEPROM.read(1022);user23=EEPROM.read(1023);user24=EEPROM.read(1024);
 user25=EEPROM.read(1025);user26=EEPROM.read(1026);user27=EEPROM.read(1027);user28=EEPROM.read(1028);
 user29=EEPROM.read(1029);user30=EEPROM.read(1030);user31=EEPROM.read(1031);user32=EEPROM.read(1032);
 user33=EEPROM.read(1033);user34=EEPROM.read(1034);user35=EEPROM.read(1035);user36=EEPROM.read(1036);
 user37=EEPROM.read(1037);user38=EEPROM.read(1038);user39=EEPROM.read(1039);user40=EEPROM.read(1040);
 user41=EEPROM.read(1041);user42=EEPROM.read(1042);user43=EEPROM.read(1043);user44=EEPROM.read(1044);
    
    lcd.clear();
    digitalWrite(indFinger, HIGH);
    
}
    

void loop() {
  // put your main code here, to run repeatedly:
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
              lcd.print("Waiting...");
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
 checkKeys();
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
  else if(id == 5)  
  {
    eepLoc=840;
    user=user5++;
  }
  else if(id == 6)
  {
    eepLoc=1050;
    user=user6++;
  }
  else if(id == 7)
  {
    eepLoc=1260;
    user=user7++;
  }
  else if(id == 8)
  {
    eepLoc=1470;
    user=user8++;
  }
  else if(id == 9)
  {
    eepLoc=1680;
    user=user9++;
  }
  else if(id == 10)
  {
    eepLoc=1890;
    user=user10++;
  }
  else if(id == 11)
  {
    eepLoc=2100;
    user=user11++;
  }else if(id == 12)
  {
    eepLoc=2310;
    user=user12++;
  }
  else if(id == 13)
  {
    eepLoc=2520;
    user=user13++;
  }
  else if(id == 14)
  {
    eepLoc=2730;
    user=user14++;
  }
  else if(id == 15)
  {
    eepLoc=2940;
    user=user15++;
  }
  else if(id == 16)
  {
    eepLoc=3150;
    user=user16++;
  }
  else if(id == 17)
  {
    eepLoc=3360;
    user=user17++;
  }
  else if(id == 18)
  {
    eepLoc=3570;
    user=user18++;
  }
  else if(id == 19)
  {
    eepLoc=3780;
    user=user19++;
  }
  else if(id == 20)
  {
    eepLoc=3990;
    user=user20++;
  }
  else if(id == 21)
  {
    eepLoc=4200;
    user=user21++;
  }
  else if(id == 22)
  {
    eepLoc=4410;
    user=user22++;
  }
  else if(id == 23)
  {
    eepLoc=4620;
    user=user23++;
  }
  else if(id == 24)
  {
    eepLoc=4830;
    user=user24++;
  }
  else if(id == 25)
  {
    eepLoc=5040;
    user=user25++;
  }
  else if(id == 26)
  {
    eepLoc=5250;
    user=user26++;
  }
  else if(id == 27)
  {
    eepLoc=5460;
    user=user27++;
  }
  else if(id == 28)
  {
    eepLoc=5670;
    user=user28++;
  }
  else if(id == 29)
  {
    eepLoc=5880;
    user=user29++;
  }
  else if(id == 30)
  {
    eepLoc=6090;
    user=user30++;
  }
  else if(id == 31)
  {
    eepLoc=6300;
    user=user31++;
  }
  else if(id == 32)
  {
    eepLoc=6510;
    user=user32++;
  }
  else if(id == 33)
  {
    eepLoc=6720;
    user=user33++;
  }
  else if(id == 34)
  {
    eepLoc=6930;
    user=user34++;
  }
  else if(id == 35)
  {
    eepLoc=7140;
    user=user35++;
  }
  else if(id == 36)
  {
    eepLoc=7350;
    user=user36++;
  }
  else if(id == 37)
  {
    eepLoc=7560;
    user=user37++;
  }
  else if(id == 38)
  {
    eepLoc=7770;
    user=user38++;
  }
  else if(id == 39)
  {
    eepLoc=7980;
    user=user39++;
  }
  else if(id == 40)
  {
    eepLoc=8190;
    user=user40++;
  }
  else if(id == 41)
  {
    eepLoc=8400;
    user=user41++;
  }
  else if(id == 42)
  {
    eepLoc=8610;
    user=user42++;
  }
  else if(id == 43)
  {
    eepLoc=8820;
    user=user43++;
  }
  else if(id == 44)
  {
    eepLoc=9030;
    user=user44++;
  }
 
  else 
  return;
  
    int eepIndex=(user*7)+eepLoc;
    EEPROM.write(eepIndex++, now.hour());
    EEPROM.write(eepIndex++, now.minute());
    EEPROM.write(eepIndex++, now.second());
    EEPROM.write(eepIndex++, now.day());
    EEPROM.write(eepIndex++, now.month());
    EEPROM.write(eepIndex++, now.year()>>8 );
    EEPROM.write(eepIndex++, now.year());
    EEPROM.write(1000,user1);
    EEPROM.write(1001,user2);
    EEPROM.write(1002,user3);
    EEPROM.write(1003,user4);
    EEPROM.write(1004,user5);EEPROM.write(1005,user6);EEPROM.write(1006,user7);EEPROM.write(1007,user8);
    EEPROM.write(1008,user9);EEPROM.write(1009,user10);EEPROM.write(1010,user11);EEPROM.write(1011,user12);
    EEPROM.write(1012,user13);EEPROM.write(1013,user14);EEPROM.write(1014,user15);EEPROM.write(1015,user16);
    EEPROM.write(1016,user17);EEPROM.write(1017,user18);EEPROM.write(1018,user19);EEPROM.write(1019,user20);
    EEPROM.write(1020,user21);EEPROM.write(1021,user22);EEPROM.write(1022,user23);EEPROM.write(1023,user24);
    EEPROM.write(1024,user25);EEPROM.write(1025,user26);EEPROM.write(1026,user27);EEPROM.write(1027,user28);
    EEPROM.write(1028,user29);EEPROM.write(1029,user30);EEPROM.write(1030,user31);EEPROM.write(1031,user32);
    EEPROM.write(1032,user33);EEPROM.write(1033,user34);EEPROM.write(1034,user35);EEPROM.write(1035,user36);
    EEPROM.write(1036,user37);EEPROM.write(1037,user38);EEPROM.write(1038,user39);EEPROM.write(1039,user40);
    EEPROM.write(1040,user41);EEPROM.write(1041,user42);EEPROM.write(1042,user43);EEPROM.write(1043,user44);
}
void checkKeys()
{
   if(keypressed =='A')
   {
    lcd.clear();
    lcd.print("Waiting...");
    delay(1000);
    while(keypressed =='A');
    Enroll();
   }
   else if(keypressed =='D')
   {
    lcd.clear();
    lcd.print("Waiting...");
    delay(1000);
    delet();
   }
}
void Enroll()
{
   int count=1;
   lcd.clear();
   lcd.print("Enter Finger ID:");
   while(1)
   {
    lcd.setCursor(0,1);
     lcd.print(count);
     if(keypressed =='B')
     {
       count++;
       if(count>records)
       count=1;
       delay(500);
     }
     else if(keypressed =='C')
     {
       count--;
       if(count<1)
       count=records;
       delay(500);
     }
     else if(keypressed =='D')
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
       else if(keypressed =='A')
     {
          return;
     }
 }
}
//Function To delete Existing User
void delet()
{
   int count=1;
   lcd.clear();
   lcd.print("Enter Finger ID");
   while(1)
   {
    lcd.setCursor(0,1);
     lcd.print(count);
     if(keypressed =='B')
     {
       count++;
       if(count>records)
       count=1;
       delay(500);
     }
     else if(keypressed =='C')
     {
       count--;
       if(count<1)
       count=records;
       delay(500);
     }
     else if(keypressed =='D')
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
       else if(keypressed =='A')
     {
          return;
     }
 }
}
//Funbction to convert finger print image to templete
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
//Function to compare finger print image with stored IDs for matching
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
//Function for Download the Data fro EEPROM to Serial Monitor
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
