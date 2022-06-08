#include <SPI.h>
 
#include <ThingerESP8266.h> 
 
#include "dht.h"
#define dht_apin D0
dht DHT;

ThingerESP8266 thing("geeth", "NodeMCU", "Z-Jbd_nxi-xij!DG");//user, device_Id, device_credentials

void setup() {
thing.add_wifi("GeethCY", "Chathu1202@");
Serial.begin(5000);
Serial.print("conec6");
thing["dht11"] >> [](pson& out){
          out["humidity"] = DHT.humidity;
          Serial.print(DHT.humidity);
          out["celsius"] = DHT.temperature;
          Serial.print(DHT.temperature);
};
}

void loop() {
thing.handle();
DHT.read11(dht_apin);
 Serial.print(DHT.humidity);
 Serial.print(" ");
 Serial.println(DHT.temperature);
 delay(5000);
}
