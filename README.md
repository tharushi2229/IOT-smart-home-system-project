# Smart Home System (Arduino)

This project is an **Arduino-based Smart Home System** that integrates multiple sensors to enhance safety and automation. It detects motion, light intensity, gas leaks, and object distance, while responding with LEDs, a buzzer, and a servo motor.

---

## 🚀 Features

* **Ultrasonic Sensor** (HC-SR04): Detects objects within a range and triggers an LED.
* **PIR Motion Sensor**: Detects human movement and activates an LED.
* **Gas Sensor (MQ-series)**:

  * Detects presence of harmful gases.
  * Activates warning LED and buzzer.
  * Controls a **servo motor** (e.g., to close a gas valve).
* **LDR Sensor**: Measures light intensity and switches an LED accordingly.
* **Piezo Buzzer**: Alerts in case of gas leakage.

---

## 🛠️ Hardware Requirements

* Arduino UNO (or compatible)
* Ultrasonic sensor (HC-SR04)
* PIR motion sensor
* Gas sensor (MQ-2/MQ-5, etc.)
* LDR (Light Dependent Resistor)
* Servo motor (e.g., SG90)
* Piezo buzzer
* LEDs (various colors)
* Resistors and jumper wires
* Breadboard / PCB

---

## 🔌 Pin Connections

| Component           | Pin |
| ------------------- | --- |
| Ultrasonic Trigger  | 2   |
| Ultrasonic Echo     | 4   |
| Ultrasonic LED      | 7   |
| PIR Sensor          | 8   |
| PIR LED             | 9   |
| Gas Sensor (Analog) | A0  |
| Gas LED (Normal)    | 11  |
| Gas LED (Warning)   | 12  |
| Piezo Buzzer        | 6   |
| LDR Sensor          | A1  |
| LDR LED             | 10  |
| Servo Motor         | 5   |

---

## ⚙️ How It Works

1. **Ultrasonic Sensor**: Measures distance. If an object is close, the ultrasonic LED turns ON.
2. **PIR Sensor**: Detects motion and turns ON the PIR LED.
3. **Gas Sensor**: If gas levels exceed a threshold:

   * Warning LED and buzzer activate.
   * Servo motor rotates (e.g., to shut off a gas valve).
4. **LDR Sensor**: Detects ambient light and controls LED brightness.

---

## 📂 Project Structure

```
smart_home_system1.ino   # Main Arduino code
README.md                # Project documentation
```

---

## ▶️ Getting Started

1. Clone this repository:

   ```bash
   git clone https://github.com/yourusername/smart-home-system.git
   ```
2. Open `smart_home_system1.ino` in the **Arduino IDE**.
3. Select your Arduino board and COM port.
4. Upload the code and connect the components.

---

## 📊 Future Improvements

* Add **IoT (WiFi/ESP8266/ESP32)** to monitor sensors remotely.
* Integrate with a **mobile app** or **Blynk dashboard**.
* Add **temperature & humidity sensors** (DHT11/DHT22).
* Store sensor logs on **SD card**.

---

## 📜 License

This project is licensed under the MIT License. Feel free to use and modify.
