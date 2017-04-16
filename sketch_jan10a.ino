#include "pitches.h"
int DIR1 = 8;
int EN1 = 9;
int DIR2 = 10;
int EN2 = 11;
int soundPin = 12;
char data;
bool currentDir = 0;
int currentSpeed = 0;
int lightPin = 15;
int Mario_melody[] = {
  NOTE_E4, NOTE_E4, REST, NOTE_E4,
  REST, NOTE_C4, NOTE_E4, REST,
  NOTE_G4, REST, REST, NOTE_G3, REST,

  NOTE_C4, REST, REST, NOTE_G3,
  REST, NOTE_E3, REST,
  REST, NOTE_A3, REST, NOTE_B3,
  REST, NOTE_AS3, NOTE_A3, REST,

  NOTE_G3, NOTE_E4, NOTE_G4,
  NOTE_A4, REST, NOTE_F4, NOTE_G4,
  REST, NOTE_E4, REST, NOTE_C4,
  NOTE_D4, NOTE_B3, REST
};
int Mario_Notes[] = {
  4, 4, 4, 4,
  4, 4, 4, 4,
  4, 2, 4, 2, 2,

  4, 4, 4, 4,
  2, 4, 4,
  4, 4, 4, 4,
  4, 4, 4, 4,

  4, 2, 4,
  4, 4, 4, 4,
  4, 4, 4, 4,
  4, 4, 2
};

const int num_elements_in_arr = sizeof(Mario_Notes) / sizeof(Mario_Notes[0]);
void setup()
{
  pinMode(DIR1, OUTPUT);
  pinMode(EN1, OUTPUT);
  pinMode(DIR2, OUTPUT);
  pinMode(EN2, OUTPUT);
  Serial.begin(9600);


  // set motor to stopped state
  analogWrite(EN1, 0);
  analogWrite(EN2, 0);
  delay(5);
  // set direction to 0
  digitalWrite(DIR1, HIGH);
  digitalWrite(DIR2, LOW);
  delay(5);
}
void loop()
{
  int reading = analogRead(lightPin);
  
  if (reading < 20) {
    playSounds();
  }
  if (Serial.available())
  {
    data = Serial.read();
    Serial.println(data);
    if (data == '1') {
      moveForward();
    }
    if (data == '2') {
      moveBackward();
    }
    if (data == '3') {
      moveLeft();
    }
    if (data == '4') {
      moveRight();
    }
    if (data == '5') {
      stopMoving();
    }
    if (data == '6') {
      playSounds();
    }
  }

}
void moveForward()
{
  analogWrite(EN1, 0);
  analogWrite(EN2, 0);
  delay(50);
  digitalWrite(DIR1, HIGH);
  digitalWrite(DIR2, LOW);
  delay(50);
  for (int i = 0; i < 255; i += 5) // accelerate
  {
    analogWrite(EN1, i);
    analogWrite(EN2, i);
    delay(10);
  }
}
void moveBackward()
{
  analogWrite(EN1, 0);
  analogWrite(EN2, 0);
  delay(50);
  digitalWrite(DIR1, LOW);
  digitalWrite(DIR2, HIGH);
  delay(50);
  for (int i = 0; i < 255; i += 5) // accelerate
  {
    analogWrite(EN1, i);
    analogWrite(EN2, i);
    delay(10);
  }
}
void moveLeft()
{
  for (int i = 0; i < 255; i += 5) // accelerate
  {
    analogWrite(EN1, i);
    analogWrite(EN2, i / 5);
    delay(10);
  }
}
void moveRight()
{
  for (int i = 0; i < 255; i += 5) // accelerate
  {
    analogWrite(EN1, i / 5);
    analogWrite(EN2, i);
    delay(10);
  }
}
void stopMoving()
{
  analogWrite(EN1, 0);
  analogWrite(EN2, 0);
}
void playSounds()
{
  for (int thisNote = 0; thisNote < num_elements_in_arr; thisNote++) {

    // to calculate the note duration, take one second
    // divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 500 / Mario_Notes[thisNote];
    tone(soundPin, Mario_melody[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(soundPin);
  }
}

