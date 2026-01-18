#include <WiFi.h>
#include <Firebase_ESP_Client.h>
#include <addons/TokenHelper.h>
#include <addons/RTDBHelper.h>
#include <time.h>

// WiFi & Firebase Credentials
#define WIFI_SSID ""        // SSID of nearest WiFi
#define WIFI_PASSWORD "" // WiFi Password
#define API_KEY "" // GCP API Key
#define DATABASE_URL ""  // Firebase RTDB URL
#define USER_EMAIL ""  // Email Authentication from GCP
#define USER_PASSWORD ""   // Password for email authentication

// Pins
const int lightPin = 5; 
const int buzzerPin = 12; // Built-in piezo buzzer pin

// Firebase Objects
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

void configTimeSync() {
  // Sync time using NTP (Pool.ntp.org)
  // 28800 is the offset for Malaysia (UTC+8)
  configTime(28800, 0, "pool.ntp.org", "time.nist.gov");
  Serial.print("Waiting for NTP time sync: ");
  time_t now = time(nullptr);
  while (now < 8 * 3600 * 2) {
    delay(500);
    Serial.print(".");
    now = time(nullptr);
  }
  Serial.println("\nTime synchronized!");
}

void playSiren() {
  // Rise up
  for (int freq = 600; freq <= 1200; freq += 10) {
    tone(buzzerPin, freq);
    delay(5); 
  }
  // Fall down
  for (int freq = 1200; freq >= 600; freq -= 10) {
    tone(buzzerPin, freq);
    delay(5);
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(lightPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  // WiFi Connection
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) { delay(500); }
  Serial.println("WiFi Connected");

  // ADD THIS LINE HERE:
  configTimeSync(); 

  config.api_key = API_KEY;
  config.database_url = DATABASE_URL;
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;

  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}

void loop() {
  if (Firebase.ready()) {
    
    // 1. LIGHT CONTROL (Path: /lights/light1)
    if (Firebase.RTDB.getBool(&fbdo, "/lights/light1")) {
      bool ledState = fbdo.boolData();
      digitalWrite(lightPin, ledState ? HIGH : LOW);
      Serial.print("Light status: ");
      Serial.println(ledState ? "ON" : "OFF");
    }

    // 2. ALARM CONTROL (Path: /alarm/state)
    if (Firebase.RTDB.getBool(&fbdo, "/alarm/state")) {
      bool alarmActive = fbdo.boolData();
      if (fbdo.boolData() == true) {
        Serial.println("SIREN ON");
        playSiren(); // This function handles the oscillation
      } else {
        noTone(buzzerPin);
      }
    }

  } else {
    Serial.println("Waiting for Firebase...");
  }
  
  delay(200); // Short delay to keep the loop responsive
}

