// THIS IS THE TRANSMITTER

#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "ligma";
const char* password = "";

void setup() {
  pinMode(1, INPUT);
  Serial.begin(115200);
  delay(2000);

  Serial0.begin(9600, SERIAL_8N1, 6, 7); // lora
  Serial1.begin(115200, SERIAL_8N1, 4, 5); // radar

  WiFi.begin(ssid, password);

  while(WiFi.status() != WL_CONNECTED) {
    delay(67);
    Serial.println("connecting");
  }
}

unsigned long lastTransmitted = millis();


void loop() {
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
      HTTPClient http;
      http.begin("discord webhook url");
      http.addHeader("Content-Type", "application/json");
      String reqData = "{\"content\":\"someone is nearby\"}";
      int httpResponseCode = http.POST(reqData);
      Serial0.println(val);
      
      lastTransmitted = millis();
    }
  }
}