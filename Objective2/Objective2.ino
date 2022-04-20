#include "dht.h"

#define dht_apin A1
dht DHT;
const int ledpin = 13;
const int ldrpin = A0;
int relay = 8;
 
void setup(){
 
  Serial.begin(9600);
  pinMode(ledpin, OUTPUT);
  pinMode(relay, OUTPUT);
  pinMode(ldrpin, INPUT);
  delay(500);
  Serial.println("Humidity,temperature & light intensity\n\n");
  delay(1000);
}

void loop(){
 
    DHT.read11(dht_apin);
    
    Serial.print("Current humidity = ");
    Serial.print(DHT.humidity);
    Serial.print("%  ");
    Serial.print("temperature = ");
    Serial.print(DHT.temperature); 
    Serial.println("C  ");
    delay(5000);

     int ldrStatus = analogRead(ldrpin);

     Serial.print("Current light intensity = ");
     Serial.println(ldrStatus);
     
      if (ldrStatus <= 150) {
        digitalWrite(ledpin, HIGH);
        digitalWrite(relay, HIGH);
        Serial.println("LDR is Dark, LED,light is ON\n");
        delay(2500);
      }
      else if(ldrStatus <= 350){
        digitalWrite(ledpin, HIGH);
        digitalWrite(relay, HIGH);
        Serial.println("LDR is Mid, LED,light is ON\n");
        delay(2500);
      }
      else {
        digitalWrite(ledpin, LOW);
        digitalWrite(relay, LOW);
        Serial.println("LDR is light, LED,light is OFF\n");
        delay(2500);
      } 
}
