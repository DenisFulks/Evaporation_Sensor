// Pins
#define follower 2
#define trigger 8
#define echo 9
#define light 10

// Data
unsigned int counter = 0;

// Variables
unsigned int t;

void setup() {
  Serial.begin(9600);

  // Sets Pin Mode
  pinMode(follower, OUTPUT);
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(light, OUTPUT);

  digitalWrite(light, LOW);
}

void loop() {
  // Sends follow signal
  digitalWrite(follower, HIGH);
  delayMicroseconds(10);
  digitalWrite(follower, LOW);

  // sends ultra pulse
  digitalWrite(trigger, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);

  // records time
  t = pulseIn(echo, HIGH);

  // prints ToF
  Serial.print(t);
  Serial.write(13);
  Serial.write(10);

  // counter++;

  /*
  if (counter == 100) {
    counter = 0;

    digitalWrite(light, HIGH);
    delay(100);
    digitalWrite(light, LOW);
  }
  */

  delay(150);
}
