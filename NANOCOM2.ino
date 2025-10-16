// Arduino Nano 33 BLE Sense code
void setup() {
  Serial.begin(115200);  // For USB serial monitor
  Serial1.begin(9600);   // Hardware serial pins 0 (RX) and 1 (TX)
  Serial.println("Nano BLE 33 ready to communicate with ESP32");
}

void loop() {
  // Send a message to ESP32
  Serial1.println("Hello from Nano BLE 33!");
  delay(2000);

  // Read if ESP32 sent something
  if (Serial1.available()) {
    String data = Serial1.readStringUntil('\n');
    Serial.print("Received from ESP32: ");
    Serial.println(data);
  }
}
