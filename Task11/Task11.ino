#include "FirebaseESP8266.h"  //FirebaseESP8266.h must be included before ESP8266WiFi.h
#include <ESP8266WiFi.h>         
#include "dht.h"

#define dht_apin D0
dht DHT;

#define soilMoisture_Pin D1
const int ldr_Pin = A0; 

float soil;
int light;

#define FIREBASE_HOST "geeth-13d50-default-rtdb.firebaseio.com" 
#define FIREBASE_AUTH "qvz8dQRhJjamdOoRp87KIkuzMoXEtlvpPLBzWKRG"
#define WIFI_SSID "GeethCY"
#define WIFI_PASSWORD "Chathu1202@"

FirebaseData sensorData;//Define FirebaseESP8266 data object
FirebaseJson json;

void setup(){
  Serial.begin(9600);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
}

void sensorUpdate(){
  DHT.read11(dht_apin);
  float h = DHT.humidity;
  float t = DHT.temperature;
  soil = analogRead(soilMoisture_Pin);  
  light = analogRead(ldr_Pin); 
  
  /*if (isnan(h) || isnan(t)) {// Check if any reads failed and exit early (to try again).
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  } */  
  
  Serial.print(F("Humid.: "));
  Serial.print(h);
  Serial.print(F("%  Temp.: "));
  Serial.print(t);
  Serial.print(F("C  "));
  Serial.print(F("soilMoist.: "));
  Serial.print(soil);
  Serial.print(F(" lightInt.: "));
  Serial.println(light);

Firebase.setFloat(sensorData, "/FirebaseIOT/temperature", t);
Firebase.setFloat(sensorData, "/FirebaseIOT/humid", h);
Firebase.setFloat(sensorData, "/FirebaseIOT/soilmoisture", soil);
Firebase.setFloat(sensorData, "/FirebaseIOT/light", light);

}
void loop() {
  sensorUpdate();
 /* if (Firebase.getString(ledData, "/FirebaseIOT/led")){
    Serial.println(ledData.stringData());
    if (ledData.stringData() == "1") {
    digitalWrite(led, HIGH);
    }
  else if (ledData.stringData() == "0"){
    digitalWrite(led, LOW);
    }
  }*/
  delay(5000);
}
