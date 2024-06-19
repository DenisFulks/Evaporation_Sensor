#include <NewPing.h>

// Pins
#define trigger 8
#define echo 9

void setup() {
  Serial.begin(9600);

  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);
}

NewPing sonar(trigger, echo);

void loop() {
  float t = sonar.ping_median();

  float distance = (t * 0.0343) / 2;

  Serial.print(millis());
  Serial.print(", ");
  Serial.print(t);
  Serial.print(", ");
  Serial.println(distance);
}
