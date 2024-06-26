// Pins
#define follower 2
#define trigger 8
#define echo 9

// Data
unsigned int cycle = 0;
unsigned int n = 100;

// Variables;
unsigned int t;
unsigned int startTime;

void setup() {
  Serial.begin(9600);

  pinMode(follower, INPUT);
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);
}

void loop() {
  while(digitalRead(follower) == LOW) {}
  delayMicroseconds(10);

  digitalWrite(trigger, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);

  t = pulseIn(echo, HIGH);

  cycle++;

  delay(25);

  Serial.print(t);
  Serial.write(13);
  Serial.write(10);
}
