void setup() {
  pinMode(13, OUTPUT);
  pinMode(3, OUTPUT);
}

void loop() {
  digitalWrite(3, HIGH);
  digitalWrite(3, LOW);

  digitalWrite(13, HIGH);
  delay(100);
  digitalWrite(13, LOW);
  delay(100);
}
