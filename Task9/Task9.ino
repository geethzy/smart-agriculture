const int Valve_Pin = 8;  
#define soilMoisture_Pin A0

#define soilWet 500   
#define soilDry 750 

float soil;

void setup() {
  pinMode(Valve_Pin, OUTPUT);
  digitalWrite(Valve_Pin, LOW);
  Serial.begin(9600);
}

void loop() {
  soil = analogRead(soilMoisture_Pin);
  Serial.println(soil); 
  if (soil < soilWet) {
    digitalWrite(Valve_Pin, LOW);
    Serial.println("Status: Soil is too wet");
  } else if(soil >= soilWet && soil < soilDry) {
    digitalWrite(Valve_Pin, LOW);
    Serial.println("Status: Soil moisture is perfect");
  } else {
    digitalWrite(Valve_Pin, HIGH);
    Serial.println("Status: Soil moisture is too dry - time to water!");
  } 
  delay(5000);
}
