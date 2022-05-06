#include "dht.h"

#define dht_apin A1
const int ldr_pin = A0; 
dht DHT;
 
void setup(){
  Serial.begin(9600);
  pinMode(ldr_pin, INPUT);
  delay(1000); 
}
 
void loop(){
    DHT.read11(dht_apin);
    int ldrStatus = analogRead(ldr_pin);
    Serial.print(DHT.temperature);
    Serial.print(" ");
    Serial.print(DHT.humidity);
    Serial.print(" ");
    Serial.println(ldrStatus);
    delay(5000);
}
