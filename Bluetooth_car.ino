/* 
 *  Written by Rupak Poddar
 *  www.youtube.com/RupakPoddar
 *  www.github.com/RupakPoddar
*/

#include<SoftwareSerial.h>
#define LED 13              // Connect light to pin 13 (Optional)
#define BUZZER 12        // Connect buzzer to pin 12 (Optional)
#define MOTOR_1A 2   // Connect motor driver input 1 to pin 11
#define MOTOR_1B 3   // Connect motor driver input 2 to pin 10
#define MOTOR_2A 4     // Connect motor driver input 3 to pin 9
#define MOTOR_2B 5     // Connect motor driver input 4 to pin 6
#define TX 0                 // Connect Bluetooth module Tx to pin 2
#define RX 1                 // Connect Bluetooth module Rx to pin 3

SoftwareSerial BTmodule(TX, RX);
int speed = 255;

void setup() {
  Serial.begin(9600);
  BTmodule.begin(9600);
  BTmodule.setTimeout(10);
  pinMode(MOTOR_1A, OUTPUT);
  pinMode(MOTOR_1B, OUTPUT); 
  pinMode(MOTOR_2A, OUTPUT);
  pinMode(MOTOR_2B, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  analogWrite(10, 100);
  analogWrite(9, 100);
}

void loop() {
  String readString;
  
  while(BTmodule.available()) {
    readString = BTmodule.readString();
    Serial.print("Received: ");
    Serial.println(readString);
  }
  // analogWrite(3, 100);
  // analogWrite(9, 100);
  if(readString.toInt() > 0)
  {
    analogWrite(10, readString.toInt());
    analogWrite(9, readString.toInt());
  }

                                                                                       // FORWARD
  if(readString == "F"){
    analogWrite(MOTOR_1A, speed);
    analogWrite(MOTOR_2A, speed);
  }
                                                                                       // BACKWARD
  if(readString == "B"){
    analogWrite(MOTOR_1B, speed);
    analogWrite(MOTOR_2B, speed);
  }
                                                                                       // LEFT
  if(readString == "L"){
    analogWrite(MOTOR_1B, speed);
    analogWrite(MOTOR_2A, speed);
  }
                                                                                       // RIGHT
  if(readString == "R"){
    analogWrite(MOTOR_1A, speed);
    analogWrite(MOTOR_2B, speed);
  }
                                                                                       // STOP
  if(readString == "S"){
    analogWrite(MOTOR_1A, 0);
    analogWrite(MOTOR_1B, 0);
    analogWrite(MOTOR_2A, 0);
    analogWrite(MOTOR_2B, 0);
  }
                                                                                       // LED ON
  if(readString == "LED_ON"){
    digitalWrite(LED, HIGH);
  }
                                                                                       // LED OFF
  if(readString == "LED_OFF"){
    digitalWrite(LED, LOW);
  }
                                                                                       // SOUND
  if(readString == "SOUND"){
    digitalWrite(BUZZER, HIGH);
    delay(100);
    digitalWrite(BUZZER, LOW);
  }
                                                                                       // SPEED
   if(readString.substring(0, 6) == "Speed:"){
    String val = readString.substring(readString.length()-3);
    if(val.substring(0, 1) == "d"){
      speed = val.substring(2).toInt();
    }
    else if(val.substring(0, 1) == ":"){
      speed = val.substring(1).toInt();
    }
    else{
      speed = val.toInt();
    }
    Serial.print("Speed: ");
    Serial.println(speed);
  }
}