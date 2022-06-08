const int ldrpin = A1;
int relay = 12;
 
void setup(){
 
  Serial.begin(9600);
  pinMode(relay, OUTPUT);
  pinMode(ldrpin, INPUT);
  delay(500);
  Serial.println("Humidity,temperature & light intensity\n\n");
  delay(1000);
}

void loop(){
     int ldrStatus = analogRead(ldrpin);

     Serial.print("Current light intensity = ");
     Serial.println(ldrStatus);
     
      if (ldrStatus <= 150) {
        digitalWrite(relay, HIGH);
        Serial.println("LDR is Dark, light is ON\n");
        delay(2500);
      }
      else if(ldrStatus <= 350){
        digitalWrite(relay, HIGH);
        Serial.println("LDR is Mid, light is ON\n");
        delay(2500);
      }
      else {
        digitalWrite(relay, LOW);
        Serial.println("LDR is light, light is OFF\n");
        delay(2500);
      } 
}
