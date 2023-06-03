/*
  Code by ArmanJR
  
  ESP32 HTTP req by Rui Santos
  Complete project details at Complete project details at https://RandomNerdTutorials.com/esp32-http-get-post-arduino/

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*/

#include <WiFi.h>
#include <HTTPClient.h>
#include <Arduino_JSON.h>
#include <LiquidCrystal_I2C.h>


const char* ssid = "WIFI_SSID";
const char* password = "WIFI_PASSWORD";

//Your Domain name with URL path or IP address with path
const char* serverName = "SERVER_URL";

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastTime = 0;
// Timer set to 10 minutes (600000)
//unsigned long timerDelay = 600000;
// Set timer to 25 seconds (25000)
unsigned long timerDelay = 25000;

String sensorReadings;
float sensorReadingsArr[3];

// set the LCD number of columns and rows
int lcdColumns = 16;
int lcdRows = 2;

// set LCD address, number of columns and rows
// if you don't know your display address, run an I2C scanner sketch
LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);  

const char* dest;
const char* number;
const char* aircraft_model;
const char* airline_name;
String line1;
String line2;

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
 
  Serial.println("Timer set to 25 seconds (timerDelay variable), it will take 25 seconds before publishing the first reading.");

  // initialize LCD
  lcd.init();
  // turn on LCD backlight                      
  lcd.noBacklight();
}

void loop() {
  //Send an HTTP POST request every 10 minutes
  if ((millis() - lastTime) > timerDelay) {
    //Check WiFi connection status
    if(WiFi.status()== WL_CONNECTED){
              
      sensorReadings = httpGETRequest(serverName);
      Serial.println(sensorReadings);
      JSONVar myObject = JSON.parse(sensorReadings);
  
      // JSON.typeof(jsonVar) can be used to get the type of the var
      if (JSON.typeof(myObject) == "undefined") {
        Serial.println("Parsing input failed!");
        return;
      }
    
      Serial.print("JSON object = ");
      Serial.println(myObject);
    
      // myObject.keys() can be used to get an array of all the keys in the object
      JSONVar keys = myObject.keys();

      dest = myObject["dest"];
      number = myObject["number"];
      aircraft_model = myObject["aircraft_model"];
      airline_name = myObject["airline_name"];

      lcd.clear();
      lcd.noBacklight();
      delay(1000);
      line1 = dest;
      line2 = number;
      if(aircraft_model != "null") {
        line2 = line2+" / ";
        line2 = line2+aircraft_model;
      }
      if(airline_name != "null") {
        line2 = line2+" / ";
        line2 = line2+airline_name;
      }
      lcd.backlight();
      lcd.setCursor(0, 0);
      
      lcd.print(line1);
      delay(1000);
      lcd.setCursor(0,1);
      lcd.print(line2);
    }
    else {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }
}

String httpGETRequest(const char* serverName) {
  WiFiClient client;
  HTTPClient http;
    
  // Your Domain name with URL path or IP address with path
  http.begin(client, serverName);
  
  // If you need Node-RED/server authentication, insert user and password below
  //http.setAuthorization("REPLACE_WITH_SERVER_USERNAME", "REPLACE_WITH_SERVER_PASSWORD");
  
  // Send HTTP POST request
  int httpResponseCode = http.GET();
  
  String payload = "{}"; 
  
  if (httpResponseCode>0) {
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
