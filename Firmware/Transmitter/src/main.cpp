// THIS IS THE TRANSMITTER

#include <Arduino.h>

void setup() {
  pinMode(1, INPUT);
  Serial.begin(115200);
  delay(2000);
  Serial.println("dddd");
  Serial0.begin(9600, SERIAL_8N1, 6, 7);
  Serial1.begin(115200, SERIAL_8N1, 4, 5);
}

// byte data[] = {0x00, 0x29, 0x41, 0x43, 0x43, 0x43};
// Serial1.write(data, sizeof(data));

unsigned long lastTransmitted = millis();

void loop() {
  // Serial0.println("HI!!!!!");
  // delay(3000);
  if(Serial1.available() > 0) {
    String val;
    for(char c: Serial1.readStringUntil('e')) { // get the range
      if(c != '\n') {
        Serial.print(c);
        val += c;
      } else {
        break;
      }
    }

    Serial.println(val);

    if(millis() - lastTransmitted >= 2800 && val.toInt() < 167) {
      Serial0.println(val);
      // Serial0.println(digitalRead(1));
      lastTransmitted = millis();
    }
  }
}