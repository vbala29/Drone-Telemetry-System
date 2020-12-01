//Developed by VIKRAM BALA & MILES BATLEY, 2020. Contact: vikrambala2002@gmail.com. 
//Please contact if you wish to use for commercial purposes, and provide credit in any public usage.
//Credit can be provided with the following: "Vikram Bala, https://github.com/vbala29"

//THIS CODE IS INTENDED TO RUN ON AN ARDUINO UNO
#include <LiquidCrystal.h>
#include "SevSeg.h"


LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
//7 = bottom //8 left bottom //6 left top //13 top //A0 top rght //

int pinA = 10;
int pinB = 6;
int pinC = A2;
int pinD = A3;
int pinE = A4;
int pinF = 9;
int pinG = A1;
int D1 = 13;
int D2 = 8;
int D3 = 7;
int D4 = A0;




void setup() {
 pinMode(pinA, OUTPUT);     
  pinMode(pinB, OUTPUT);     
  pinMode(pinC, OUTPUT);     
  pinMode(pinD, OUTPUT);     
  pinMode(pinE, OUTPUT);     
  pinMode(pinF, OUTPUT);     
  pinMode(pinG, OUTPUT);   
  pinMode(D1, OUTPUT);  
  pinMode(D2, OUTPUT);  
  pinMode(D3, OUTPUT);  
  pinMode(D4, OUTPUT);

    
digitalWrite(D1, HIGH);
digitalWrite(D2, HIGH);
digitalWrite(D3, HIGH);
digitalWrite(D4, HIGH);


 Serial.begin(115200);
while (!Serial) {
; // wait for serial port to connect. Needed for native USB port only
}
 
lcd.clear();
// set up the LCD's number of columns and rows:
lcd.begin(16, 2);


}

String content = "";
char character; 
int num;


void loop() {
  unsigned long currentMillis = millis();
  lcd.setCursor(0, 0); 
  
  if (Serial.available()) {
    content = Serial.readString();
    Serial.println(content); 
    int ind1 = content.indexOf(',');
    String acx = content.substring(0, ind1); 
    int ind2 = content.indexOf(',', ind1 + 1);
    String acy = content.substring(ind1 + 1, ind2);
    int ind3 =  content.indexOf(',', ind2 + 1); 
    String acz = content.substring(ind2 + 1, ind3);
    int ind4 =  content.indexOf(',', ind3 + 1);  
    String gyy = content.substring(ind3 + 1, ind4);
    Serial.println("Acx = " + acx + " Acy = "  + acy + " Acz = " + acz + " Gyy = " + gyy);
  if(abs(gyy.toInt()) < 10){
    pickDigit(1);
    switch(abs(gyy.toInt())){
       case 0:
        zero();
        break;
      case 1:
        one();
        break;
      case 2:
        two();
        break;
      case 3: 
        three();
        break;
      case 4:
        four();
        break;
       case 5:
        five();
        break;
       case 6:
        six();
        break;
       case 7:
        seven();
        break;
       case 8:
        eight();
        break;
       case 9:
        nine();
        break;
       default:
        break;
    }
  } else {
    pickDigit(2); 
    switch(abs(gyy.toInt() / 10)){
      case 0:
        zero();
        break;
      case 1:
        one(); 
        break;
      case 2:
        two();
        break;
      case 3: 
        three();
        break;
      case 4:
        four();
        break;
       case 5:
        five();
        break;
       case 6:
        six();
        break;
       case 7:
        seven();
        break;
       case 8:
        eight();
        break;
       case 9:
        nine();
        break;
       default:
        break;
    }
  }
     lcd.clear();
     
//     DISPLAY VALUES ON BACKEND LCD - TESTING ONLY
     lcd.print("Acx = " + acx);
     lcd.setCursor(0, 1); 
     
     lcd.print("Acy = " + acy);
     delay(500);
     
     lcd.setCursor(0, 0);
     
     lcd.print("Acz = " + acz);
     lcd.setCursor(0, 1);
     lcd.print("Gyy = " + gyy);
     delay(500);

    

       
     }
    
    
}
void zero(){
  
 digitalWrite(pinA, HIGH);   
  digitalWrite(pinB,  HIGH);   
  digitalWrite(pinC, HIGH);   
  digitalWrite(pinD, HIGH);   
  digitalWrite(pinE, HIGH);   
  digitalWrite(pinF, HIGH);   
  digitalWrite(pinG, LOW);     
}


void one(){
  
 digitalWrite(pinA, LOW);   
  digitalWrite(pinB,  LOW);   
  digitalWrite(pinC, LOW);   
  digitalWrite(pinD, LOW);   
  digitalWrite(pinE, HIGH);   
  digitalWrite(pinF, HIGH);   
  digitalWrite(pinG, LOW);     
}

void two(){
  
 digitalWrite(pinA, HIGH);   
  digitalWrite(pinB,  HIGH);   
  digitalWrite(pinC, LOW);   
  digitalWrite(pinD, HIGH);   
  digitalWrite(pinE, HIGH);   
  digitalWrite(pinF, LOW);   
  digitalWrite(pinG, HIGH);     
}


void three(){
  
 digitalWrite(pinA, HIGH);   
  digitalWrite(pinB,  HIGH);   
  digitalWrite(pinC, HIGH);   
  digitalWrite(pinD, HIGH);   
  digitalWrite(pinE, LOW);   
  digitalWrite(pinF, LOW);   
  digitalWrite(pinG, HIGH);     
}


void four(){
//4
 digitalWrite(pinA, LOW);   
  digitalWrite(pinB, HIGH);   
  digitalWrite(pinC, HIGH);   
  digitalWrite(pinD, LOW);   
  digitalWrite(pinE, LOW);   
  digitalWrite(pinF, HIGH);   
  digitalWrite(pinG, HIGH);     
}

void five(){

 digitalWrite(pinA, HIGH);   
  digitalWrite(pinB, LOW);   
  digitalWrite(pinC, HIGH);   
  digitalWrite(pinD, HIGH);   
  digitalWrite(pinE, LOW);   
  digitalWrite(pinF, HIGH);   
  digitalWrite(pinG, HIGH);     
}

void six(){

 digitalWrite(pinA, HIGH);   
  digitalWrite(pinB, LOW);   
  digitalWrite(pinC, HIGH);   
  digitalWrite(pinD, HIGH);   
  digitalWrite(pinE, HIGH);   
  digitalWrite(pinF, HIGH);   
  digitalWrite(pinG, HIGH);     
}

void seven(){

 digitalWrite(pinA, HIGH);   
  digitalWrite(pinB, HIGH);   
  digitalWrite(pinC, HIGH);   
  digitalWrite(pinD, LOW);   
  digitalWrite(pinE, LOW);   
  digitalWrite(pinF, LOW);   
  digitalWrite(pinG, LOW);     
}



void eight(){

 digitalWrite(pinA, HIGH);   
  digitalWrite(pinB, HIGH);   
  digitalWrite(pinC, HIGH);   
  digitalWrite(pinD, HIGH);   
  digitalWrite(pinE, HIGH);   
  digitalWrite(pinF, HIGH);   
  digitalWrite(pinG, HIGH);     
}


void nine(){

 digitalWrite(pinA, HIGH);   
  digitalWrite(pinB, HIGH);   
  digitalWrite(pinC, HIGH);   
  digitalWrite(pinD, LOW);   
  digitalWrite(pinE, LOW);   
  digitalWrite(pinF, HIGH);   
  digitalWrite(pinG, HIGH);     
}

void g(){

 digitalWrite(pinA, HIGH);   
  digitalWrite(pinB, HIGH);   
  digitalWrite(pinC, HIGH);   
  digitalWrite(pinD, HIGH);   
  digitalWrite(pinE, LOW);   
  digitalWrite(pinF, HIGH);   
  digitalWrite(pinG, HIGH);     
}

//https://osoyoo.com/2017/08/08/arduino-lesson-4-digit-7-segment-led-display/
void pickDigit(int x) //light up a 7-segment display
{
  //The 7-segment LED display is a common-cathode one. So also use digitalWrite to  set d1 as high and the LED will go out
  digitalWrite(D1, HIGH);
  digitalWrite(D2, HIGH);
  digitalWrite(D3, HIGH);
  digitalWrite(D4, HIGH);

  switch(x)
  {
    case 0: 
    digitalWrite(D1, LOW);//Light d1 up 
    break;
    case 1: 
    digitalWrite(D2, LOW); //Light d2 up 
    break;
    case 2: 
    digitalWrite(D3, LOW); //Light d3 up 
    break;
    default: 
    digitalWrite(D4, LOW); //Light d4 up 
    break;
  }
}


 
