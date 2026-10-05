#include <Arduino.h>

#include <Wire.h>

#define TARGET_ADDR 0x08 // Target I2C address

void setup() {
  Serial.begin(115200);
  Wire.begin();                     // Default pins: D2 (SDA), D1 (SCL)
  Wire.setClock(100000);            // Standard 100kHz for reliable software I2C
  Wire.setClockStretchLimit(15000); // Allow target time to hold SCL LOW if busy

  Serial.println("\n--- I2C Controller Initialized ---");
}

void loop() {
  String textToSend = "Hello ESP8266! IS";

  Serial.print("Sending to Target: ");
  Serial.println(textToSend);

  // 1. Send the string byte-by-byte with small microsecond pauses
  Wire.beginTransmission(TARGET_ADDR);
  for (size_t i = 0; i < textToSend.length(); i++) {
    Wire.write(textToSend[i]);
  }
  uint8_t error = Wire.endTransmission();

  if (error != 0) {
    Serial.print("I2C Transmission Error: ");
    Serial.println(error);
  } else {
    Serial.println("Transmission successful!");
  }

  // Allow Target time to finish receive callback & reverse string
  delay(150);

  // 2. Request reversed string from Target
  int bytesToRequest = textToSend.length();
  int bytesReceived = Wire.requestFrom(TARGET_ADDR, bytesToRequest);

  String receivedString = "";
  while (Wire.available()) {
    char c = Wire.read();
    receivedString += c;
  }

  Serial.print("Received from Target: ");
  Serial.println(receivedString);
  Serial.println("----------------------------------------");

  delay(3000);
}
