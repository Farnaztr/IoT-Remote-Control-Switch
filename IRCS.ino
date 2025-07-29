#include <ESP8266WiFi.h>      
#include <ESP8266WebServer.h> 
const char* ssid = "YOUR_WIFI_SSID";    
const char* password = "YOUR_WIFI_PASSWORD"; 

const int RELAY_PIN = D8; 

ESP8266WebServer server(80);

bool relayState = false; 

void sendCorsHeaders() {
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.sendHeader("Access-Control-Allow-Methods", "GET, POST, OPTIONS");
  server.sendHeader("Access-Control-Allow-Headers", "*");
}

void handleRoot() {
  String html = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>IoT Remote Control Switch</title>
    <link href="https://fonts.googleapis.com/css2?family=Poppins:wght@300;400;600&display=swap" rel="stylesheet">
    <style>
        :root {
            --primary-bg-color: #374e71; 
            --secondary-bg-color: #e3e7ed;
            --card-bg-color: #ffffff; 

            --primary-text-color: #34495e;
            --secondary-text-color: #689699;

            --on-button-color: #1abc9c;
            --on-button-hover: #16a085;

            --off-button-color: #e74c3c;
            --off-button-hover: #c0392b;

            --status-on-color: #2ecc71;
            --status-off-color: #e74c3c;

            --shadow-light: 0 4px 15px rgba(0, 0, 0, 0.08);
            --shadow-dark: 0 8px 25px rgba(0, 0, 0, 0.15);
        }

        body {
            font-family: 'Poppins', sans-serif;
            display: flex;
            flex-direction: column;
            justify-content: center;
            align-items: center;
            min-height: 100vh;
            margin: 0;
            background-color: var(--primary-bg-color);
            color: var(--primary-text-color);
            overflow: hidden;
            position: relative;
        }

        body::before, body::after {
            content: '';
            position: absolute;
            border-radius: 50%;
            opacity: 0.1;
            filter: blur(50px);
        }

        body::before {
            width: 300px;
            height: 300px;
            background-color: var(--on-button-color);
            top: -100px;
            left: -100px;
        }

        body::after {
            width: 400px;
            height: 400px;
            background-color: var(--off-button-color);
            bottom: -150px;
            right: -150px;
        }

        .container {
            background-color: var(--card-bg-color);
            padding: 40px 30px;
            border-radius: 18px;
            box-shadow: var(--shadow-light);
            text-align: center;
            width: 90%;
            max-width: 350px; 
            z-index: 10;
            position: relative;
            transform: translateY(0);
            transition: transform 0.3s ease-in-out;
        }

        .container:hover {
            transform: translateY(-5px);
            box-shadow: var(--shadow-dark);
        }

        h1 {
            color: var(--primary-text-color);
            margin-bottom: 30px;
            font-size: 2.2em; 
            font-weight: 600;
        }

        .status-display, .status-indicator {
            display: none; 
        }

        .button-group {
            display: flex;
            gap: 20px;
            justify-content: center;
            margin-bottom: 25px;
        }

        button {
            background-color: var(--on-button-color);
            color: white;
            padding: 15px 35px;
            border: none;
            border-radius: 10px;
            font-size: 1.2em;
            font-weight: 600;
            cursor: pointer;
            transition: background-color 0.3s ease, transform 0.2s ease, box-shadow 0.3s ease;
            flex: 1;
            box-shadow: 0 5px 15px rgba(0, 0, 0, 0.1);
        }

        button:hover {
            background-color: var(--on-button-hover);
            transform: translateY(-3px);
            box-shadow: 0 8px 20px rgba(0, 0, 0, 0.15);
        }

        button:active {
            transform: translateY(0);
            box-shadow: 0 3px 10px rgba(0, 0, 0, 0.1);
        }

        button.off-button {
            background-color: var(--off-button-color);
        }

        button.off-button:hover {
            background-color: var(--off-button-hover);
        }

        .message {
            display: none; 
        }

        @media (max-width: 600px) {
            .container {
                padding: 30px 20px;
                max-width: 95%; 
            }
            h1 {
                font-size: 1.8em; 
            }
            .button-group {
                flex-direction: column;
                gap: 15px;
            }
            button {
                width: 100%;
                padding: 12px 25px;
                font-size: 1.1em;
            }
        }
    </style>
</head>
<body>
    <div class="container">
        <h1>IoT Remote Control Switch</h1> 
        <div class="button-group">
            <button id="turnOnBtn">Turn On</button>
            <button id="turnOffBtn" class="off-button">Turn Off</button>
        </div>
    </div>

    <script>
        const turnOnBtn = document.getElementById('turnOnBtn');
        const turnOffBtn = document.getElementById('turnOffBtn');

        const NODEMCU_IP = window.location.origin; 

        async function sendControlCommand(action) {
            try {
                const response = await fetch(`${NODEMCU_IP}/${action}`, { method: 'GET' });

                if (!response.ok) {
                    console.error(`Failed to send ${action} command. NodeMCU responded with an error:`, response.status);
                }
            } catch (error) {
                console.error(`Network error sending ${action} command to NodeMCU:`, error);
            }
        }

        turnOnBtn.addEventListener('click', () => sendControlCommand('on'));
        turnOffBtn.addEventListener('click', () => sendControlCommand('off'));
    </script>
</body>
</html>
)rawliteral";
  sendCorsHeaders(); 
  server.send(200, "text/html", html); 
}

void handleOn() {
  digitalWrite(RELAY_PIN, HIGH); 
  relayState = true;
  Serial.println("Relay ON"); 
  sendCorsHeaders();
  server.send(200, "application/json", "{\"status\":\"success\", \"new_status\":\"on\"}");
}

void handleOff() {
  digitalWrite(RELAY_PIN, LOW); 
  relayState = false;
  Serial.println("Relay OFF"); 
  sendCorsHeaders();
  server.send(200, "application/json", "{\"status\":\"success\", \"new_status\":\"off\"}");
}

void handleStatus() {
  sendCorsHeaders();
  String state = relayState ? "on" : "off";
  Serial.print("Status requested: ");
  Serial.println(state);
  server.send(200, "application/json", "{\"status\":\"success\", \"new_status\":\"" + state + "\"}");
}

void handleNotFound() {
  sendCorsHeaders();
  server.send(404, "text/plain", "Not found");
}

void setup() {
  Serial.begin(115200); 
  delay(100); 
  Serial.println("\n--- NodeMCU Booting ---"); 
  Serial.print("Attempting to connect to WiFi: "); 
  Serial.println(ssid); 

  pinMode(RELAY_PIN, OUTPUT); 
  digitalWrite(RELAY_PIN, LOW); 
  relayState = false; 

  WiFi.begin(ssid, password); 

  int wifi_attempts = 0; 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    wifi_attempts++; 
    if (wifi_attempts > 20) { 
      Serial.println("\n--- WiFi Connection Failed! ---"); 
      Serial.print("WiFi Status: "); 
      Serial.println(WiFi.status()); 
      break; 
    }
  }
  
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nConnected to WiFi successfully!"); 
    Serial.print("NodeMCU IP address: "); 
    Serial.println(WiFi.localIP()); 
    server.on("/", handleRoot);          
    server.on("/on", handleOn);          
    server.on("/off", handleOff);        
    server.on("/get_status", handleStatus); 
    server.onNotFound(handleNotFound);   
    server.begin(); 
    Serial.println("HTTP server started on NodeMCU."); 
  } else {
    Serial.println("Failed to connect to WiFi. Web server not started."); 
  }
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) { 
    server.handleClient(); 
  }
}
