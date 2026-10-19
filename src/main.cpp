#include <Arduino.h>
#include <SoftwareSerial.h>

// Define SoftwareSerial pins for NodeMCU to talk to ESP32-S3
// D2 (GPIO4) as RX, D1 (GPIO5) as TX
SoftwareSerial mySerial(D2, D1); 

void setup() {
  Serial.begin(115200);      // For PC Serial Monitor (USB)
  mySerial.begin(9600);     // For communication with ESP32-S3
  
  delay(1000);
  Serial.println("\n--- Serial Master Initialized ---");
}

void loop() {
  String textToSend = "Hello ESP32-S3! Serial";

  Serial.print("Sending to Target: ");
  Serial.println(textToSend);

  // 1. Send string to slave via Serial
  mySerial.println(textToSend);

  // Allow Target time to receive and echo back
  delay(100);

  // 2. Read response back from slave
  String receivedString = "";
  unsigned long startTime = millis();
  
  // Wait up to 500ms for response
  while (millis() - startTime < 500) {
    if (mySerial.available()) {
      receivedString = mySerial.readStringUntil('\n');
      receivedString.trim(); // Remove trailing newline/carriage return
      break;
    }
  }

  Serial.print("Received from Target: ");
  Serial.println(receivedString);
  Serial.println("----------------------------------------");

  delay(3000);
}