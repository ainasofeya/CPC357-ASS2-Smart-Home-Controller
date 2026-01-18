** Smart Home Controller
An event-driven IoT system that provides remote lighting control and an emergency siren alert. This project demonstrates a complete 5-layer IoT architecture integrating an ESP32 edge device with Google Cloud Platform (GCP) and a web-based dashboard.

🚀 Features
Remote Light Control: Toggle a physical LED via a cloud-based web application.

Security Siren: Trigger a wailing siren effect on a built-in piezo buzzer.

Real-time Synchronization: Low-latency bidirectional communication using Firebase RTDB.

Secure Communication: Full HTTPS/SSL encryption with NTP time synchronization.

State-Change Logic: Efficient serial monitoring that only logs data when status changes occur.

🏗️ System Architecture
The project is structured into five functional layers:

Perception Layer: ESP32 Microcontroller, LED (GPIO 5), and Piezo Buzzer (GPIO 12).

Network Layer: WiFi connectivity (WPA2) and NTP time sync for SSL validation.

Middleware Layer: Firebase Realtime Database (GCP) and Firebase Client Library.

Application Layer: Smart Lighting and Security Alarm web services.

Business Layer: Firebase Authentication (IAM) and system governance policies.

🛠️ Hardware Requirements
Microcontroller: ESP32 (DevKit V1 or similar)

Light Actuator: 1x LED, 1x 220Ω Resistor

Audio Actuator: Built-in Piezo Buzzer (GPIO 12)

Connection: Micro USB cable for power and programming


📂 Development Steps
Hardware Connection: Interfacing actuators to GPIO 5 and 12.

Code Structure: Modular Arduino sketch with secure credential management.

Authentication: Implementing IAM via Firebase Auth.

Connectivity: Establishing WPA2 WiFi and SSL tunnels.

Synchronization: Using NTP to align local time for token validation.

Web App: Deploying a static HTML/JS dashboard via GCP Cloud Storage.

📝 Usage
Clone the repository.

Update the WIFI_SSID, WIFI_PASSWORD, API_KEY, and DATABASE_URL in the .ino file.

Upload the code to your ESP32.

Open the Serial Monitor at 115200 baud to view system status.

Use the Web Dashboard to toggle:

/lights/light1 (Boolean)

/alarm/state (Boolean)
