#include <WiFi.h>
#include <ThingSpeak.h>

// Wi-Fi Credentials
const char* ssid = "";
const char* password = "";

// ThingSpeak API Information
unsigned long channelID = ;  // Replace with your ThingSpeak Channel ID
const char* apiKey = ""; // Read API Key

WiFiClient client;
int ledPin = 2; // LED connected to GPIO 2

void setup() {
    Serial.begin(115200);
    pinMode(ledPin, OUTPUT);
    digitalWrite(ledPin, LOW); // Initially OFF

    // Connect to Wi-Fi
    WiFi.begin(ssid, password);
    Serial.print("Connecting to WiFi...");
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(1000);
    }
    Serial.println("\nConnected to WiFi!");

    // Initialize ThingSpeak
    ThingSpeak.begin(client);
}

void loop() {
    if (WiFi.status() == WL_CONNECTED) {
        int ledState = ThingSpeak.readIntField(channelID, 1, apiKey); // Read field 1

        if (ledState == 0) {
            digitalWrite(ledPin, LOW); // Turn OFF LED
            Serial.println("LED OFF");
        } else if (ledState == 1) {
            digitalWrite(ledPin, HIGH); // Turn ON LED
            Serial.println("LED ON");
        } else {
            Serial.println("Failed to read data from ThingSpeak");
        }
    }

    delay(5000); // Check ThingSpeak every 5 seconds
}
