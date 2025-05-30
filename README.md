README: Car Parking System (Arduino-based)
✅ Overview
This project is an automated car parking system using Arduino, LCD display, IR sensors, and servos. It manages car entry and exit based on available parking space.

🔧 Components
Arduino Uno/Nano

16x2 LCD (I2C interface)

2x IR sensors (for detecting entry/exit)

2x Servo motors (for gates)

LEDs (for entry/exit indicators)

Jumper wires, breadboard

⚙️ Pin Configuration
Component	Arduino Pin
IR Sensor 1	D2
IR Sensor 2	D5
Servo 1 (entry gate)	D8
Servo 2 (exit gate)	D9
Entry Green LED	D3
Entry Red LED	D4
Exit Green LED	D6
Exit Red LED	D7

📟 LCD Display
Line 1: Total number of parking slots

Line 2: Available spaces

🔁 Logic
When IR sensor 1 is triggered and space is available:

Entry gate opens, space count decreases.

When IR sensor 2 is triggered:

Exit gate opens, space count increases.

If no space, "Sorry no space" is displayed.

After entry and exit, gates close automatically.

🧪 Usage
Upload code to Arduino.

Power up the circuit.

Use objects to simulate vehicles over IR sensors.

Watch the LCD update and gates open/close accordingly.
