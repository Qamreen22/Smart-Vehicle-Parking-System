#define BLYNK_TEMPLATE_ID "TMPL3sx7MxDYJ"
#define BLYNK_TEMPLATE_NAME "MyNodeMCU"
#define BLYNK_FIRMWARE_VERSION "0.1.0"

#define BLYNK_PRINT Serial // Debug print to Serial Monitor

#include "BlynkEdgent.h"
#include <Arduino.h>

BlynkTimer timer;

#define LED_V0 V0
#define LED_V1 V1
#define LED_V2 V2
#define LED_V3 V3
#define LED_V4 V4
#define LED_V5 V5

String inputString = "";         // A String to hold incoming data
bool stringComplete = false;     // Whether the string is complete

void setup() {
  Serial.begin(9600);             // Initialize serial communication
  inputString.reserve(200);       // Reserve 200 bytes for the inputString
  BlynkEdgent.begin();            // Start Blynk
  timer.setInterval(1000L, checkParkingStatus); // Check parking status every second
}

void checkParkingStatus() {
  if (stringComplete) {
    if (inputString.length() == 6) { // Expecting 6 characters for the 6 parking slots
      int S1 = inputString.charAt(0) - '0';
      int S2 = inputString.charAt(1) - '0';
      int S3 = inputString.charAt(2) - '0';
      int S4 = inputString.charAt(3) - '0';
      int S5 = inputString.charAt(4) - '0';
      int S6 = inputString.charAt(5) - '0';

      // Write the values to the Blynk virtual pins
      Blynk.virtualWrite(LED_V0, S1);
      Blynk.virtualWrite(LED_V1, S2);
      Blynk.virtualWrite(LED_V2, S3);
      Blynk.virtualWrite(LED_V3, S4);
      Blynk.virtualWrite(LED_V4, S5);
      Blynk.virtualWrite(LED_V5, S6);
    }

    // Clear the string:
    inputString = "";
    stringComplete = false;
  }
}

void serialEvent() {
  while (Serial.available()) {
    // Get the new byte:
    char inChar = (char)Serial.read();
    // Add it to the inputString:
    inputString += inChar;
    // If the incoming character is a newline, set a flag:
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}

void loop() {
  BlynkEdgent.run(); // Run Blynk
  timer.run();       // Run the timer
}