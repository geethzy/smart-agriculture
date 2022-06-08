#define BLYNK_PRINT Serial   
#define BLYNK_TEMPLATE_ID "TMPLesOR4Ibw"
#define BLYNK_DEVICE_NAME "SmartGreenhouse"

#include <SPI.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include "dht.h"

#define dht_apin D0
dht DHT;

#define soilMoisture_Pin D2 
const int ldr_Pin = A0; 

float humid, temp, soil;
int light;  

#define BLYNK_AUTH_TOKEN "C3jO3JKPMsjKaBAtrv9kZ2bJ5QTR5aro"

char auth[] = "C3jO3JKPMsjKaBAtrv9kZ2bJ5QTR5aro";

char server[] = "blynk-cloud.com";
char ssid[] = "GeethCY";  
char pass[] = "Chathu1202@";  
int port = 8080;

void sendSensor()
{
  DHT.read11(dht_apin);
  float h = DHT.humidity;
  float t = DHT.temperature; 
  soil = analogRead(soilMoisture_Pin);
  light = analogRead(ldr_Pin);   

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  Blynk.virtualWrite(V0, h); 
  Blynk.virtualWrite(V1, t); 
  Blynk.virtualWrite(V2, soil);
  Blynk.virtualWrite(V3, light);
  Serial.print(h);
  Serial.print(" ");
  Serial.print(t);
  Serial.print(" ");
  Serial.print(soil);
  Serial.print(" "); 
  Serial.println(light);
  delay(5000);
}

void setup()
{
  Serial.begin(9600); 
  Blynk.begin(auth, ssid, pass);
  //Blynk.connectWiFi(ssid, pass);
  //Blynk.config(auth);
  //Blynk.connect();
}

void loop()
{
  Blynk.run(); 
  sendSensor();
}
