/*
                            *
                            * Project Name:   Biometric Attendance System
                            * Author List:    Adnan Mujawar
                            *     
                            * Filename:       Task3: Keypad and user initialization  
                            * Functions:    
                            * Global Variables: 
                            *
                            */
// the real initiative is to have two menus of A, B, C, D and * is to enter and # is to exit
#include <LiquidCrystal_I2C.h>
#include<LiquidCrystal.h> // includes the lcd library
LiquidCrystal lcd(12,13,5,4,3,2);
#include <SoftwareSerial.h>
SoftwareSerial fingerPrint(10,11);
#include <Wire.h>

#define buzzer 8
#define records 4  // 5 for 5 user
#define indFinger 10
int user1,user2,user3,user4,user5;
int checkAttendance;
int screenOffMsg =0;
String password="1234";
String tempPassword;
boolean activated = false;
boolean TakingAttendance;
boolean MarkingAttendance = false;
boolean AdminMenuActivated = false;
boolean enteredPassword;
boolean passChangeMode = false;
boolean passChanged = false;
boolean EnrollId;
boolean IdEnrollMode = false;
boolean DeleteId;
boolean IdDeleteMode = false;



//constants for LEDs
int greenLED = 6; 
int redLED =  7;
int orangeLED= 14;

//RTC stuff
#include "RTClib.h"
RTC_DS1307 rtc;

#include "Adafruit_Fingerprint.h"
uint8_t id;
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&fingerPrint)


#include <Keypad.h>
//define the keypad
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
DateTime now;

void setup() {
  lcd.begin(20,4);

 //SETUP AND TURN OFF LED AND BUZZER
  pinMode(buzzer, OUTPUT); 
  pinMode(greenLED, OUTPUT);
  pinMode(orangeLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  digitalWrite(greenLED, LOW);
  digitalWrite(orangeLED, LOW);
  digitalWrite(redLED, LOW);
  keypad.setDebounceTime(20);

  if (finger.verifyPassword()) { // fingerprint serial discrimination
    Serial.println("Found fingerprint sensor!");
  } else {
    Serial.println("Did not find fingerprint sensor :(");
    while (1);
  }

  
 {  lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(" MCOE Project Libra ");
    lcd.setCursor(0,1);
    lcd.print(" A Biometric Based");
    lcd.setCursor(0,2);
    lcd.print(" Student Attendance");
    lcd.setCursor(0,3);
    lcd.print("      System     ");
    delay(4000);
    lcd.clear();
    lcd.print("An Initiative of:");
    lcd.setCursor(0,1);
    lcd.print("Adnan Mujawar");
    delay(2000);
 }
}
 
void loop(){
if (MarkingAttendance)  {
   finger.begin(57600);
   digitalWrite(indFinger, HIGH);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Place Your Finger");
  lcd.setCursor(0,1);
}
if (!MarkingAttendance)  {
  if  (screenOffMsg == 0 ) {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("A - TakeAttendance");
    lcd.setCursor(0,1);
    lcd.print("B - Admin Menu");
    lcd.setCursor(0,2);
    lcd.print("C - More Options");
    lcd.setCursor(0,3);
    lcd.print("D - Shutdown");
  }
   keypressed = keypad.getKey();
  if (keypressed =='A'){ //if A is Pressed,start marking the attendance
    digitalWrite(buzzer, HIGH);
      delay(500);
      digitalWrite(buzzer, LOW);
      finger.begin(57600);
      digitalWrite(indFinger, HIGH);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Place Your Finger");
  lcd.setCursor(0,1);
 }
 else if (keypressed =="B"){//admin wala jhanjhat
   
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
    
    
if (AdminMenuActivated == true){
  if   (screenOffMsg == 1)  {
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
 }
  Mykeys = keypad.getKey();
  if (Mykeys == "A") {  // Enroll key is pressed and stream menu is opened
    if   (screenOffMsg == 2) {
    
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
    }
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
        else  (fieldKeys == "#"); {
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
   (!MarkingAttendance == true);
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
  else if (keypressed =="C")  { // MoreOptions menu giving more functionality to the system
    if(screenOffMsg == 14)  {
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
      }
      optionKeys= keypad.getKey();
      if (optionKeys == "A"){  // battery indicator program
        
      }
      else if (optionKeys == "B"){  // storage indication program
        
      }
      else if (optionKeys == "C") { // Return back to main menu
        (!MarkingAttendance == true);
        (screenOffMsg == 0);
      }
      
  }
  
}

  
   if (! rtc.begin())//rtc setup.
       Serial.println("Couldn't find RTC");

      if (! rtc.isrunning())
    {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
       rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
    }

   now = rtc.now();
    lcd.setCursor(0,0);
    lcd.print("T");
    lcd.print(now.hour(), DEC);
    lcd.print(':');
    lcd.print(now.minute(), DEC);
    lcd.print(':');
    lcd.print(now.second(), DEC);
    lcd.print("    ");
    lcd.setCursor(0,1);
    lcd.print("D");
    lcd.print(now.day(), DEC);
    lcd.print('/');
    lcd.print(now.month(), DEC);
    lcd.print('/');
    lcd.print(now.year(), DEC);
    lcd.print("     ");
    delay(50000);
}
      
    
