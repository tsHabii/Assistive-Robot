// ===== NANO 33 BLE CODE =====

// Motor pins
int enA = 9;
int in1 = 3;
int in2 = 6;
int enB = 10;
int in3 = 5;
int in4 = 4;

void setup(){
  // Motor setup
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  // USB serial for debugging
  Serial.begin(115200);
  while (!Serial);

  // UART serial for ESP32 communication
  Serial1.begin(115200);   // TX1=Pin D1, RX1=Pin D0 on Nano BLE 33

  Serial.println("✅ Nano 33 BLE ready and waiting for commands...");
}

void moveForward(int s) { digitalWrite(in1, HIGH); digitalWrite(in2, LOW); digitalWrite(in3, HIGH); digitalWrite(in4, LOW); analogWrite(enA, s); analogWrite(enB, s); }
void moveBackward(int s){ digitalWrite(in1, LOW); digitalWrite(in2, HIGH); digitalWrite(in3, LOW); digitalWrite(in4, HIGH); analogWrite(enA, s); analogWrite(enB, s); }
void turnLeft(int s)    { digitalWrite(in1, LOW); digitalWrite(in2, HIGH); digitalWrite(in3, HIGH); digitalWrite(in4, LOW); analogWrite(enA, s); analogWrite(enB, s); }
void turnRight(int s)   { digitalWrite(in1, HIGH); digitalWrite(in2, LOW); digitalWrite(in3, LOW); digitalWrite(in4, HIGH); analogWrite(enA, s); analogWrite(enB, s); }
void stopMotors()       { digitalWrite(in1, LOW); digitalWrite(in2, LOW); digitalWrite(in3, LOW); digitalWrite(in4, LOW); analogWrite(enA, 0); analogWrite(enB, 0);
 }

void loop(){
  if (Serial1.available()) {
    char cmd = Serial1.read();

    switch (cmd) {
      case 'F': moveForward(130); break;
      case 'B': moveBackward(130); break;
      case 'L': turnLeft(130); break;
      case 'R': turnRight(130); break;
      case 'S': stopMotors(); break;
      default: break;
    }

    // Debug print on USB serial
    Serial.print("Received cmd: ");
    Serial.println(cmd);

    // Send ACK back to ESP32
    Serial1.println("ACK");
  }
}
