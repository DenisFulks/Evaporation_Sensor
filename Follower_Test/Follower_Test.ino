void setup() {
  pinMode(13, OUTPUT);
  pinMode(3, INPUT);
}

void loop() {
  while(digitalRead(3) == LOW) {}

  digitalWrite(13, HIGH);
  delay(100);
  digitalWrite(13, LOW);
  delay(100);
}
