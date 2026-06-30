
# Nebras: Interactive Friendly Robot

Nebras is an intelligent, interactive robot designed to bridge the gap between AI-driven conversational agents and hardware automation. Built with a charming and friendly personality, Nebras leverages advanced Generative AI to communicate naturally in the Saudi Arabic dialect while performing synchronized physical gestures. 

The project employs a hybrid architecture, using **Python** as the high-level cognitive "brain" (managing NLP, speech-to-text, and Generative AI inference) and **Arduino** as the real-time hardware controller to execute smooth physical movements and handle sensor-driven edge interruptions.

---

##  Key Features

* **Generative AI Conversations:** Powered by Google's `gemini-2.5-flash` model, allowing natural, context-aware dialogue tailored to specific roles and regional dialects (Saudi Arabic).
* **Audio-Visual UI Elements:** Uses localized audio cues (`listen.mp3`, `convert.mp3`) via `pygame` to intuitively signal the robot's state to the user.
* **Dynamic Gesture Generation:** Synchronizes text output with dynamic non-verbal actions:
    * **Greeting Sequence (`hello_gesture`):** Triggered automatically upon detecting conversational openings.
    * **Expressive Feedback (`confused_movement`):** Mimics human confusion using head tilt adjustments when speech recognition fails or connection drops.
    * **Synchronized Entertainment (`dance_and_sing_gesture`):** An asynchronous multimedia state executing continuous motor oscillations during audio playback.
* **Smooth Servo Interpolation:** Implements a linear interpolation stepping algorithm (`move_servo`) rather than raw step jumps to guarantee fluid, lifelike mechanical adjustments and avoid gear wear.
* **Gesture-Based Hardware Override:** Utilizes an Infrared (IR) proximity sensor to count user hand-waves. Upon detecting the physical gesture sequence, the hardware temporarily overrides Python serial instructions to execute an independent mechanical response.

---

##  System Architecture & Workflow


1.  **Input:** The robot listens via a local microphone using Google's Speech Recognition API.
2.  **Cognition:** Text is formatted into a system prompt instructing Gemini to act as a personal assistant, routing intents via structural flags (`[DANCE]`, `[SONG]`).
3.  **Execution:** Parsing logic strips the internal tags, converts text to audio utilizing Google Text-to-Speech (`gTTS`), and writes multi-channel positional matrices concurrently to the Arduino via Serial communication.
4. **Hardware Override:** If the user triggers the IR sensor sequentially, the Arduino bypasses incoming serial commands to prioritize immediate local interactive gestures.

---

## Tech Stack

### Software
* **Language:** Python 3.10+
* **AI Models & APIs:** Google GenAI SDK (`gemini-2.5-flash`)
* **Libraries:** 
    * `speech_recognition` (Audio capture & conversion)
    * `gTTS` (Text-to-Speech synthesis)
    * `pygame` (Audio mixing, playback, and timing)
    * `cvzone.SerialModule` (High-level Serial communication)

### Hardware Integration
* **Microcontroller:** Arduino Uno (or compatible)
* **Actuators:** 3 Servo Motors (Configured for Left Hand, Right Hand, and Head alignment)
* **Sensors:** Infrared (IR) Proximity/Wave sensor

---

## Hardware Configuration & Pin Mapping

| Component | Arduino Pin | Description |
| :--- | :--- | :--- |
| **Left Servo (LServo)** | `Pin 8` | Controls left arm movement matrix received via Serial. |
| **Right Servo (RServo)** | `Pin 9` | Controls right arm movement (and manual hardware wave). |
| **Head Servo (HServo)** | `Pin 10` | Controls head orientation and horizontal panning. |
| **IR Proximity Sensor** | `Pin 2` | Detects obstacle reflections for gesture-based interruption. |

---

## Hardware Control Logic & Edge Detection

The embedded firmware runs a deterministic polling loop handling two main operations concurrently:
1. **Serial Packet Parsing:** Integrates `cvzone`'s `SerialData` protocol to unpack `int` arrays containing target angles `[LServo, RServo, HServo]` arriving via Python.
2. **The 3-Wave Interruption Loop:** Monitors the IR sensor using an state-change detection algorithm (**Edge Detection**). It implements a 200 ms software debounce delay to prevent erratic multi-triggering. Upon registering the consecutive hand waves, the firmware raises a safety flag (`wavingActive = true`), decoupling the hardware from Python serial writes to execute an independent mechanical sequence (`performWave`).

---

## Installation & Setup

### 1. Clone the Repository
```bash
git clone [https://github.com/your-username/Nebras-Robot.git](https://github.com/your-username/Nebras-Robot.git)
cd Nebras-Robot

```

### 2. Install Python Dependencies

```bash
pip install speech_recognition gTTS pygame google-genai cvzone

```

### 3. API Key Configuration

Replace the `MY_API_KEY` placeholder inside the main script with your authorized Gemini API Key:

```python
MY_API_KEY = "YOUR_GEMINI_API_KEY"

```

### 4. Hardware Compilation

1. Ensure your Arduino IDE has the **Servo** and **Cvzone** libraries installed.
2. Open the firmware sketch, select **Tools > Board > Arduino Uno**, and select the correct `COM` port.
3. Upload the sketch to the board. *(Note: Close any active Python execution loops while uploading to avoid COM port occupancy conflicts)*.

### 5. Directory Structure

Ensure your local assets match the following directory structure before running the Python script:

```text
├── Recources/
│   ├── listen.mp3
│   ├── convert.mp3
│   └── song.mpeg
├── Nebras_Firmware.ino
└── main.py

```

---

## 👥 Developers

Developed with pride by the students of the first Artificial Intelligence batch:

* Al-Anoud
* Shahad
* Nada
* Yara


