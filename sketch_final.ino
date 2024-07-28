#include <DHT.h>

#define DHTPIN 2      // DHT11 data pin connected to digital pin 2
#define DHTTYPE DHT11 // Define the type of DHT sensor

DHT dht(DHTPIN, DHTTYPE);

int sensor_pin = A0;       // Soil moisture sensor pin
int relay_pin = 7;         // Relay pin
int rainfall_pin = A1;     // Rainfall sensor pin

void setup() {
  Serial.begin(9600);
  pinMode(sensor_pin, INPUT);
  pinMode(relay_pin, OUTPUT);
  pinMode(rainfall_pin, INPUT);
  dht.begin();
}

void loop() {
  int sensor_data = analogRead(sensor_pin);
  int rainfall_data = analogRead(rainfall_pin);
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  Serial.print("Soil Moisture: ");
  Serial.print(sensor_data);
  Serial.print(" | Rainfall: ");
  Serial.print(rainfall_data);
  Serial.print(" | Humidity: ");
  Serial.print(humidity);
  Serial.print(" | Temperature: ");
  Serial.print(temperature);
  Serial.print("\t | ");

  // Rainfall detection
  if (rainfall_data < 500) {
    Serial.println("Rain detected, turning off the pump");
    digitalWrite(relay_pin, LOW);
  } else {
    // Soil moisture detection
    if (sensor_data > 950) {
      Serial.println("No moisture, Soil is dry");
      digitalWrite(relay_pin, HIGH);
    } else if (sensor_data >= 400 && sensor_data <= 950) {
      Serial.println("Some moisture, Soil is medium");
      digitalWrite(relay_pin, LOW);
    } else if (sensor_data < 400) {
      Serial.println("Soil is wet");
      digitalWrite(relay_pin, LOW);
    }
  }

  delay(2000); // Increased delay for better readability
}