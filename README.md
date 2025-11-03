# 🤖 Assistive Robot Project

This project aims to create an **Assistive Robot** that can safely navigate its environment, assist users, and communicate between multiple microcontrollers — specifically an **ESP32** and an **Arduino Nano BLE 33**. The robot includes environmental sensing, path tracking, and communication capabilities to support tasks such as harvesting, assistance, and environmental monitoring.

---

## 📁 Project Structure

| File / Folder | Description |
|----------------|-------------|
| **CAD/** | 3D model and design files for the robot chassis. |
| **ESP32-2.ino** | Code for the ESP32 microcontroller (main control). |
| **ESP32COM.ino** | Communication test code for ESP32. |
| **ESP32COM2.ino** | Alternate ESP32 communication version. |
| **NANOCOM2.ino** | Communication test code for Arduino Nano. |
| **NanoBLE33COM.ino** | Communication code for Arduino Nano BLE 33 Sense. |
| **Schematic Assistive Robot.png** | Circuit schematic showing connections between sensors, motors, and controllers. |
| **README.md** | This file — project overview and documentation. |
| **UserManual** | Demonstration of how to set up the assistive robot. |

---

## ⚙️ Hardware Components

- **ESP32** (main controller for Wi-Fi and logic)
- **Arduino Nano BLE 33 Sense** (sensor module)
- **Motor Driver (L298N / similar)**
- **Ultrasonic sensors** (for obstacle detection)
- **Power supply (Li-ion or USB)**
- **Chassis with wheels / rover base**

---

## 🔌 Communication Setup

The **ESP32** and **Nano BLE 33** communicate via **serial connection (UART)**:
- ESP32 TX → Nano RX  
- ESP32 RX → Nano TX  
- Common GND between both boards  

Baud rate: **115200 bps**  

Make sure to disconnect RX/TX when uploading new code.

---

## 🧠 Features

- Obstacle detection and navigation
- Wireless communication using ESP32
- Sensor monitoring ( distance)
- Modular firmware for easy updates

---

## 🧩 Schematic

![Schematic Assistive Robot](Schematic%20Assistive%20Robot.png)

---

##  CAD

<img width="925" height="562" alt="Robot CAD" src="https://github.com/user-attachments/assets/f77bfdb5-4d3d-4d39-96cb-40e8130b7048" />

---

##  Mo Robot

![Videoframe_20251103_151231_com huawei himovie overseas](https://github.com/user-attachments/assets/508a33a5-cf65-41d1-84b1-8118b4290048)




---

## 🚀 Getting Started

### 1️⃣ Upload Code
1. Flash the `NanoBLE33COM.ino` to the **Arduino Nano BLE 33 Sense**
2. Flash the `ESP32-2.ino` (or `ESP32COM.ino`) to the **ESP32**

### 2️⃣ Connect Hardware
- Ensure all sensors and communication lines match the schematic.
- Power both boards appropriately.

### 3️⃣ Test Communication
Open Serial Monitor on both boards and verify messages are exchanged correctly.

---

## 📚 Future Improvements

- Add AI-based path planning  
- Integrate camera or computer vision  
- Improve chassis design for better maneuverability  
    

---

## 👩🏽‍💻 Author
**Motshabi**  
Developed as part of an assistive robotics project to explore multi-controller communication and automation for community applications.

---



