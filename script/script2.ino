#include <SoftwareSerial.h>

SoftwareSerial mySerial(12, 13); // ports RX, TX to read and transmit the signals

int button1 = 7; // set the button1 pin
int button2 = 8; // set the button2 pin
int LED = 4; // set the LED pin
int buzzer = 3; // set buzzer
int motion = 5; // set motion sensor

bool state1 = 1; // set button1 state
bool state2 = 1; // set button2 state

unsigned long motionDetectedTime = 0;
unsigned long noMotionDetectedTime = 0;
unsigned long startTime = 0;
unsigned long userTime = 0;
int counter = 0;
bool motionDetected = false;
bool blinking = false;

void setup() {
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  pinMode(LED, OUTPUT);
  pinMode(buzzer, OUTPUT);
  digitalWrite(buzzer, LOW);
  pinMode(motion, INPUT);
  mySerial.begin(115200);
  Serial.begin(9600);
}

void loop() {
  state1 = digitalRead(button1);
  state2 = digitalRead(button2);

  // x = digitalRead(motion);
  // Serial.println(x);
  
  if (digitalRead(motion)) {

    if (!motionDetected) {

      motionDetected = true;
      motionDetectedTime = millis();
      noMotionDetectedTime = 0;

      if (counter == 0) {
        startTime = millis(); // Start the timer
      }
    }
    userTime = (millis() - startTime) / 1000 / 60; // calculate user time in minutes
  } else {
    if (motionDetected) {
      noMotionDetectedTime = millis();
      motionDetected = false;
    }
    if (millis() - noMotionDetectedTime > 10000) { // 45 minutes
      counter = 0;
      blinking = false;
      noMotionDetectedTime = 0;
    }
  }

  if (motionDetected && millis() - motionDetectedTime >= 5000) { // 30 minutes
    blinking = true;
    tone(buzzer, 100, 50);
    delay(100);
    tone(buzzer, 1000, 50);
    motionDetectedTime = millis(); // Reset the timer
  }

  if (blinking) {
    digitalWrite(LED, HIGH);
    delay(500);
    digitalWrite(LED, LOW);
    delay(500);
  }

  if (state1 == 0 && blinking) {
    // Send data to ESP32
    mySerial.print("User time: ");
    mySerial.println(userTime);
    blinking = false;
    Serial.println("User time: ");
    Serial.println(userTime);
  }

  if (state2 == 0 && blinking) {
    // Send data to ESP32
    mySerial.print("User time: ");
    mySerial.println(userTime);
    blinking = false;
    Serial.print("User time: ");
    Serial.println(userTime);
  }
}