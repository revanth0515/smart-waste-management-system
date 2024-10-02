#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <HTTPClient.h>

// Replace with your WiFi credentials
const char* ssid = "your_ssid";
const char* password = "your_password";

// Replace with your database URL and credentials
const char* database_url = "https://your_database_url";
const char* username = "your_username";
const char* password = "your_password";

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("Connected to WiFi");
}

void loop() {
  // Read sensor data
  int ultrasonicValue = analogRead(A0);
  int temperatureValue = analogRead(A1);
  int smokeValue = analogRead(A2);

  // Send data to database
  HTTPClient http;
  http.begin(database_url);
  http.addHeader("Content-Type", "application/json");

  String data = "{\"ultrasonicValue\":" + String(ultrasonicValue) + ",\"temperatureValue\":" + String(temperatureValue) + ",\"smokeValue\":" + String(smokeValue) + "}";
  int httpCode = http.POST(data);

  if (httpCode == HTTP_CODE_OK) {
    Serial.println("Data sent successfully");
  } else {
    Serial.print("Error: ");
    Serial.println(httpCode);
  }

  http.end();

  delay(1000);
}
