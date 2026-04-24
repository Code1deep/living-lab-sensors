#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include "config.h"

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  Serial.begin(115200);
  setup_wifi();
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
    doc["timestamp"] = "2026-04-24T10:00:00Z"; // À remplacer par NTP

    // 3. Sérialisation JSON
    char buffer[256];
    serializeJson(doc, buffer);

    // 4. Publication MQTT
    if (client.publish(MQTT_TOPIC, buffer)) {
        Serial.print("Données envoyées : ");
        Serial.println(buffer);
    } else {
        Serial.println("Échec de la publication MQTT");
    }
}
