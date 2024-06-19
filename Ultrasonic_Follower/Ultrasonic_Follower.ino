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

  pinMode(13, OUTPUT);

  pinMode(follower, INPUT);
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);

  Serial.println("Follower Boot Complete");
  Serial.println("Waiting for start command...");

  for (int i = 0; i < n; i++) {
    while(digitalRead(follower) == LOW) {}
    delayMicroseconds(10);

    digitalWrite(trigger, LOW);
    delayMicroseconds(2);
    digitalWrite(trigger, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigger, LOW);

    t = pulseIn(echo, HIGH);

    Serial.println(t);
  }

  startTime = millis();
  Serial.println();
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

  Serial.print(cycle);
  Serial.print(", ");
  Serial.print(millis() - startTime);
  Serial.print(", ");
  Serial.println(t);
}
