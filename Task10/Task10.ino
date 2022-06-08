#define CAYENNE_PRINT Serial   //#define CAYENNE_DEBUG 
#include <CayenneMQTTESP8266.h> 

#include "dht.h"
#define dht_apin D0
dht DHT;
#define soilMoisture_Pin A0 
const int ldr_Pin = D2; 

float humid, temp, soil;
int light;  

char ssid[] = "GeethCY";
char wifiPassword[] = "Chathu1202@"; 
 
char username[] = "a6e32a70-dca6-11ec-8da3-474359af83d7"; 
char password[] = "73667b934e6a37c1acbb6c0d7d7eace1e8d72a8e";
 char clientID[] = "04821270-de61-11ec-8da3-474359af83d7";
 
void setup() {
   Serial.begin(9600); 
   Cayenne.begin(username, password, clientID, ssid, wifiPassword); 
} 
void loop() { 
  Cayenne.loop(); 
    
   DHT.read11(dht_apin);
   temp = DHT.temperature;
   Serial.print(temp);
   Serial.print(" "); 
   Cayenne.virtualWrite(V1, temp);
   
   humid = DHT.humidity;
   Serial.print(humid);
   Serial.print(" "); 
   Cayenne.virtualWrite(V0, humid);

   soil = analogRead(soilMoisture_Pin);
   Serial.print(soil);
   Serial.print(" "); 
   Cayenne.virtualWrite(V2, soil);
   
   light = analogRead(ldr_Pin);     
   Serial.println(light);
   Cayenne.virtualWrite(V3, light);
   delay(5000);
} 
CAYENNE_OUT_DEFAULT() { // Here the data we want to send
  }
