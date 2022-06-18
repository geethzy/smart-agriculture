/*----------Arduino to Pi----------
 
 void setup() {
  Serial.begin(9600);
}
void loop() {
  Serial.println("Hello from Arduino!");
  delay(1000);
}
*/

/*----- Pi to Arduino-------*/
void setup() {
  Serial.begin(9600);
}
void loop() {
  if (Serial.available() > 0) {
    String data = Serial.readStringUntil('\n');
    Serial.print("You sent me: ");
    Serial.println(data);
  }
}
