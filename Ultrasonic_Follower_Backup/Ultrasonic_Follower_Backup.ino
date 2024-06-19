// Pins
#define follower 2
#define comm 4
#define trigger 8
#define echo 9

// Data
unsigned int cycle = 0;
unsigned index = 0;

// Variables;
float t;

void setup() {
  Serial.begin(9600);

  pinMode(13, OUTPUT);

  pinMode(follower, INPUT);
  pinMode(comm, OUTPUT);
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);

  Serial.println("Follower Boot Complete");
  Serial.println("Waiting for start command...");
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

  delay(100);

  digitalWrite(comm, HIGH);
  delayMicroseconds(t);
  digitalWrite(comm, LOW);

  cycle = cycle + 1;

  if (index < 100) {
    cycle = 0;
    index++;
  }

  Serial.print(cycle);
  Serial.print(", ");
  Serial.print(millis());
  Serial.print(", ");
  Serial.println(t);
}
