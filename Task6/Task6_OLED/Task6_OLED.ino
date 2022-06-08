#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width,  in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels


#include "dht.h" 
#define dht_apin A0
dht DHT;

const int ldr_pin = A1;

#define soil_pin A2 
int soilMois;

Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);// declare an SSD1306 display object connected to I2C

void setup() {
  Serial.begin(9600);  
  if (!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {// initialize OLED display with address 0x3C for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    while (true);
  }

  delay(2000);         // wait for initializing
  oled.clearDisplay(); // clear display

  oled.setTextSize(2);          
  oled.setTextColor(WHITE);     
}

void loop() {
  DHT.read11(dht_apin);
  Serial.print(DHT.temperature);
  Serial.print(" ");
  Serial.print(DHT.humidity);
  Serial.print(" ");
  oled.setCursor(0, 4);        // position to display
  oled.print("T:");
  oled.println(DHT.temperature); // text to display
  oled.display();
  
  oled.setCursor(0, 19);       
  oled.print("H:");
  oled.println(DHT.humidity);             
  oled.display();
  
  int ldrStatus = analogRead(ldr_pin);
  Serial.print(ldrStatus);
  Serial.print(" ");
  oled.setCursor(0, 35);       
  oled.print("L:");
  oled.println(ldrStatus);
  oled.display();
  
  soilMois = analogRead(soil_pin);
  Serial.println(soilMois);
  oled.setCursor(0, 51);     
  oled.print("M:");   
  oled.println(soilMois); 
  oled.display();// show on OLED

  delay(9600);
}
