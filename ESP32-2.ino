#include "BluetoothSerial.h"
#include <NewPing.h>   // ✅ Added for ultrasonic sensors

BluetoothSerial SerialBT;

// Ultrasonic sensors
#define TRIG_PIN1 23
#define ECHO_PIN1 22
#define TRIG_PIN2 21
#define ECHO_PIN2 19
#define MAX_DISTANCE 200   // cm

NewPing sonarL(TRIG_PIN1, ECHO_PIN1, MAX_DISTANCE);
NewPing sonarR(TRIG_PIN2, ECHO_PIN2, MAX_DISTANCE);

// LEDs
int redLED = 25, yellowLED = 26, greenLED = 27;
const int dangerDistance = 20;

// Communication timeout
const int ACK_TIMEOUT = 400;

void setup() {
  pinMode(redLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(greenLED, OUTPUT);

  Serial.begin(115200);                                // Debug to PC
  Serial2.begin(115200, SERIAL_8N1, 16, 17);           // RX2=16, TX2=17 (Hardware Serial)
  SerialBT.begin("Mo_Robot");                        // Bluetooth name
  delay(1000);

  Serial.println("✅ ESP32-WROOM-32 ready. Waiting for Nano...");
  SerialBT.println("✅ ESP32-WROOM-32 ready. Waiting for Nano...");
}

// ✅ Updated Distance Function using NewPing
long readUltrasonic(NewPing &sonar) {
  unsigned int distance = sonar.ping_cm();
  if (distance == 0) return -1;  // No echo detected
  return distance;
}

// Send command to Nano and wait for ACK
void sendToNano(char cmd) {
  Serial.print("➡️ Sending to Nano: ");
  Serial.println(cmd);

  Serial2.write(cmd);
  Serial2.println();
  Serial2.flush();

  unsigned long start = millis();
  bool ackReceived = false;

  while (millis() - start < ACK_TIMEOUT) {
    if (Serial2.available()) {
      String reply = Serial2.readStringUntil('\n');
      reply.trim();
      if (reply.indexOf("ACK") >= 0) {
        ackReceived = true;
        Serial.println("✅ ACK received.");
        break;
      } else {
        Serial.print("⚠️ Unexpected reply: ");
        Serial.println(reply);
      }
    }
  }

  if (!ackReceived) {
    Serial.println("❌ No ACK — retrying...");
    Serial2.write(cmd);
    Serial2.println();
    Serial2.flush();
  }
}

void loop() {
  // ---- Manual override via Bluetooth ----
  if (SerialBT.available()) {
    char manualCmd = SerialBT.read();
    sendToNano(manualCmd);
    return;
  }

  // ---- Autonomous mode ----
  long distL = readUltrasonic(sonarL);
  long distR = readUltrasonic(sonarR);

  // Debugging distances
  Serial.printf("L: %ld cm | R: %ld cm\n", distL, distR);

  // Ignore invalid readings (don't immediately stop)
  if (distL < 0 || distR < 0) {
    Serial.println("⚠️ Sensor glitch detected — ignoring reading.");
    digitalWrite(yellowLED, HIGH);
    delay(50);
    return;
  } else {
    digitalWrite(yellowLED, LOW);
  }

  // ---- Normal obstacle logic ----
  if (distL < dangerDistance && distR < dangerDistance) {
    digitalWrite(redLED, HIGH);
    digitalWrite(greenLED, LOW);
    sendToNano('S'); delay(100);
    sendToNano('B'); delay(400);
    sendToNano('R'); delay(400);
    sendToNano('S');
  } 
  else if (distL < dangerDistance) {
    digitalWrite(redLED, HIGH);
    digitalWrite(greenLED, LOW);
    sendToNano('S'); delay(100);
    sendToNano('R'); delay(400);
    sendToNano('S');
  } 
  else if (distR < dangerDistance) {
    digitalWrite(redLED, HIGH);
    digitalWrite(greenLED, LOW);
    sendToNano('S'); delay(100);
    sendToNano('L'); delay(400);
    sendToNano('S');
  } 
  else {
    digitalWrite(redLED, LOW);
    digitalWrite(greenLED, HIGH);
    sendToNano('F');
  }

  delay(100);
}


