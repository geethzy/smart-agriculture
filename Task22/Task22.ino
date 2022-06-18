
#include "dht.h" 
#define dht_apin A0
dht DHT;

#define ldr_pin A1

#define soil_pin A2 
float soilMois;

#include <LiquidCrystal_I2C.h>
//LCD display is defined as device number 0x27 on the I2C bus
LiquidCrystal_I2C lcd(0x27, 16, 2);
//DHT11 is connected to pin 8


//Raspberry Pi is connected to Serial 0
#define serialPi Serial
void setup() {
  lcd.begin(20, 4); // Initializes the interface to the LCD screen, and specifies the dimensions (width and height) of the display
  lcd.init();
  lcd.backlight();
  serialPi.begin(9600);  //Arduino to serial monitor
}
void loop() {
  //Read sensor data
  int sensorData = DHT.read11(dht_apin);
  float temperature = DHT.temperature;
  float humidity = DHT.humidity;
  //Print temperature
  lcd.setCursor(0, 0);
  lcd.print("T:");
  lcd.print(temperature);
  //Print humidity
  lcd.setCursor(0, 1);
  lcd.print("H:");
  lcd.print(humidity);     
  float ldrStatus = analogRead(ldr_pin);
  lcd.setCursor(8, 0);
  lcd.print("L:");
  lcd.print(ldrStatus);
  float soilMois = analogRead(soil_pin);
  lcd.setCursor(8, 1);
  lcd.print("M:");
  lcd.print(soilMois);  
  //Send temperature and humidity data to Raspberry Pi
  serialPi.print("<");
  serialPi.print(int(temperature));
  serialPi.print(",");
  serialPi.print(int(humidity));
  serialPi.print(";");
  serialPi.print(int(ldrStatus));
  serialPi.print(":");
  serialPi.print(int(soilMois));
  serialPi.println(">");
  //Wait for 10 seconds
  delay(10000);
}
