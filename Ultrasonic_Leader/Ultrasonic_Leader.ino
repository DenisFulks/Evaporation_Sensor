// Pins
#define follower 2
#define trigger 8
#define echo 9

// Data
unsigned int cycle = 0;
unsigned int n = 100;

// Variable
unsigned int t;
unsigned int startTime;

void setup() {
  Serial.begin(9600);

  pinMode(follower, OUTPUT);
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);

  Serial.println("Leader Boot Complete");
  Serial.println("Performing Calibration, Please Place Sensor in Place with no Wind and Press Enter...");
  while(Serial.available() == 0) {}
  Serial.println("Calibrating...");

  for (int i = 0; i < n; i++) {
    digitalWrite(follower, HIGH);
    delayMicroseconds(10);
    digitalWrite(follower, LOW);

    digitalWrite(trigger, LOW);
    delayMicroseconds(2);
    digitalWrite(trigger, HIGH);  
    delayMicroseconds(10);
    digitalWrite(trigger, LOW);

    t = pulseIn(echo, HIGH);

    Serial.println(t);

    delay(200);
  }

  startTime = millis();
  Serial.println();
}

void loop() {
  digitalWrite(follower, HIGH);
  delayMicroseconds(10);
  digitalWrite(follower, LOW);

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

  delay(200);
}
