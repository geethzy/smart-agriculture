#include <Wire.h>
#include "RTClib.h"

RTC_DS3231 rtc;
char t[32];

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

#include <Keypad.h>

const int ROW_NUM = 4; 
const int COLUMN_NUM = 4; 

char keys[ROW_NUM][COLUMN_NUM] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte pin_rows[ROW_NUM] = {9, 8, 7, 6};   
byte pin_column[COLUMN_NUM] = {5, 4, 3, 2}; 
Keypad keypad = Keypad( makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM );

String inputString;
long startTime;
long endTime;
bool light = 0;

int light_pin = 12;
const int ldr_pin = A0; 

//String Time;
long int currentTime;

void setup () 
{
  Serial.begin(9600);
  delay(3000);

  pinMode(ldr_pin, INPUT);
  inputString.reserve(6); 
  pinMode(light_pin, OUTPUT);
  digitalWrite(light_pin, LOW);

  printTime();
  getDetails(); 
}

void loop () {
  while (1) {
    getcurrentTime();
    /*char *time_format = "hhmmss";//String Time = String(now.hour(), DEC) + String(now.minute(), DEC) + String(now.second(), DEC);
    Time = now.toString(time_format);
    Serial.println(Time);
    currentTime = Time.toInt();
    Serial.println(currentTime);*/
   
    if (t < startTime) {
      readData();
    }
    if (startTime == t) {
      Serial.println("Start manual light cycle !!!");
    }
    if (startTime < t < endTime) {
      digitalWrite(light_pin, HIGH);
    }
    if (t == endTime) {
      Serial.println("End manual light cycle !!!");
    }
    if ( t > endTime) {  
      readData();
    }        
  } 
}

void getcurrentTime(){
  DateTime now = rtc.now();
  sprintf(t, "%02d%02d%02d",  now.hour(), now.minute(), now.second());  
  Serial.println(t);
  currentTime = t;
  Serial.println(currentTime);
     /*char *time_format = "hhmmss";//String Time = String(now.hour(), DEC) + String(now.minute(), DEC) + String(now.second(), DEC);
    Time = now.toString(time_format);
    String Time = String(now.hour(), DEC) + String(now.minute(), DEC) + String(now.second(), DEC);
    Serial.println(Time);
    long int currentTime = Time.toInt();
    Serial.println(currentTime);*/
}

long key_to_int() {
  long inputInt;
  while (1) {
    char key = keypad.getKey();

    if (key) {
      Serial.print(key);

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

void printTime(){
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  if (rtc.lostPower()) {
    Serial.println("RTC lost power, lets set the time!");
    rtc.adjust(DateTime(F(__DATE__),F(__TIME__)));// Comment out below lines once you set the date & time.Following line sets the RTC to the date & time this sketch was compiled
    /*Following line sets the RTC with an explicit date & time
    for example to set January 27 2017 at 12:56 you would call:*/
     //rtc.adjust(DateTime(2022, 6, 7, 8, 28, 0));
  }

    DateTime now = rtc.now();
    Serial.print("Current Date & Time: ");
    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(" (");
    Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
    Serial.print(") ");
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();
}

void getDetails(){
  Serial.println();
 Serial.println("-----DETAILS OF THE LIGHT CYCLE-----\n");
  Serial.println("Enter start time of light cycle: ");
  startTime = key_to_int();
  Serial.print("\nSaved start time as ");
  Serial.println(startTime);
  Serial.println("\nEnter end time of light cycle:");
  endTime = key_to_int();
  Serial.print("\nSaved end time as ");
  Serial.println(endTime);
  Serial.println("\n-----LIGHT READINGS-----");
  Serial.println("*******************************************************");
  Serial.println();
}

void readData(){
   int ldrStatus = analogRead(ldr_pin);
     Serial.print(ldrStatus);
     if (ldrStatus <= 150) {
      digitalWrite(light_pin, LOW);
      Serial.print("  Status: OFF(Light range)");
      delay(5000);
     } else if (ldrStatus <= 350) {
      digitalWrite(light_pin, HIGH);
      Serial.print("  Status: ON(Mid range)");
      delay(5000);
     } else if (ldrStatus <= 1500){
      digitalWrite(light_pin, HIGH);
      Serial.print("  Status: ON(Dark range)");
      delay(5000);
     }
     Serial.println();
}
