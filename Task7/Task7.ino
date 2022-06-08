#include <ThingSpeak.h>
#include <ESP8266WiFi.h>

#include "dht.h"
#define dht_apin D0
dht DHT;
#define soilMoisture_Pin D2 
const int ldr_Pin = A0; 

float humid, temp, soil;
int light;  

const char* ssid     = "GeethCY";
const char* password = "Chathu1202@";

WiFiClient  client;
long myChannelNumber =  1750935;
const char myWriteAPIKey[] = "1ZYXNRAA4FV6GMDY";

void setup() {
   Serial.begin(9600); 
   delay(100);
   pinMode(ldr_Pin, INPUT);
   
   Serial.println();
   Serial.println();
   Serial.print("Connecting to ");
   Serial.println(ssid);
  
   WiFi.begin(ssid, password);
  
   while (WiFi.status() != WL_CONNECTED) {
   delay(200);
   Serial.print("...");
   }
  
   Serial.println("");
   Serial.println("WiFi connected");  
   Serial.println("IP address: ");
   Serial.println(WiFi.localIP());
   ThingSpeak.begin(client);
   Serial.println("\nTemperature Humidity SoilMositure LightIntensity");
  }


void loop() {  
   DHT.read11(dht_apin);
   temp = DHT.temperature;
   Serial.print(temp);
   Serial.print(" "); 
   humid = DHT.humidity;
   Serial.print(humid);
   Serial.print(" "); 

   soil = analogRead(soilMoisture_Pin);
   Serial.print(soil);
   Serial.print(" "); 
   
   light = analogRead(ldr_Pin);     
   Serial.print(light);
  
   ThingSpeak.setField(1,temp);
   ThingSpeak.setField(2,humid);
   ThingSpeak.setField(3,soil);
   ThingSpeak.setField(4,light);

   ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);//ThingSpeak.writeField(myChannelNumber, 1,input_val, myWriteAPIKey);//For one 
   Serial.println("  Send to Thingspeak.");//ThingSpeak need min 15 sec delay between updates
   Serial.println("Waiting.....");
   delay(15000);
}
