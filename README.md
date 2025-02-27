## ESP32 Project with Ultrasonic Sensor and HTTP Request

This project uses an **ESP32** with an **HC-SR04 ultrasonic sensor** to measure distances. When the measured distance is greater than 50 cm, the ESP32 makes an HTTP request to a specific route. Additionally, the Wi-Fi connection status is displayed in the Serial Monitor.

### Files

- `sensor_wifi.ino`: Main source code for the ultrasonic sensor functionality and HTTP request with Wi-Fi status.

### Functionality

1. The **ultrasonic sensor** is used to measure the distance.
2. When the **measured distance** is greater than 50 cm, an **HTTP GET request** is sent to the URL `www.myapitest/notifications`.
3. The **Wi-Fi connection status** is displayed in the Serial Monitor.
4. If the Wi-Fi connection is successful, the device's **IP address** will be shown.

### Dependencies

- **WiFi.h**: Library for connecting the ESP32 to a Wi-Fi network.
- **HTTPClient.h**: Library for making HTTP requests.

### How to Use

1. Connect your **ESP32** to your computer.
2. Upload the `sensor_wifi.ino` code to your ESP32.
3. Open the **Serial Monitor** to view the Wi-Fi connection status and measured distance.
4. When the distance is greater than 50 cm, the ESP32 will make the HTTP request.

### Example Output in Serial Monitor

```bash
Connecting to REDE_2G
Wi-Fi connected!
IP Address: 192.168.1.10
Distance: 60.45 cm
HTTP Code: 200
JSON Response:
{
  "status": "success",
  "message": "Notification sent."
}
