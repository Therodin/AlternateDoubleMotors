#include <Arduino.h>
#include <Espalexa.h>
#include <ESP8266WiFi.h>

// Define your WiFi credentials
const char* ssid = "YourWiFiSSID";
const char* password = "YourWiFiPassword";

// Define your device names
const char* deviceName1 = "LED1";
const char* deviceName2 = "LED2";

// Define the pins for controlling the LEDs
const int ledPin1 = D1; // Change D1 to the GPIO pin you're using for LED1
const int ledPin2 = D2; // Change D2 to the GPIO pin you're using for LED2

// Initialize the Espalexa object
Espalexa espalexa;

// Callback function to handle device state changes for LED1
void onDevice1StateChange(uint8_t newState) {
  if (newState == 0) {
    // Device turned off
    digitalWrite(ledPin1, LOW);
  } else {
    // Device turned on
    digitalWrite(ledPin1, HIGH);
    // Turn off LED2
    digitalWrite(ledPin2, LOW);
    // Update Espalexa state for LED2
    espalexa.setDeviceState(deviceName2, 0);
  }
}

// Callback function to handle device state changes for LED2
void onDevice2StateChange(uint8_t newState) {
  if (newState == 0) {
    // Device turned off
    digitalWrite(ledPin2, LOW);
  } else {
    // Device turned on
    digitalWrite(ledPin2, HIGH);
    // Turn off LED1
    digitalWrite(ledPin1, LOW);
    // Update Espalexa state for LED1
    espalexa.setDeviceState(deviceName1, 0);
  }
}

void setup() {
  // Initialize Serial communication for debugging
  Serial.begin(115200);

  // Connect to WiFi
  Serial.println("Connecting to WiFi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected!");

  // Set up the LED pins
  pinMode(ledPin1, OUTPUT);
  digitalWrite(ledPin1, LOW); // Led começa off
  pinMode(ledPin2, OUTPUT);
  digitalWrite(ledPin2, LOW); // Led começa off

  // Add the devices to Espalexa
  espalexa.addDevice(deviceName1, onDevice1StateChange);
  espalexa.addDevice(deviceName2, onDevice2StateChange);

  // Start the Espalexa server
  espalexa.begin();
}

void loop() {
  // Handle Espalexa requests
  espalexa.loop();
}
