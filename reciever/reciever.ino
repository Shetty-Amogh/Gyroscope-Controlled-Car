String line = "";

void setup() {
  Serial.begin(115200);
  Serial1.begin(9600);
  delay(200);
  Serial.println("UNO R4 tilt receiver started");
}

void loop() {
  
  while (Serial1.available()) {
    char c = Serial1.read();

    Serial.println("works bt");

    if (c == '\n') {
      Serial.print("Received: ");
      Serial.println(line);

      int pIndex = line.indexOf("P:");
      int rIndex = line.indexOf(",R:");

      if (pIndex >= 0 && rIndex >= 0) {
        String pitchStr = line.substring(pIndex + 2, rIndex);
        String rollStr = line.substring(rIndex + 3);

        float pitch = pitchStr.toFloat();
        float roll = rollStr.toFloat();

        Serial.print("Pitch = ");
        Serial.print(pitch);
        Serial.print(" deg, Roll = ");
        Serial.print(roll);
        Serial.println(" deg");
      }

      line = "";
    } else if (c != '\r') {
      line += c;
    }
  }
}