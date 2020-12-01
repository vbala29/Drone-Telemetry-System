//Developed by VIKRAM BALA & MILES BATLEY, 2020. Contact: vikrambala2002@gmail.com. 
//Please contact if you wish to use for commercial purposes, and provide credit in any public usage.
//Credit can be provided with the following: "Vikram Bala, https://github.com/vbala29"

/*PART OF THIS CODE IS ATTRIBUTED TO RUI SANTOS, SEE HIS COPYRIGHT GRANT BELOW
  Rui Santos
  Complete project details at Complete project details at https://RandomNerdTutorials.com/esp8266-nodemcu-http-get-post-arduino/

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*/

//THIS CODE IS INTENDED TO RUN ON AN ESP8266 NODE MCU


#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h> 
#include <Arduino_JSON.h>
#include <SoftwareSerial.h>

const char* ssid = "MERIT6";
const char* password = "*Putnam98#Zulu";

const char* serverNameAcx = "http://io.adafruit.com/api/v2/vbala20/feeds/acx?x-aio-key="; // REDCATED KEY
const char* serverNameAcy = "http://io.adafruit.com/api/v2/vbala20/feeds/acy?x-aio-key="; // REDCATED KEY 
const char* serverNameAcz = "http://io.adafruit.com/api/v2/vbala20/feeds/acz?x-aio-key="; // REDCATED KEY
const char* serverNameGyy = "http://io.adafruit.com/api/v2/vbala20/feeds/gyy?x-aio-key="; // REDCATED KEY

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastTime = 0;
// Timer set to 10 minutes (600000)
//unsigned long timerDelay = 600000;
// Set timer to 5 seconds (5000)
unsigned long timerDelay = 5000;

String sensorReadings;
float sensorReadingsArr[3];

void setup() {
  Serial.begin(115200);
  Serial1.begin(115200); //For sending data to the arduino

  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
 
  Serial.println("Timer set to 5 seconds (timerDelay variable), it will take 5 seconds before publishing the first reading.");
}

void loop() {
  //Send an HTTP POST request every 10 minutes
  if ((millis() - lastTime) > timerDelay) {
    //Check WiFi connection status
    if(WiFi.status()== WL_CONNECTED){
              
      String acx = httpGETRequest(serverNameAcx);
      //Serial.println(acx);
      
      int ind1 = acx.indexOf('}');
      int ind2 = acx.indexOf('_', ind1); //takes you to unit_type in the JSON 
      int ind3 = acx.indexOf('v', ind2); //takes you to last_v in the JSON
      int ind4 = acx.indexOf(':', ind3); //takes you to right before "number goes here"
      int ind5 = acx.indexOf(',', ind4); //takes you to comma after "number goes here",
      String acxValue = acx.substring(ind4+2, ind5-1); 
      //Serial.println("acx = " + acxValue); 
       String acy = httpGETRequest(serverNameAcy);
      //Serial.println(acy);
      
      int ind1b = acy.indexOf('}');
      int ind2b = acy.indexOf('_', ind1b); //takes you to unit_type in the JSON 
      int ind3b = acy.indexOf('v', ind2b); //takes you to last_v in the JSON
      int ind4b = acy.indexOf(':', ind3b); //takes you to right before "number goes here"
      int ind5b = acy.indexOf(',', ind4b); //takes you to comma after "number goes here",
      String acyValue = acy.substring(ind4b+2, ind5b-1); 
      //Serial.println("acy = " + acyValue);

      
      String acz = httpGETRequest(serverNameAcz);
      //Serial.println(acy);
      
      int ind1c = acz.indexOf('}');
      int ind2c = acz.indexOf('_', ind1c); //takes you to unit_type in the JSON 
      int ind3c = acz.indexOf('v', ind2c); //takes you to last_v in the JSON
      int ind4c = acz.indexOf(':', ind3c); //takes you to right before "number goes here"
      int ind5c = acz.indexOf(',', ind4c); //takes you to comma after "number goes here",
      String aczValue  = acz.substring(ind4c+2, ind5c-1); 
     // Serial.println("acz = " + aczValue);

 
      String gyy = httpGETRequest(serverNameGyy);
      //Serial.println(acy);
      
      int ind1d = gyy.indexOf('}');
      int ind2d = gyy.indexOf('_', ind1c); //takes you to unit_type in the JSON 
      int ind3d = gyy.indexOf('v', ind2c); //takes you to last_v in the JSON
      int ind4d = gyy.indexOf(':', ind3c); //takes you to right before "number goes here"
      int ind5d = gyy.indexOf(',', ind4c); //takes you to comma after "number goes here",
      String gyyValue  = gyy.substring(ind4c+2, ind5c-1); 
     // Serial.println("gyy = " + gyyValue);

      Serial1.print(acxValue + "," + acyValue + "," + aczValue + "," + gyyValue + ",");

    }
    else {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }
}

String httpGETRequest(const char* serverName) {
  HTTPClient http;
    
  // Your IP address with path or Domain name with URL path 
  http.begin(serverName);
  
  // Send HTTP POST request
  int httpResponseCode = http.GET();
  
  String payload = "{}"; 
  
  if (httpResponseCode> 0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    payload = http.getString();
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  // Free resources
  http.end();

  return payload;
}
