#include <Servo.h>
#define NOTE_C4 262
#define NOTE_D4 294
#define NOTE_E4 330
#define NOTE_F4 349
#define NOTE_G4 392
#define NOTE_A4 440
#define NOTE_B4 494
#define NOTE_C5 523

Servo myServo;
int pos = 0;    //position of servo
int buttonState = 0; //state of button
int garageLedPin = 9; //pin of garage led
int buttonPin = 8; //pin of button
int pingEchoPin = 12; //pin of ultrasonic sensor for echo
int pingTrigPin = 13; //pin of ultrasonic sensor for trigger
int LdrPin = A0; //ldr input pin
int ldrValue = 0; //value outputted by ldr
int dayNight = 400;  //value determining day or night
int adultHeight = 5; //value for distincting height
int piezoPin = 11; //pin for piezo
int adultLed = 6; //pin for adult led
int childLed = 7; //pin for child led

void setup() {

  Serial.begin(9600);
  for (int i = 0; i < 40; i++) {     //clears serial monitor
    Serial.println();
  }
  pinMode(garageLedPin, OUTPUT);
  digitalWrite(garageLedPin, HIGH);
  pinMode(buttonPin, INPUT);
  pinMode(adultLed, OUTPUT);
  pinMode(childLed, OUTPUT);
}


void loop() {

  ldrValue = analogRead(LdrPin); //stores value of light
  Serial.println(ldrValue);
  buttonState = digitalRead(buttonPin);

  if (buttonState == HIGH) {  //checking if button is pressed
    ultrasonic();
    Serial.println("Button is pressed");
  }
  buttonState = LOW;
}

//function to start the ultrasonic sensor
void ultrasonic() {

  long duration, cm;
  pinMode(pingTrigPin, OUTPUT);
  digitalWrite(pingTrigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingTrigPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingTrigPin, LOW);

  pinMode(pingEchoPin, INPUT);
  duration = pulseIn(pingEchoPin, HIGH);

  // convert the time into a distance
  cm = microsecondsToCentimeters(duration);
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  if (cm < adultHeight) {
    adultCase();
  } else {
    childCase();
  }
  pinMode(pingTrigPin, OUTPUT);

}

//function to convert time into centimeters
long microsecondsToCentimeters(long microseconds) {

  return microseconds / 29 / 2;

}

//function takes care in case of adult
void adultCase() {
  Serial.println("Adult Case");
  digitalWrite(adultLed, HIGH);

  if (ldrValue < dayNight) {
    Serial.println("Entered loop");
    digitalWrite(garageLedPin, LOW);
  }
  myServo.attach(10);

  for (pos = 0; pos <= 90; pos += 1) { // goes from 0 degrees to 180 degrees
    myServo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  
  delay(5000);
  
  for (pos = 90; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myServo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  digitalWrite(garageLedPin, HIGH);
  digitalWrite(adultLed, LOW);
}

//function takes care in case of adult
void childCase() {
  digitalWrite(childLed, HIGH);
  Serial.println("Child Case");
  alarm();
  digitalWrite(childLed, LOW);

}

//function plays the alarm
void alarm() {

  tone(piezoPin, NOTE_C4);
  delay(1000);
  tone(piezoPin, NOTE_G4);
  delay(1000);
  tone(piezoPin, NOTE_F4);
  delay(250);
  tone(piezoPin, NOTE_E4);
  delay(250);
  tone(piezoPin, NOTE_D4);
  delay(250);
  tone(piezoPin, NOTE_C5);
  delay(1000);
  tone(piezoPin, NOTE_G4);
  delay(500);
  tone(piezoPin, NOTE_F4);
  delay(250);
  tone(piezoPin, NOTE_E4);
  delay(250);
  tone(piezoPin, NOTE_D4);
  delay(250);
  tone(piezoPin, NOTE_C5);
  delay(1000);
  tone(piezoPin, NOTE_G4);
  delay(500);
  tone(piezoPin, NOTE_F4);
  delay(250);
  tone(piezoPin, NOTE_E4);
  delay(250);
  tone(piezoPin, NOTE_F4);
  delay(250);
  tone(piezoPin, NOTE_D4);
  delay(2000);

  noTone(piezoPin);
}
