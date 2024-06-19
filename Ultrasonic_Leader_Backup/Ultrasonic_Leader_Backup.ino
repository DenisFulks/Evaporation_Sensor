// Pins
#define follower 2
#define ultraComm 4
#define trigger 8
#define echo 9

// Data
int cycle = 0;
float distance = 0.2;
float n = 100;

// Variable
float t1;
float t2;
float velocity;
float startTime;
float sum;
float error;
float velocityCalibrated;

void setup() {
  Serial.begin(9600);

  pinMode(follower, OUTPUT);
  pinMode(ultraComm, INPUT);
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

    t1 = pulseIn(echo, HIGH);

    t2 = pulseIn(ultraComm, HIGH, 1000000);

    if (t2 == 0) {
      Serial.println("Skipping...");

      n = n - 1;
      continue;
    }

    sum = sum + (t1 - t2);

    Serial.print(t1, 0);
    Serial.print(", ");
    Serial.print(t2, 0);
    Serial.print(", ");
    Serial.println("Calibrating...");

    delay(100);
  }

  error = sum / n;

  Serial.print("The Error is Approximately: ");
  Serial.print(error);
  Serial.println("us.");

  Serial.print("Waiting for Start Command... ");
  while(Serial.available() == 0) {}
  startTime = millis();
  Serial.println("Starting...");
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

  t1 = pulseIn(echo, HIGH);

  t2 = pulseIn(ultraComm, HIGH, 1000000);

  velocity = (distance / 2) * (1 / (t2 / 1000000) - 1 / (t1 / 1000000));
  velocityCalibrated = (distance / 2) * (1 / (t2 / 1000000) - 1 / ((t1 - error) / 1000000));

  if(t2 == 0){
    cycle = cycle;
  } else{
    cycle = cycle + 1;
  }

  Serial.print(cycle);
  Serial.print(", ");
  Serial.print(millis() - startTime, 0);
  Serial.print(", ");
  Serial.print(t1, 0);
  Serial.print(", ");
  Serial.print(t2, 0);
  Serial.print(", ");
  Serial.print(velocity, 10);
  Serial.print(", ");
  Serial.println(velocityCalibrated, 10);

  delay(100);
}
