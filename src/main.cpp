#include <Arduino.h>
#include <SPI.h>

#define SS_PIN D8 // GPIO15 - Chip Select pin

void setup() {
  Serial.begin(115200);
  SPI.begin();                    // Initialize SPI Master
  pinMode(SS_PIN, OUTPUT);
  digitalWrite(SS_PIN, HIGH);     // Deselect slave initially
  SPI.setClockDivider(SPI_CLOCK_DIV64); // Safe communication speed

  Serial.println("\n--- SPI Master Initialized ---");
}

void loop() {
  String textToSend = "Hello ESP32-S3! SPI";
  size_t length = textToSend.length();

  Serial.print("Sending to Target: ");
  Serial.println(textToSend);

  // --- Transaction 1: Send string to Slave ---
  digitalWrite(SS_PIN, LOW);
  for (size_t i = 0; i < length; i++) {
    SPI.transfer(textToSend[i]);
  }
  digitalWrite(SS_PIN, HIGH);

  // Allow Slave a moment to process and load response buffer
  delay(50);

  // --- Transaction 2: Read string back from Slave ---
  digitalWrite(SS_PIN, LOW);
  String receivedString = "";
  for (size_t i = 0; i < length; i++) {
    char c = SPI.transfer(0x00); // Send dummy byte to clock data back
    receivedString += c;
  }
  digitalWrite(SS_PIN, HIGH);

  Serial.print("Received from Target: ");
  Serial.println(receivedString);
  Serial.println("----------------------------------------");

  delay(3000);
}