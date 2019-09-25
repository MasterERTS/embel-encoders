#include "Encoder.h"

int gOldValueEncoder;
int gCounter = 0;
bool usingEncoders = false;
int gShutdownCounter = 0;
bool gShutdownState = false;

LiquidCrystal lcd (18, 17, 16, 15, 14, 19);

void setupPWM() {
  analogWriteFrequency(PWM, PWM_FREQ);
  analogWriteResolution(6);
  analogWrite(PWM, gCounter);
}

void setupLCD() {
  lcd.begin(20, 4);
  lcd.setCursor(0, 1);
  lcd.print(gCounter);
}

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

void refreshLCD() {
  // Refresh screen every 100ms and enter Shutdown procedure after 
  if (millis() - gTimeStamp > 100) {
    gShutdownCounter++;

    // After 5 seconds, enter shutdown procedure
    if (gShutdownCounter > 50) {
      if (gCounter != 0) {
        // Decrease counter while it's different than 0
        gShutdownState = true;
        gCounter--;
      } else {
        // Go back to normal state if we reach 0
        gCounter = 0;
        gShutdownState = false;
      }
      analogWrite(PWM, gCounter);     
    }

    // Print two spaces and overwrite it with the counter value
    lcd.setCursor(0, 1);
    lcd.print("  ");
    lcd.setCursor(0, 1);
    lcd.print(gCounter);
    gTimeStamp = millis();
  }
}

int getEncoders() {
    // put your main code here, to run repeatedly:
  int currentValueEncoder = 0;

  // We can't affect the digital encoder while in shutdown procedure
  if (gShutdownState == false) {
    currentValueEncoder = digitalRead(ENCODER_A);

    // Transition state of encoder A to read the rotation direction
    if (gOldValueEncoder == LOW && currentValueEncoder == HIGH) { 
      gShutdownCounter = 0; // Reset shutdown counter if encoder is used
      incrementEncoders();
      analogWrite(PWM, gCounter);
    }
  }

  refreshLCD();

  gOldValueEncoder = currentValueEncoder;
  return(gCounter);
}
