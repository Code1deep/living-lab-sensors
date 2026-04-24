# living-lab-sensors – Code ESP32 pour aquaponie

## Matériel
- ESP32
- Capteurs Atlas Scientific (pH, température, EC)
- Protocole MQTT

## Structure
- `calibration/` : Scripts de calibration des capteurs
- `mqtt_publish/` : Publication des données vers broker
- `watchdog/` : Redémarrage automatique

## Utilisation
```bash
pio run --target upload
