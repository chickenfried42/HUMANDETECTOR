// THIS IS A RECEIVER

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>

HardwareSerial E220(1);
Adafruit_SSD1306 oled(128, 64, &Wire, -1);

void setup() {
  pinMode(5, INPUT_PULLUP);
  Serial.begin(9600);
  delay(1000);
  if(!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    // Serial.println("oled failed");
    for(;;);
  }

  oled.setTextSize(1);
  oled.setTextColor(SSD1306_WHITE);
  oled.setCursor(0,0);
  oled.clearDisplay();
  oled.setRotation(2);
  oled.println("Receiving!!");
  oled.display();

  E220.begin(9600, SERIAL_8N1, 6, 7);
  // Serial.println("reading");
}

unsigned long buttonCooldown = millis();
unsigned long lastReceived = millis();
void loop() {
  // if(digitalRead(5) == LOW && millis() - buttonCooldown > 999) {
  //   oled.clearDisplay();
  //   oled.setCursor(0, 0);
  //   oled.display();
  //   buttonCooldown = millis();
  // }
  // that used to be for a button to clear the display that I've removed
  if(millis() - lastReceived >= 4000) {
    oled.clearDisplay();
    oled.display();
  }

  if(E220.available()) {
    oled.clearDisplay();

    oled.drawCircle(18, 15, 11, 1);
    oled.drawLine(16, 9, 16, 12, 1);
    oled.drawLine(23, 12, 23, 15, 1);
    oled.drawLine(12, 14, 14, 21, 1);
    oled.drawLine(14, 21, 24, 19, 1);
    oled.setTextColor(1);
    oled.setTextWrap(false);
    oled.setCursor(44, 5);
    oled.print("Person");
    oled.setCursor(44, 15);
    oled.print("Detected!!");
    oled.display();

    oled.setCursor(8, 48);
    String val = E220.readStringUntil('\n');
    oled.print("Distance: ");
    oled.print(val);
    oled.display();
    lastReceived = millis();
  }
}