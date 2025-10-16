// ESP32 code
#define RXp2 16
#define TXp2 17

void setup() {
  Serial.begin(115200);      // For monitor
  Serial2.begin(9600, SERIAL_8N1, RXp2, TXp2); // For communication
  Serial.println("ESP32 ready to communicate with Nano BLE 33");
}

void loop() {
  // Send a message to Nano
  Serial2.println("Hello from ESP32!");
  delay(2000);

  // Read if Nano sent something
  if (Serial2.available()) {
    String data = Serial2.readStringUntil('\n');
    Serial.print("Received from Nano: ");
    Serial.println(data);
  }
}

