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

  // Sets Pin Mode
  pinMode(follower, OUTPUT);
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);

  // Makes sure board boots and waits for calibration command
  Serial.println("Leader Boot Complete");
  Serial.println("Performing Calibration, Please Place Sensor in Place with no Wind and Press Enter...");
  while(Serial.available() == 0) {}
  Serial.println("Calibrating...");

  // Calibration
  for (int i = 0; i < n; i++) {
    // Send follow signal
    digitalWrite(follower, HIGH);
    delayMicroseconds(10);
    digitalWrite(follower, LOW);

    // Send ultra puls
    digitalWrite(trigger, LOW);
    delayMicroseconds(2);
    digitalWrite(trigger, HIGH);  
    delayMicroseconds(10);
    digitalWrite(trigger, LOW);

    // Records time
    t = pulseIn(echo, HIGH);

    Serial.println(t);

    delay(200);
  }

  // Gets start time and makes seperator
  startTime = millis();
  Serial.println();
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

  cycle++;

  // prints cycle, runtime, and ultra time
  Serial.print(cycle);
  Serial.print(", ");
  Serial.print(millis() - startTime);
  Serial.print(", ");
  Serial.println(t);

  delay(200);
}
