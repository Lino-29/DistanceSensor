#include <Arduino.h>
#include "Adafruit_VL53L0X.h"

Adafruit_VL53L0X lox = Adafruit_VL53L0X();

uint8_t ledPin = LED_BUILTIN;
uint8_t RED = PIND4;
uint8_t GREEN = PIND5;
uint8_t BLUE = PIND6;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  Serial.begin(115200);

  while (! Serial) {
    delay(1);
  }

  Serial.println("Adafruit VL53L0X test.");
  if (!lox.begin()) {
    Serial.println(F("Failed to boot VL53L0X"));
    while(1);
  }

  Serial.println(F("VL53L0X API Continuous Ranging example\n\n"));

  lox.startRangeContinuous();
}

void loop() {
  digitalWrite(RED, LOW);
  digitalWrite(GREEN, LOW);
  digitalWrite(BLUE, HIGH);

  digitalWrite(ledPin, HIGH);
  _delay_ms(100);
  digitalWrite(ledPin, LOW);
  _delay_ms(100);

  if (lox.isRangeComplete()) {
    Serial.print("Distancia en mm: ");
    Serial.println(lox.readRange());
  }
}
