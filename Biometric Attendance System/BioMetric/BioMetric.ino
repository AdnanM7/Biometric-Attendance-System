/*
                            *
                            * Project Name:   BioMetric Attendance System 
                            * Author List:    Adnan Mujawar
                            *     
                            * Filename:       BioMetric.ino
                            *
                            */
String password="1234";
String tempPassword;
boolean activated = false;
boolean TakingAttendance;
boolean MarkingAttendance = false;
boolean AdminMenuActivated = false;
boolean enteredPassword;
boolean passChangeMode = false;
boolean passChanged = false;
int checkAttendance;
int screenOffMsg =0;

#include<LiquidCrystal.h>
LiquidCrystal lcd(12,13,5,4,3,2);
#include <SoftwareSerial.h>
SoftwareSerial fingerPrint(10,11);
#include <Wire.h>
#include <Keypad.h>
#include "Adafruit_Fingerprint.h"
uint8_t id;
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&fingerPrint);
SoftwareSerial mySerial(10, 11);
#include <Keypad.h>

float userset = 0;



const byte ROWS = 4;
const byte COLS = 4;
char keypressed;
char Mykeys;
char fieldKeys;
char divKeys;
char optionKeys;
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
#define indFinger 10
int user1,user2,user3,user4,user5;

void setup()
{
    delay(1000);
    lcd.begin(20,4);
    Serial.begin(9600);
     pinMode(buzzer, OUTPUT); 
     
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("MCOE Project Libra ");
    lcd.setCursor(0,1);
    lcd.print("A Biometric Based");
    lcd.setCursor(0,2);
    lcd.print("Student Attendance");
    lcd.setCursor(0,3);
    lcd.print("      System     ");
    delay(6000);
    lcd.clear();
    lcd.print("An Initiative of:");
    lcd.setCursor(0,1);
    lcd.print("Adnan Mujawar");
    delay(2000);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("A - TakeAttendance");
    lcd.setCursor(0,1);
    lcd.print("B - Admin Menu");
    lcd.setCursor(0,2);
    lcd.print("C - More Options");
    lcd.setCursor(0,3);
    lcd.print("D - Shutdown");
    Serial.begin(9600);
  while (!Serial);  // For Yun/Leo/Micro/Zero/...
  delay(100);
  Serial.println("\n\nAdafruit Fingerprint sensor enrollment");

  // set the data rate for the sensor serial port
  finger.begin(57600);
  
  if (finger.verifyPassword()) {
    Serial.println("Found fingerprint sensor!");
  } else {
    Serial.println("Did not find fingerprint sensor :(");
    while (1) { delay(1); }
  }
}
uint8_t readnumber(void) {
  uint8_t num = 0;
  
  while (num == 0) {
    while (! Serial.available());
    num = Serial.parseInt();
  }
  return num;
}
void loop(){
   keypressed = keypad.getKey();
  if (keypressed =='A'){ //if A is Pressed,start marking the attendance
    digitalWrite(buzzer, HIGH);
      delay(500);
      digitalWrite(buzzer, LOW);
      Serial.println("Ready to enroll a fingerprint!");
  Serial.println("Please type in the ID # (from 1 to 127) you want to save this finger as...");
  id = readnumber();
  if (id == 0) {// ID #0 not allowed, try again!
     return;
  }
  Serial.print("Enrolling ID #");
  Serial.println(id);
  
  while (!  getFingerprintEnroll() ); 
 }
  
 
 
 else if (keypressed =='B'){//admin wala jhanjhat
    digitalWrite(buzzer, HIGH);
      delay(500);
      digitalWrite(buzzer, LOW);
      int k=5;
      tempPassword = "";
      activated = true;
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print(" ENTER ");
      lcd.setCursor(0,1);
      lcd.print("Pass>");
          while(activated) {
          keypressed = keypad.getKey();
          if (keypressed != NO_KEY){
            if (keypressed == '0' || keypressed == '1' || keypressed == '2' || keypressed == '3' ||
                keypressed == '4' || keypressed == '5' || keypressed == '6' || keypressed == '7' ||
                keypressed == '8' || keypressed == '9' ) {
              tempPassword += keypressed;
              lcd.setCursor(k,1);
              lcd.print("*");
              k++;
            }
          }
          if (k > 9 || keypressed == '#') {
            tempPassword = "";
            k=5;
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print(" ENTER ");
            lcd.setCursor(0,1);
            lcd.print("Pass>");
          }
          if ( keypressed == '*') {
            if ( tempPassword == password ) {
              activated = false;
               AdminMenuActivated= false;
               digitalWrite(buzzer, HIGH);
               delay(500);
               digitalWrite(buzzer, LOW);
              screenOffMsg == 1; 
            }
            else if (tempPassword != password) {
              lcd.setCursor(0,1);
              lcd.print("Wrong! Try Again");
              delay(2000);
              lcd.clear();
              lcd.setCursor(0,0);
              lcd.print(" ENTER ");
              lcd.setCursor(0,1);
              lcd.print("Pass>");
            }
          }    
        }
    
    
if (AdminMenuActivated = true){
  
  digitalWrite(buzzer, HIGH);
  delay(500);
  digitalWrite(buzzer, LOW);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("A: Enroll Student");
  lcd.setCursor(0,1);
  lcd.print("B: Delete Student");
  lcd.setCursor(0,2);
  lcd.print("C: Create List");
  lcd.setCursor(0,3);
  lcd.print("D: Return");
 
  Mykeys = keypad.getKey();
  if (Mykeys == 'A') {  // Enroll key is pressed and stream menu is opened
    
    
    digitalWrite(buzzer, HIGH);
      delay(500);
      digitalWrite(buzzer, LOW);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("A: MECH");
      lcd.setCursor(0,1);
      lcd.print("B: ELEC");
      lcd.setCursor(0,2);
      lcd.print("C: E&TC");
      lcd.setCursor(0,3);
      lcd.print("D: IT");
      lcd.setCursor(10,0);
      lcd.print("#: CS");
    
    fieldKeys = keypad.getKey();  
      if  (fieldKeys == "A") {
        if   (screenOffMsg == 3) {

          digitalWrite(buzzer, HIGH);
          delay(500);
          digitalWrite(buzzer, LOW);
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("A: DivA");
          lcd.setCursor(0,1);
          lcd.print("B: DivB");
          lcd.setCursor(0,2);
          lcd.print("C: DivC");
          
        }
        }
        else if (fieldKeys == "B")  {
          if  (screenOffMsg == 4){
          digitalWrite(buzzer,HIGH);
          delay(500);
          digitalWrite(buzzer,LOW);
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("A: DivD");
          lcd.setCursor(0,1);
          lcd.print("B: DivE");
          }
        }
        else if (fieldKeys == "C")  {
          if  (screenOffMsg == 5){
             digitalWrite(buzzer,HIGH);
          delay(500);
          digitalWrite(buzzer,LOW);
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("A: DivF");
          lcd.setCursor(0,1);
          lcd.print("B: DivG");
           }
        }
        else if (fieldKeys == "D")  {
          if  (screenOffMsg == 6)  {
             digitalWrite(buzzer,HIGH);
          delay(500);
          digitalWrite(buzzer,LOW);
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("A: DivJ");
          lcd.setCursor(0,1);
          lcd.print("B: DivK");
          }
        }
        else  (fieldKeys == "#"); {
          if  (screenOffMsg == 7)  {
             digitalWrite(buzzer,HIGH);
          delay(500);
          digitalWrite(buzzer,LOW);
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("A: DivH");
          lcd.setCursor(0,1);
          lcd.print("B: DivL");
          }
        }
    }
    
  else if (Mykeys == "B")  { //DELETE KEY IS PRESSED FOR DELETING DATA
       if   (screenOffMsg == 8) {
    
    digitalWrite(buzzer, HIGH);
      delay(500);
      digitalWrite(buzzer, LOW);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("A: MECH");
      lcd.setCursor(0,1);
      lcd.print("B: ELEC");
      lcd.setCursor(0,2);
      lcd.print("C: E&TC");
      lcd.setCursor(0,3);
      lcd.print("D: IT");
      lcd.setCursor(10,0);
      lcd.print("#: CS");
      lcd.setCursor(10,1);
      lcd.print("*: BACK");
    }
    fieldKeys = keypad.getKey(); 
      if  (fieldKeys == "A") {
        if   (screenOffMsg == 9) {

          digitalWrite(buzzer, HIGH);
          delay(500);
          digitalWrite(buzzer, LOW);
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("A: DivA");
          lcd.setCursor(0,1);
          lcd.print("B: DivB");
          lcd.setCursor(0,2);
          lcd.print("C: DivC");
          
        }
        }
        else if (fieldKeys == "B")  {
          if  (screenOffMsg == 10){
          digitalWrite(buzzer,HIGH);
          delay(500);
          digitalWrite(buzzer,LOW);
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("A: DivD");
          lcd.setCursor(0,1);
          lcd.print("B: DivE");
          }
        }
        else if (fieldKeys == "C")  {
          if  (screenOffMsg == 11){
             digitalWrite(buzzer,HIGH);
          delay(500);
          digitalWrite(buzzer,LOW);
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("A: DivF");
          lcd.setCursor(0,1);
          lcd.print("B: DivG");
           }
        }
        
        else if (fieldKeys == "D")  {
          if  (screenOffMsg == 12)  {
             digitalWrite(buzzer,HIGH);
          delay(500);
          digitalWrite(buzzer,LOW);
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("A: DivJ");
          lcd.setCursor(0,1);
          lcd.print("B: DivK");
          }
        }
        else if (fieldKeys == "#"); {
          if  (screenOffMsg == 13)  {
             digitalWrite(buzzer,HIGH);
          delay(500);
          digitalWrite(buzzer,LOW);
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("A: DivH");
          lcd.setCursor(0,1);
          lcd.print("B: DivL");
          }
        }
  }
  else if (Mykeys == "C")  {  //creation of Excel data sheet
    
  }
  else (Mykeys == "D"); {  //RETURNING TO MAIN MENU
   (!MarkingAttendance);
 }
   
  }
  else if (!AdminMenuActivated) {
          lcd.clear();
      int i=1;
      tone(buzzer, 2000, 100);
      tempPassword = "";
      lcd.setCursor(0,0);
      lcd.print("Current Password");
      lcd.setCursor(0,1);
      lcd.print(">");
      passChangeMode = true;
      passChanged = true;   
      while(passChanged) {      
      keypressed = keypad.getKey();
      if (keypressed != NO_KEY){
        if (keypressed == '0' || keypressed == '1' || keypressed == '2' || keypressed == '3' ||
            keypressed == '4' || keypressed == '5' || keypressed == '6' || keypressed == '7' ||
            keypressed == '8' || keypressed == '9' ) {
         tempPassword += keypressed;
         lcd.setCursor(i,1);
         lcd.print("*");
         i++;
         tone(buzzer, 2000, 100);
        }
      }
      if (i > 5 || keypressed == '#') {
        tempPassword = "";
        i=1;
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Current Password");
        lcd.setCursor(0,1);
        lcd.print(">"); 
      }
      if ( keypressed == '*') {
        i=1;
        tone(buzzer, 2000, 100);
        if (password == tempPassword) {
          tempPassword="";
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Set New Password");
          lcd.setCursor(0,1);
          lcd.print(">");
          while(passChangeMode) {
            keypressed = keypad.getKey();
            if (keypressed != NO_KEY){
              if (keypressed == '0' || keypressed == '1' || keypressed == '2' || keypressed == '3' ||
                  keypressed == '4' || keypressed == '5' || keypressed == '6' || keypressed == '7' ||
                  keypressed == '8' || keypressed == '9' ) {
                tempPassword += keypressed;
                lcd.setCursor(i,1);
                lcd.print("*");
                i++;
                tone(buzzer, 2000, 100);
              }
            }
            if (i > 5 || keypressed == '#') {
              tempPassword = "";
              i=1;
              tone(buzzer, 2000, 100);
              lcd.clear();
              lcd.setCursor(0,0);
              lcd.print("Set New Password");
              lcd.setCursor(0,1);
              lcd.print(">");
            }
            if ( keypressed == '*') {
              i=1;
              tone(buzzer, 2000, 100);
              password = tempPassword;
              passChangeMode = false;
              passChanged = false;
              screenOffMsg = 0;
            }            
          }
        }
      }
    }
  }
  }
  else if (keypressed =='C')  { // MoreOptions menu giving more functionality to the system
     digitalWrite(buzzer, HIGH);
      delay(500);
      digitalWrite(buzzer, LOW);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("   MORE OPTIONS   ");
      lcd.setCursor(0,1);
      lcd.print("A: Battery Status");
      lcd.setCursor(0,2);
      lcd.print("B: Check Storage");
      lcd.setCursor(0,3);
      lcd.print("C: Return");
      
      optionKeys= keypad.getKey();
      if (optionKeys == "A"){  // battery indicator program
        
      }
      else if (optionKeys == "B"){  // storage indication program
        
      }
      else if (optionKeys == "C") { // Return back to main menu
        (!MarkingAttendance == true);
        (screenOffMsg == 0);
      }}
      else if (keypressed == 'D') {//shutdown the system
          digitalWrite(buzzer, HIGH);
      delay(500);
      digitalWrite(buzzer, LOW);
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
int              attendance(result);
              lcd.clear();
              lcd.print("Attendance ");
              lcd.setCursor(0,1);
              lcd.print("Registed");
              delay(1000);
        digitalWrite(indFinger, HIGH);
        return;
        delay(3000);
       
 }
      }
      
      
      
  }

uint8_t getFingerprintEnroll() {

  int p = -1;
  Serial.print("Waiting for valid finger to enroll as #"); Serial.println(id);
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
  delay(2000);
  p = 0;
  while (p != FINGERPRINT_NOFINGER) {
    p = finger.getImage();
  }
  Serial.print("ID "); Serial.println(id);
  p = -1;
  Serial.println("Place same finger again");
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
  
