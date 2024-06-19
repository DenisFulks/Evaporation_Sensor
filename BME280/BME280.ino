#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

Adafruit_BME280 bme;

// Pins
#define follower 2

// Data
unsigned int cycle = 0;
unsigned int n = 100;

// Variables
float temp;
float pressure;
float humidity;
unsigned int startTime;

void setup() {
  Serial.begin(9600);

  pinMode(follower, INPUT);

  if (!bme.begin(0x76)){
    Serial.println("Could not find BME 280");
    while(true);
  }

  Serial.println("BME Follower Boot Complete");
  Serial.println("Waiting for Start Command...");

  for (int i = 0; i < n; i++) {
    while(digitalRead(follower) == LOW) {}
    delayMicroseconds(10);

    // Reads atmospheric data
    temp = bme.readTemperature();
    pressure = bme.readPressure();
    humidity = bme.readHumidity();

    Serial.print(temp, 0);
    Serial.print(", ");
    Serial.print(pressure / 1000, 3);
    Serial.print(", ");
    Serial.println(humidity, 0);
  }

  startTime = millis();
  Serial.println();
}

void loop() {
  while(digitalRead(follower) == LOW) {}

  // Reads atmospheric data
  temp = bme.readTemperature();
  pressure = bme.readPressure();
  humidity = bme.readHumidity();

  Serial.print(millis() - startTime);
  Serial.print(", ");
  Serial.print(cycle);
  Serial.print(", ");
  Serial.print(temp, 0);
  Serial.print(", ");
  Serial.print(pressure / 1000, 3);
  Serial.print(", ");
  Serial.println(humidity, 0);
}
