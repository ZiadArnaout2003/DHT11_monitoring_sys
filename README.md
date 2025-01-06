# Real-Time Temperature and Humidity Monitoring System  

This project monitors temperature and humidity in real time using an ESP32 microcontroller, a DHT11 sensor, and a web interface. It showcases live sensor data on a local network via an HTTP server.

## Table of Contents  
- [Overview](#overview)  
- [Features](#features)  
- [Project Structure](#project-structure)  
- [How It Works](#how-it-works)  
- [Setup Instructions](#setup-instructions)  
- [Important Notes](#important-notes)  
- [Future Improvements](#future-improvements)
- [Demo](#demo)

---

## Overview  
The system uses the ESP32 to gather temperature and humidity data, displaying it locally via:  
1. A connected LCD.  
2. A web interface accessed over a local network.

---

## Features  
- **Real-Time Updates**: Data is updated every 2 seconds on the web interface.  
- **Dual Temperature Units**: Displays temperature in both Celsius and Fahrenheit.  
- **Humidity Warnings**: Highlights high humidity levels (>80%) with a visual red glow.  
- **Local Network Access**: Data is accessible only within the same network as the ESP32.  

---

## Project Structure  
### Files and Their Functions  
- **index.html**  
  - Provides the structure of the web interface.  
  - Displays real-time temperature and humidity data.  

- **style.css**  
  - Styles the web interface with a modern, responsive design.  
  - Includes dynamic effects such as glowing indicators for high humidity.  

- **script.js**  
  - Fetches sensor data from the ESP32 server and updates the DOM in real time.  
  - Adds visual feedback for humidity thresholds using CSS class manipulation.  

- **ESP32_DHT11.ino**  
  - Contains the ESP32 firmware.  
  - Reads data from the DHT11 sensor and serves it via an HTTP server.  
  - Sends JSON responses to the web interface for seamless updates.  

---

## How It Works  
1. **Data Acquisition**:  
   - The ESP32 reads temperature (Celsius and Fahrenheit) and humidity from the DHT11 sensor.  
   - Values are processed and prepared for display.  

2. **Local HTTP Server**:  
   - ESP32 runs a local HTTP server.  
   - JSON data is served at the endpoint `/data`.  

3. **Data Transmission**:  
   - Data is transmitted via HTTP as a JSON object, e.g.:  
     ```json  
     {
       "temperature": 25.3,
       "temperatureF": 77.5,
       "humidity": 65.2
     }
     ```  

4. **Web Interface**:  
   - The browser fetches data every 2 seconds using JavaScript's `fetch()` function.  
   - The interface updates dynamically without reloading the page.  

5. **LCD Display**:  
   - The ESP32 also updates a connected LCD with temperature and humidity readings.  

---

## Setup Instructions  
1. **Hardware Requirements**:  
   - ESP32 microcontroller.  
   - DHT11 sensor.  
   - 16x2 LCD screen.  

2. **Connections**:  
   - Connect the DHT11 to GPIO 15 of the ESP32.  
   - Connect the LCD to GPIOs 2, 4, 5, 18, 19, and 21.  

3. **Software Setup**:  
   - Install the Arduino IDE with ESP32 board support.  
   - Add necessary libraries (`DHT` and `LiquidCrystal`).  

4. **Network Configuration**:  
   - Update the WiFi SSID and password in `ESP32_DHT11.ino`:  
     ```cpp  
     const char *ssid = "YOUR_WIFI_SSID";  
     const char *password = "YOUR_WIFI_PASSWORD";  
     ```  

5. **Deployment**:  
   - Flash the ESP32 with the `.ino` file.  
   - Navigate to `http://<ESP32_IP_ADDRESS>/data` to view data in JSON format.  

---
## Demo

https://github.com/user-attachments/assets/ce963382-dbb5-40dd-b1a8-5ee952c953ca



## Important Notes  
- **Local Access Only**:  
  - The system operates only within the local WiFi network. Remote access requires port forwarding or additional configurations.  

- **Cross-Origin Requests**:  
  - CORS headers (`Access-Control-Allow-Origin: *`) are added to allow browser access.  

- **Error Handling**:  
  - Sensor errors are logged in the serial monitor for debugging.  
## Future Improvements  
- Add a database to log historical data.  
- Implement a mobile-friendly UI.  
- Introduce MQTT for real-time updates over the internet.  
