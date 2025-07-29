<div align="center">

<img src="https://img.icons8.com/fluency/96/light-on.png" width="80" alt="Smart Light Icon" />

# IRCS –  IoT Remote Control Switch
**Smartphone-controlled 220V appliance switch via ESP8266.**



[![Platform](https://img.shields.io/badge/platform-ESP8266-black.svg)](#hardware)
[![Built With](https://img.shields.io/badge/built%20with-C++%20%7C%20Arduino-purple.svg)](https://www.arduino.cc/)
[![Control Method](https://img.shields.io/badge/control%20method-Web%20Server-blue.svg)](#how-it-works)
[![Application](https://img.shields.io/badge/application-Home%20Automation-green.svg)](#introduction)
[![GitHub Stars](https://img.shields.io/github/stars/Farnaztr/IoT-Remote-Control-Switch?style=social)](https://github.com/Farnaztr/IoT-Remote-Control-Switch/stargazers)

</div>

---

## Introduction

Have you ever wished you could control your home lights or appliances remotely, using just your smartphone, without needing any intermediate device like a dedicated hub or a computer always running? The **IoT Remote Control Switch** project does exactly that!

By leveraging a NodeMCU (ESP8266) board and a relay module, you can easily transform any 220V electrical appliance into a smart device, controllable via a simple web page in your phone's browser. This project operates completely autonomously — once programmed, it requires no further connection to a laptop or PC.

This project is perfect for beginners in IoT and home automation, offering a practical and rewarding experience.

---

## Key Features

- **Wireless Control:** Turn your electrical appliances ON/OFF over Wi-Fi.
- **Standalone Operation:** No need for a laptop or intermediary server after initial programming.
- **Simple Web Interface:** Minimalist and user-friendly interface accessible via any smartphone browser.
- **Cost-Effective:** Utilizes affordable and readily available electronic components.
- **Scalable:** Provides a solid foundation for more complex IoT projects.
- **Basic Security:** Avoids exposing sensitive Wi-Fi credentials in public code.
- **Cross-Platform Access:** Control from any device (phone, tablet, PC) on the same Wi-Fi network.

---

##  How It Works

This project uses a **NodeMCU ESP8266** board configured as a mini web server:

1. **Wi-Fi Connection:** On power-up, the NodeMCU connects to your home Wi-Fi network using stored credentials.
2. **Internal Web Server:** The board runs a small embedded HTTP server.
3. **Control Page:** When you enter the NodeMCU's IP in your browser, it serves a control page.
4. **HTTP Commands:** ON/OFF buttons send HTTP GET requests to the board.
5. **GPIO Control:** The board sets the designated GPIO pin to HIGH or LOW based on request.
6. **Relay Activation:** Relay switches the connected 220V appliance accordingly.

---

## Project Demonstration
📺[IoT Remote Control Switch(Video)](https://github.com/Farnaztr/IoT-Remote-Control-Switch/blob/main/IMG_6257.MOV)

---

## 📸 Project Photos

<img src="5785234327267821675.jpg" alt="My Setup" width="300"/>  <img src="5785234327267821673.jpg" alt="My Setup" width="300"/>


- Assembled NodeMCU + Relay Module
- Relay + Appliance Setup
- Final Installation in Enclosure

---

## Components Required

| Component                               | Quantity |
|-----------------------------------------|----------|
| NodeMCU ESP8266 Board (ESP-12E Module)  | 1        |
| Single-Channel Relay Module (5V)        | 1        |
| Micro-USB Cable                         | 1        |
| 5V Power Adapter (1A–2A recommended)    | 1        |
| Jumper Wires (Male-Female)              | as needed|
| 220V Light Bulb / Appliance             | 1        |
| Plastic Electrical Enclosure (crucial) | 1        |

---

## 🔌 Wiring Diagram

**Low Voltage: NodeMCU → Relay Module**

- `VIN` → `VCC`
- `GND` → `GND`
- `D8 (GPIO15)` → `IN` *(RELAY_PIN)*

**High Voltage: Relay Module → 220V Appliance**

- Cut the **Live (L)** wire from the wall outlet.
  - One end → `COM` on Relay
  - Other end → `NO` (Normally Open) on Relay
- **Neutral (N)** goes directly from wall to appliance.

> ⚠️ **Safety First:** Always disconnect power before wiring. If unsure, ask an electrician!


---

## 💻 Software Setup

### 1. Preparing the Arduino IDE

Install the ESP8266 Board Support:

- Open **Arduino IDE** → File → Preferences  
- In *Additional Board URLs* paste:

```
http://arduino.esp8266.com/stable/package_esp8266com_index.json
```

- Go to Tools → Board → Boards Manager → Search "`esp8266`" → Install **ESP8266 by ESP8266 Community**

Required Libraries (auto-installed with board package):

- `ESP8266WiFi.h`
- `ESP8266WebServer.h`

---

### 2. Uploading the Code

1. Open your `.ino` file in Arduino IDE.
2. Replace Wi-Fi credentials:

```cpp
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";
```

3. Check GPIO Relay Pin:

```cpp
const int RELAY_PIN = D8;
```

> If relay logic is reversed, flip HIGH/LOW values in `digitalWrite()`.

4. Select the board and port:

- Board: **NodeMCU 1.0 (ESP-12E Module)**
- Port: **COMx** (whichever matches your device)

5. Upload the sketch using the ▶️ Upload button.

---

## 📱 Using the Switch

1. Open **Serial Monitor** (baud: 115200) after upload.
2. Wait for this message:

```text
Connected! IP address: 192.168.X.X
```

3. Unplug USB from your laptop.
4. Power NodeMCU using a 5V phone charger.
5. On your phone (connected to the same Wi-Fi), open:

```
http://192.168.X.X
```

6. Use the web interface to turn your appliance ON/OFF.

---

## ⚠️ Safety Precautions

- ⚡ **220V is dangerous! Always disconnect power before wiring.**
- Use a plastic **electrical enclosure** to avoid electric shock.
- Double-check wiring against the **relay module’s datasheet**.
- Never touch the relay or wires when the system is powered.
- If unsure, consult a qualified electrician.

---

✍️ Made by [Farnaz](https://github.com/Farnaztr)
