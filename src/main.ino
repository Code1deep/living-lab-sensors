#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include "config.h"
#include <time.h> // Bibliothèque standard

WiFiClient espClient;
PubSubClient client(espClient);

const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 3600;      // Ajuste selon mon fuseau horaire (ex: 3600 pour UTC+1)
const int   daylightOffset_sec = 3600; // Ajuste pour l'heure d'été

void setup() {
  Serial.begin(115200);
  setup_wifi();
  
  // Initialisation du temps via NTP
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  Serial.println("Synchronisation du temps en cours...");
  
  client.setServer(MQTT_BROKER, 1883);
}

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connexion à ");
  Serial.println(WIFI_SSID);
  
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connecté");
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  
  publier_donnees();
  delay(5000);
}

void reconnect() {
  while (!client.connected()) {
    if (client.connect("ESP32_LivingLab")) {
      client.subscribe(MQTT_TOPIC);
    } else {
      delay(5000);
    }
  }
}

void publier_donnees() {
    // 1. Lecture capteur (simulation ou réel)
    float ph_value = 6.82; // À remplacer par fonction de lecture Atlas Scientific

    // 2. Création du document JSON
    JsonDocument doc;
    doc["sensor"] = "ph";
    doc["value"] = ph_value;
    doc["unit"] = "pH";
    doc["timestamp"] = getISOTimestamp(); // Utilisation du temps réel

    // 3. Sérialisation JSON
    char buffer[128];
    serializeJson(doc, buffer);
    client.publish(MQTT_TOPIC, buffer);
    Serial.println(buffer);

    // 4. Publication MQTT
    if (client.publish(MQTT_TOPIC, buffer)) {
        Serial.print("Données envoyées : ");
        Serial.println(buffer);
    } else {
        Serial.println("Échec de la publication MQTT");
    }
}
String getISOTimestamp() {
    struct tm timeinfo;
    if(!getLocalTime(&timeinfo)){
        return "NTP_Error";
    }
    char buffer[25];
    // Format: 2026-04-24T10:00:00Z
    strftime(buffer, sizeof(buffer), "%Y-%m-%dT%H:%M:%SZ", &timeinfo);
    return String(buffer);
}

