#include "Ubidots.h"

#include "dht.h"
#define dht_apin D0 
dht DHT;

#define soilMoisture_Pin D1
const int ldr_Pin = A0; 

float soil;
int light;

const char* UBIDOTS_TOKEN = "BBFF-1iEJgM06gznqLxGbUkbX3L2N3fgmjg";  // Put here your Ubidots TOKEN
const char* WIFI_SSID = "GeethCY";      // Put here your Wi-Fi SSID
const char* WIFI_PASS = "Chathu1202@";      // Put here your Wi-Fi password 

Ubidots ubidots(UBIDOTS_TOKEN, UBI_HTTP); 

void setup() {                       

  Serial.begin(115200);
  ubidots.wifiConnect(WIFI_SSID, WIFI_PASS);
  // ubidots.setDebug(true);  // Uncomment this line for printing debug  messages                     
}

void loop() {
  DHT.read11(dht_apin);
  float MyHumidity = DHT.humidity;
  float MyTemperature = DHT.temperature;
  soil = analogRead(soilMoisture_Pin);  
  light = analogRead(ldr_Pin); 
  Serial.print(MyHumidity);
  Serial.print(" ");
  Serial.print(MyTemperature);
  Serial.print(" ");
  Serial.print(soil);
  Serial.print(" ");
  Serial.println(light);
  //client.add("MyHumidity",MyHumidity );
  //client.add("MyTemperature",MyTemperature );
  //client.sendAll(true);

  ubidots.add("HUM", MyHumidity);
  ubidots.add("TEMP", MyTemperature);
  ubidots.add("soil", soil);
  ubidots.add("light", light);
  
  bool bufferSent = false;
  bufferSent = ubidots.send(); 

  if (bufferSent) {
   Serial.println("Values sent by the device"); //set baud rate to 115200
  }
  delay(5000);
}
