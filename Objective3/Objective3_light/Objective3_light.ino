#include <Keypad.h>

const int ROW_NUM = 4; 
const int COLUMN_NUM = 4; 

char keys[ROW_NUM][COLUMN_NUM] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte pin_rows[ROW_NUM] = {2, 3, 4, 5};   
byte pin_column[COLUMN_NUM] = {6, 7, 8, 9}; 
Keypad keypad = Keypad( makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM );

String inputString;
long stime;
long endtime;
bool light = 0;

void setup() {
  Serial.begin(9600);
  inputString.reserve(6); 
  pinMode(13, OUTPUT);

}

void loop() {

  Serial.println("Enter start time of light cycle: ");
  stime = key_to_int();
  Serial.println(stime);
  Serial.println("Enter end time of light cycle:");
  endtime = key_to_int();
  Serial.println(endtime);

  while (1) {
    if (stime < millis()) {
      digitalWrite(13, HIGH);
    }
    if (millis() > endtime) {
      digitalWrite(13, LOW);
      break;
    }
  }
}

long key_to_int() {
  long inputInt;
  while (1) {
    char key = keypad.getKey();

    if (key) {
      Serial.println(key);

      if (key >= '0' && key <= '9') {
        inputString += key;
      } else if (key == '#') {
        if (inputString.length() > 0) {
          inputInt = inputString.toInt();
          inputString = "";
          break;

        }
      } else if (key == '*') {
        inputString = "";
      }
    }
  }
  return inputInt;
}
