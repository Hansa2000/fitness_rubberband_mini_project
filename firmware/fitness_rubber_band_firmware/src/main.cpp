// #include <Arduino.h>
// #include "HX711.h"
// #include <Wire.h>
// #include <Adafruit_GFX.h>
// #include <Adafruit_SSD1306.h>
// #include <logo.h>

// // HX711 circuit wiring
// const int LOADCELL_DOUT_PIN = 12;
// const int LOADCELL_SCK_PIN = 13;

// HX711 scale;
// int reading;
// int lastReading;
// //REPLACE WITH YOUR CALIBRATION FACTOR
// #define CALIBRATION_FACTOR -478.507

// //OLED Display
// #define SCREEN_WIDTH 128 // OLED display width, in pixels
// #define SCREEN_HEIGHT 64 // OLED display height, in pixels


// // Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// #define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
// Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// //Button
// #define BUTTON_PIN 15
// //Pushbutton button(BUTTON_PIN);
// int currentState = 0;
// int buttonPressed = 0;
// long pressedTime;
// long releasedTime;


// //Button short press and long press
// const int SHORT_PRESS_TIME = 500; // 500 milliseconds

// //unit changing
// int unit = 0; // 0 for grams and 1 for ounces

// //sleep mode
// int change = 1;
// int timmer = 0;
// long beginTime;
// long currentTime;
// const long TIMEOUT = 60000; 


// void displayWeight(int weight){
//   display.clearDisplay();
//   display.setTextColor(WHITE);
//   // Display static text
//   //display.setTextSize(1);
//   //display.setCursor(0, 10);
//   //display.println("unit:");
//   //display.println(unit);
//   //display.display();
//   display.setCursor(24, 20);
//   if(!unit) { display.setTextSize(3); display.print(weight);}
//   else {display.setTextSize(2); display.print(weight*0.035274);}
//   display.display(); 
//   //display.print(" ");
//   display.setTextSize(4);
//   display.setCursor(96, 20);
//   if(!unit) display.print("N");
//   else{ display.setCursor(80, 20); display.setTextSize(3); display.print("oz");}
//   display.display();  
// }

// void setup() {
//   Serial.begin(115200);

//   if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
//     Serial.println(F("SSD1306 allocation failed"));
//     for(;;);
//   }
//   delay(2000);
//   display.clearDisplay();
//   display.drawBitmap(0, 0, logoFT, 128, 64, 1);
//   display.display();
//   display.setTextColor(WHITE);
  
//   Serial.println("Initializing the scale");
//   scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);

//   scale.set_scale(-518);   // this value is obtained by calibrating the scale with known weights
//   scale.tare();               // reset the scale to 0
//   pinMode(BUTTON_PIN,INPUT);
// }

// void loop() {

//   //Serial.println(button.getSingleDebouncedPress());
//   buttonPressed = digitalRead(BUTTON_PIN);
//   if (buttonPressed && !currentState){
//      pressedTime = millis();
//      currentState = HIGH;
//   }
//   else if(!buttonPressed && currentState){
//     releasedTime = millis();
//     currentState = LOW;
//     // check whether the press is short or long and tare or change unit accordingly
//     long pressDuration = releasedTime - pressedTime;
//      //Serial.print("Button Pressed time: ");
//       //Serial.print(pressDuration);
//     if( pressDuration < SHORT_PRESS_TIME ){
//       //Serial.print("tare...");
//       //Serial.read();
//       scale.tare();
//     }
//     else{
//       if(unit) unit = 0;
//       else unit = 1;
//       displayWeight(reading);
//     }
    
//   }
  

//   if (scale.wait_ready_timeout(200)) {
//     reading = round(scale.get_units());
//     //Serial.print("Weight: ");
//     //Serial.println(reading);
//     if (reading != lastReading){
//       displayWeight(reading);
//       change=1; 
//     }
//     else change=0;
    
//     lastReading = reading;
    
//     if(change) {timmer=0;}
//     else if(!change && !timmer){ timmer=1; beginTime = millis();}
//     else if(!change && timmer) { 
//        currentTime = millis(); 
//        if(currentTime-beginTime>TIMEOUT){ 
//         display.clearDisplay();
//         display.display();
//         ESP.deepSleep(0);
        
//         }
//     }
    
    
//   }
//   else {
//     Serial.println("HX711 not found.");
//   }
// }


#include <Arduino.h>
#include "HX711.h"
#include <Wire.h>   
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// HX711 circuit wiring
const int LOADCELL_DOUT_PIN = 12;
const int LOADCELL_SCK_PIN = 13;

HX711 scale;
int reading;
int lastReading;

// REPLACE WITH YOUR CALIBRATION FACTOR
#define CALIBRATION_FACTOR -478.507

// OLED Display
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Button
#define BUTTON_PIN 15
int currentState = 0;
int buttonPressed = 0;
long pressedTime;
long releasedTime;

// Button short press and long press
const int SHORT_PRESS_TIME = 500; // 500 milliseconds

// Unit changing
int unit = 0; // 0 for grams and 1 for ounces

// Sleep mode
int change = 1;
int timmer = 0;
long beginTime;
long currentTime;
const long TIMEOUT = 60000;

// Wi-Fi Credentials
const char *ssid = "your_SSID";  // Replace with your Wi-Fi credentials
const char *password = "your_PASSWORD";  // Replace with your Wi-Fi credentials

// Web server on port 80
ESP8266WebServer server(80);

void displayWeight(int weight) {
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setCursor(24, 20);
  if (!unit) {
    display.setTextSize(3);
    display.print(weight);
  } else {
    display.setTextSize(2);
    display.print(weight * 0.035274);
  }
  display.display();
  display.setTextSize(4);
  display.setCursor(96, 20);
  if (!unit) display.print("N");
  else {
    display.setCursor(80, 20);
    display.setTextSize(3);
    display.print("oz");
  }
  display.display();
}

// Handle web requests and return the current weight
void handleRoot() {
  String html = "<html><body>";
  html += "<h1>Weight Measurement</h1>";
  html += "<p>Current Weight: " + String(reading) + (unit == 0 ? " N" : " oz") + "</p>";
  html += "<p><a href='/change'>Change Unit</a></p>";
  html += "</body></html>";
  server.send(200, "text/html", html);
}

// Handle the unit change request
void handleUnitChange() {
  unit = (unit == 0) ? 1 : 0;
  server.sendHeader("Location", "/");
  server.send(303);
}

void setup() {
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi!");
  Serial.println("IP Address: " + WiFi.localIP().toString());

  // Initialize the web server
  server.on("/", HTTP_GET, handleRoot);  // Handle root URL
  server.on("/change", HTTP_GET, handleUnitChange);  // Handle unit change URL

  server.begin();  // Start the server

  // Initialize HX711
  Serial.println("Initializing the scale");
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.set_scale(-518);  // Calibrate with known weights
  scale.tare();  // Reset the scale to 0
  pinMode(BUTTON_PIN, INPUT);

  // Initialize OLED display
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  delay(2000);
  display.clearDisplay();
  display.display();
}

void loop() {
  // Read button state for unit change
  buttonPressed = digitalRead(BUTTON_PIN);
  if (buttonPressed && !currentState) {
    pressedTime = millis();
    currentState = HIGH;
  } else if (!buttonPressed && currentState) {
    releasedTime = millis();
    currentState = LOW;
    long pressDuration = releasedTime - pressedTime;
    if (pressDuration < SHORT_PRESS_TIME) {
      scale.tare();  // Tare the scale
    } else {
      unit = (unit == 0) ? 1 : 0;
      displayWeight(reading);  // Update OLED display
    }
  }

  // Update reading and serve the webpage
  if (scale.wait_ready_timeout(200)) {
    reading = round(scale.get_units());
    if (reading != lastReading) {
      displayWeight(reading);
    }
    lastReading = reading;
  }

  server.handleClient();  // Handle incoming client requests
}
