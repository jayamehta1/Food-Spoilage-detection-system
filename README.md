# IoT Food Spoilage Monitoring System

This project is an **IoT-based food spoilage detector** using Arduino UNO, MQ-3 gas sensor, DHT11 sensor, and ESP8266 WiFi module.  
It continuously monitors **volatile gases**, **temperature**, and **humidity**, then uploads data to [ThingSpeak](https://thingspeak.com/) for real-time tracking and spoilage prediction.

---

## Features
- Detects **volatile gases (ethanol, alcohol vapors, spoilage gases)** from food using MQ-3.  
- Tracks **temperature** and **humidity**, which are critical spoilage factors.  
- Uploads sensor readings to **ThingSpeak Cloud** every 20 seconds.  
- Can be extended to send alerts when food spoilage thresholds are reached.  

---

## Hardware Requirements
- Arduino UNO (or compatible board)  
- ESP8266 WiFi Module (AT firmware)  
- MQ-3 Gas Sensor (alcohol/volatile gas detection)  
- DHT11 Temperature & Humidity Sensor  
- Breadboard, jumper wires, USB cable  
