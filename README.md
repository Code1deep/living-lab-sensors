# living-lab-sensors – Code ESP32 pour aquaponie

[![Licence](https://img.shields.io/badge/Licence-MIT-blue.svg)](LICENSE)
[![PlatformIO](https://img.shields.io/badge/PlatformIO-Professional-orange.svg)](https://platformio.org)

## Écosystème IoT intégré

Ce dépôt fait partie d'un système complet de monitoring intelligent pour mon Living Lab aquaponique.

**Architecture :**

| Composant | Dépôt | Rôle |
|-----------|-------|------|
| Acquisition | `living-lab-sensors` (ce dépôt) | Captation données réelles (ESP32) |
| Transport | Broker MQTT (EMQX) | Topic: `productique/bdi/sensors` |
| Traitement | `BDI-prototype` | Collecte, simulation, intelligence |

## Matériel requis

- ESP32 (node MCU)
- Capteurs Atlas Scientific (pH, EC, température)
- Connexion WiFi

## Structure du dépôt

- `calibration/` : Scripts de calibration des capteurs
- `mqtt_publish/` : Publication des données vers broker
- `watchdog/` : Redémarrage automatique

## Utilisation
```bash
pio run --target upload


## Installation (PlatformIO)

```bash
# Cloner le dépôt
git clone https://github.com/Code1deep/living-lab-sensors.git
cd living-lab-sensors

# Compiler et flasher l'ESP32
pio run --target upload

# Monitoring série
pio device monitor
