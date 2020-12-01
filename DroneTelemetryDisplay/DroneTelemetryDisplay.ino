//Developed by VIKRAM BALA, 2020. Contact: vikrambala2002@gmail.com. 
//Please contact if you wish to use for commercial purposes, and provide credit in any public usage.
//Credit can be provided with the following: "Vikram Bala, https://github.com/vbala29"

//THIS CODE IS INTENDED TO RUN ON AN ARDUINO UNO

#include <Stepper.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <math.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

String content;

double latitude;
double longitude;
double headingLook; 

 void setup() {
    pinMode(7, OUTPUT);
  pinMode(12, INPUT);
  pinMode(13, OUTPUT);
//  pinMode(2, INPUT);
  
  lcd.init();
  lcd.init();
  lcd.backlight();
  Serial.begin(115200);
  lcd.setCursor(0,0); 
  lcd.print("Vikram and Miles's      " );
  lcd.setCursor(0, 1);
  lcd.print("Drone Telemetry System          ");
  delay(1500); 
  lcd.setCursor(0,0); 
  lcd.print("Wait for green      ");
  lcd.setCursor(0,1);
  lcd.print("LED. Then press.             "); 
 }

 void loop() {
  digitalWrite(7, HIGH);
  delay(100);
  digitalWrite(7, LOW); 
  delay(100);
  digitalWrite(7, HIGH);
  delay(100);
  digitalWrite(7, LOW); 

while(Serial.available()){
  digitalWrite(7, LOW);
    content = Serial.readString();
        Serial.println(content); 
    digitalWrite(13, HIGH);
    delay(100);
    digitalWrite(13, LOW);
    delay(100);
     digitalWrite(13, HIGH);
    delay(100);
    digitalWrite(13, LOW);
    delay(100); 
    digitalWrite(13, HIGH);
    delay(100);
      digitalWrite(13, LOW);
} 

if(digitalRead(12) == HIGH){
      digitalWrite(7, LOW);
      lcd.clear();
      int ind1 = content.indexOf(',');
      String acx = content.substring(0, ind1); 
      int ind2 = content.indexOf(',', ind1 + 1);
      String acy = content.substring(ind1 + 1, ind2);
      int ind3 =  content.indexOf(',', ind2 + 1); 
      String acz = content.substring(ind2 + 1, ind3); 
      int ind4 =  content.indexOf(',', ind3 + 1);  
      String gyy = content.substring(ind3 + 1, ind4);
     lcd.print("Drone: DJISPARK            "); 
      lcd.setCursor(0, 1); 
     lcd.print("Retriving...                         ");

//---------
    int count = 0;
     while(count < 2){
     lcd.setCursor(0, 1); 
     lcd.print("AcY " + acy + " g             " );
     delay(1000);
     lcd.setCursor(0, 1);       
     lcd.print("AcX " + acx + " g            ");
     delay(1000);
     lcd.setCursor(0, 1); 
     lcd.print("AcZ " + acz + " g                   ");
     delay(1000);
     lcd.setCursor(0, 1); 
     lcd.print("GyY " + gyy + " d");
     delay(1000);
     count ++;
     }
     
   
    }

    
  

 }
