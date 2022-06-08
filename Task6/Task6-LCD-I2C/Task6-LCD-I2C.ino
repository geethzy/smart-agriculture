#include "dht.h" 
#define dht_apin A0
dht DHT;

const int ldr_pin = A1; 

#define soil_pin A2 
int soilMois;

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup(){
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.clear();
}

void loop(){ 
   DHT.read11(dht_apin);
  Serial.print(DHT.temperature);
  Serial.print(" ");
  Serial.print(DHT.humidity);
  Serial.print(" ");
  lcd.setCursor(0, 0);// set the cursor to column 0, line1
  lcd.print("T:");
  lcd.print(DHT.temperature);
  lcd.setCursor(0, 1);// set the cursor to column 0, line 2
  lcd.print("H:");
  lcd.print(DHT.humidity);
  
  int ldrStatus = analogRead(ldr_pin);
  Serial.print(ldrStatus);
  Serial.print(" ");
  lcd.setCursor(9, 0);
  lcd.print("L:");
  lcd.print(ldrStatus);
  
  soilMois = analogRead(soil_pin);
  Serial.println(soilMois);
  lcd.setCursor(9, 1);
  lcd.print("M:");
  lcd.print(soilMois);
   delay(5000);
}
