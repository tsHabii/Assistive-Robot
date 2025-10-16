// ===== ESP32 Code (for ESP32-WROOM-32) =====
#include "BluetoothSerial.h"
BluetoothSerial SerialBT;

// Ultrasonic sensors
int trigPin1 = 23, echoPin1 = 22;
int trigPin2 = 21, echoPin2 = 19;
int redLED = 25, yellowLED = 26, greenLED = 27;
const int dangerDistance = 20;

// Communication timeout
const int ACK_TIMEOUT = 400;

void setup() {
  pinMode(trigPin1, OUTPUT); pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT); pinMode(echoPin2, INPUT);
  pinMode(redLED, OUTPUT); pinMode(yellowLED, OUTPUT); pinMode(greenLED, OUTPUT);

  Serial.begin(115200);                                // Debug to PC
  Serial2.begin(115200, SERIAL_8N1, 16, 17);           // RX2=16, TX2=17
  SerialBT.begin("Mo_Robot");                        // Bluetooth name
  delay(1000);

  Serial.println("✅ ESP32-WROOM-32 ready. Waiting for Nano...");
  SerialBT.println("✅ ESP32-WROOM-32 ready. Waiting for Nano...");
}

// Distance function
long readUltrasonic(int trig, int echo) {
  digitalWrite(trig, LOW); delayMicroseconds(2);
  digitalWrite(trig, HIGH); delayMicroseconds(10);
  digitalWrite(trig, LOW);
  long duration = pulseIn(echo, HIGH, 30000);
  if (duration == 0) return -1;
  return duration * 0.034 / 2;
}

// Send command to Nano and wait for ACK
void sendToNano(char cmd) {
  Serial.print("➡️ Sending to Nano: ");
  Serial.println(cmd);

  Serial2.write(cmd);
  Serial2.println();     // Ensure newline terminator
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
  long distL = readUltrasonic(trigPin1, echoPin1);
  long distR = readUltrasonic(trigPin2, echoPin2);

  if (distL < 0 || distR < 0) {
    digitalWrite(redLED, LOW);
    digitalWrite(greenLED, LOW);
    digitalWrite(yellowLED, HIGH);
    sendToNano('S');
    delay(200);
    return;
  }

  if (distL < dangerDistance || distR < dangerDistance) {
    digitalWrite(redLED, HIGH);
    digitalWrite(greenLED, LOW);
    digitalWrite(yellowLED, LOW);
  } else {
    digitalWrite(redLED, LOW);
    digitalWrite(greenLED, HIGH);
    digitalWrite(yellowLED, LOW);
  }

  if (distL < dangerDistance && distR < dangerDistance) {
    sendToNano('S'); delay(100);
    sendToNano('B'); delay(400);
    sendToNano('R'); delay(400);
    sendToNano('S');
  } 
  else if (distL < dangerDistance) {
    sendToNano('S'); delay(100);
    sendToNano('R'); delay(400);
    sendToNano('S');
  } 
  else if (distR < dangerDistance) {
    sendToNano('S'); delay(100);
    sendToNano('L'); delay(400);
    sendToNano('S');
  } 
  else {
    sendToNano('F');
  }

  delay(100);
}

