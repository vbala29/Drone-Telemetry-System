//Developed by VIKRAM BALA & MILES BATLEY, 2020. Contact: vikrambala2002@gmail.com. 
//Please contact if you wish to use for commercial purposes, and provide credit in any public usage.
//Credit can be provided with the following: "Vikram Bala, https://github.com/vbala29"

//Library used: https://github.com/DeanIsMe/SevSeg

#include "SevSeg.h"
SevSeg sevseg;
String content = "";

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
  byte numDigits = 4;  
  byte digitPins[] = {D1, D2, D3, D4};
  byte segmentPins[] = {pinA, pinB, pinC, pinD, pinE, pinF, pinG, A5};
  bool resistorsOnSegments = 0; 
  sevseg.begin(COMMON_CATHODE, numDigits, digitPins, segmentPins, resistorsOnSegments);
  sevseg.setBrightness(70);
   pinMode(pinA, OUTPUT);     
  pinMode(pinB, OUTPUT);     
  pinMode(pinC, OUTPUT);     
  pinMode(pinD, OUTPUT);     
  pinMode(pinE, OUTPUT);     
  pinMode(pinF, OUTPUT);     
  pinMode(pinG, OUTPUT); 
  pinMode(A5, OUTPUT);  
  pinMode(D1, OUTPUT);  
  pinMode(D2, OUTPUT);  
  pinMode(D3, OUTPUT);  
  pinMode(D4, OUTPUT);

     sevseg.setNumber(0000, 3);

 Serial.begin(115200);
while (!Serial) {
; // wait for serial port to connect. Needed for native USB port only
}

}

void loop() {
     sevseg.refreshDisplay();
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

  if ((abs(gyy.toInt())) >  100){
       String suffix =  gyy.substring(0, 4);
       sevseg.setNumber((abs((int)(suffix.toFloat())))*10, 1);
    //   Serial.println((abs((int)(suffix.toFloat())))*10); 
       sevseg.refreshDisplay();
    } else  if((abs(gyy.toInt())) > 10){
     String suffix =  gyy.substring(0, 4);
      sevseg.setNumber((abs((int)(suffix.toFloat())))*100, 2);
      sevseg.refreshDisplay();
    }  else {
       String suffix =  gyy.substring(0, 4);
       sevseg.setNumber((abs((int)(suffix.toFloat() * 1000))), 3);
   
    }
  }
   
}
