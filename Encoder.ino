#include "Encoder.h"

int gOldValueEncoder;
int gCounter = 0;
bool usingEncoders = false;
int gShutdownCounter = 0;
bool gShutdownState = false;

void setupEncoders() {
    pinMode(ENCODER_B, INPUT_PULLUP);
    pinMode(ENCODER_A, INPUT_PULLUP);

    gOldValueEncoder = digitalRead(ENCODER_A);
}

//Read the B encoder to increase or decrease the value of the counter
void incrementEncoders() {
    if (digitalRead(ENCODER_B) == HIGH) {
        if (gCounter != 0) {
          gCounter--;
        }
    }
  
    else if (digitalRead(ENCODER_B) == LOW) {
        if (gCounter != 63) {
          gCounter++;
        }
    }
}

int getEncoders() {
    int currentValueEncoder = 0;

    currentValueEncoder = digitalRead(ENCODER_A);

    // Transition state of encoder A to read the rotation direction
    if (gOldValueEncoder == LOW && currentValueEncoder == HIGH) { 
      incrementEncoders();
      usingEncoders = true;
    }

    return gCounter;
}