#include <SoftwareSerial.h>

 SoftwareSerial mySerial(16, 17);  //RX, TX 
 
 int button1 = 7; //set the button1 pin
 int button2 = 8; //set the button2 pin
 int LED = 4; //set the LED pin

 int buzzer = 3; //set buzzer
 int motion = 5; // set motion sensor

 bool state1 = 1; //set button1 state
 bool state2 = 1; //set button2 state
 
 void setup()
 {
   pinMode(button1,INPUT);
   pinMode(button2,INPUT);
   pinMode(LED,OUTPUT);
   pinMode(buzzer, OUTPUT);
   digitalWrite(buzzer,LOW);
   pinMode(motion, INPUT);
   Serial.begin(115200);
  //  Serial.println("bengin the communication");
}

void loop() {
  state1 = digitalRead(button1);
  state2 = digitalRead(button2);
  digitalWrite(LED,HIGH);
  if (state1 == 0)
  {
    tone(buzzer, 100,50);
    delay(100);
    tone(buzzer, 1000,50);
  }
  if (state2 == 0)
  {
    digitalWrite(LED,HIGH);
    delay(100);
    digitalWrite(LED,LOW);
    delay(100);
  }
  if (digitalRead(motion))
  {
    Serial.println("test");
    digitalWrite(LED,HIGH);
    delay(100);
    digitalWrite(LED,LOW);
    delay(100);
  }
 }