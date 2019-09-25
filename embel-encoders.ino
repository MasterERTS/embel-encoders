#include "Encoder.h"

void setup() {
  setupEncoders();
  setupPWM();
  setupLCD();
}

void loop() {
  int embelEncoders = getEncoders();
}

