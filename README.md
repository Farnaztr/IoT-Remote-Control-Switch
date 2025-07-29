# 💡 IoT Remote Control Switch 

Control your home lights or appliances remotely using your phone or computer, through a simple web interface hosted on an ESP8266 NodeMCU. Once programmed, the device works completely standalone – no need for a laptop or internet connection afterward.

---

## Introduction

Have you ever wished you could control your home lights or appliances remotely, using just your smartphone, without needing any intermediate device like a dedicated hub or a computer always running? The "IoT Remote Control Switch" project does exactly that!

By leveraging a NodeMCU (ESP8266) board and a relay module, you can easily transform any 220V electrical appliance into a smart device, controllable via a simple web page in your phone's browser. This project operates completely autonomously — once programmed, it requires no further connection to a laptop or PC.

This project is perfect for beginners in IoT and home automation, offering a practical and rewarding experience.

---

## Key Features

- **Wireless Control:** Turn your electrical appliances ON/OFF over Wi-Fi.
- **Standalone Operation:** No need for a laptop or an intermediary server after initial programming.
- **Simple Web Interface:** Minimalist and user-friendly interface accessible via any smartphone browser.
- **Cost-Effective:** Utilizes affordable and readily available electronic components.
- **Scalable:** Provides a solid foundation for more complex IoT projects.
- **Basic Security:** Avoids exposing sensitive Wi-Fi credentials in public code.
- **Cross-Platform Access:** Control from any device (phone, tablet, PC) on the same Wi-Fi network.

---

## How It Works

This project is based on the **"NodeMCU as a Web Server"** architecture:

1. **Wi-Fi Connection:** On power-up, the NodeMCU connects to your home Wi-Fi network using stored credentials.
2. **Internal Web Server:** The NodeMCU runs a small embedded HTTP server.
3. **Serves Control Page:** Entering the NodeMCU's IP in your browser loads a basic control page.
4. **Command Transmission:** Clicking the ON/OFF buttons sends HTTP GET requests to the NodeMCU.
5. **Relay Control:** NodeMCU sets the appropriate GPIO pin HIGH/LOW to activate the relay.
6. **220V Control:** The relay switches the appliance on or off by breaking or completing the 220V circuit.

---

## Project Demonstration

Watch this short video to see the IoT Remote Control Switch in action:

📺 YouTube: `https://www.youtube.com/watch?v=YOUR_VIDEO_ID`  


---

## Project Photos

- Assembled Board  
- Final Enclosure  
- In Action  

📷 *(Replace placeholders with your actual project photos.)*

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

**NodeMCU → Relay Module:**

- `VIN` → `VCC`
- `GND` → `GND`
- `D8 (GPIO15)` → `IN` *(RELAY_PIN)*

**Relay Module → 220V Appliance:**

- Cut **Live (L)** wire from the power source.
- One end → `COM` on Relay
- Other end → `NO` (Normally Open)
- **Neutral (N)** connects directly to the appliance.

> ⚠️ **SAFETY FIRST:** Disconnect mains power before wiring! Consult an electrician if unsure.

📷 `esp8266-relay-wiring-diagram.jpg`

---

## 💻 Software Setup

### 1. Preparing Arduino IDE

- Install **ESP8266 Board Support**:
  - File → Preferences → Add URL:  
    `http://arduino.esp8266.com/stable/package_esp8266com_index.json`
  - Then: Tools → Board → Boards Manager → Search `esp8266` → Install.

- Required Libraries:
  - `ESP8266WiFi.h`  
  - `ESP8266WebServer.h`  
  *(Usually auto-installed with the board package)*

---

### 2. Uploading the Code

- Open your `.ino` file in Arduino IDE.
- Replace credentials in these lines:

```cpp
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";
```
🔒 Important: Do not upload your real Wi-Fi credentials to GitHub!
