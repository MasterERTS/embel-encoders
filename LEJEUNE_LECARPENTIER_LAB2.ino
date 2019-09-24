#include <LiquidCrystal.h>

#define ENCODER_A    0
#define ENCODER_B    1
#define PWM          23

#define PWM_FREQ     25000

// ENCA transitionning from LOW TO HIGH : change in the direction
// ENCB value is low => CLOCKWISE
// ENCB value is high => gCounter CLOCKWISE 


// Motor doesn't start spinning before reaching minimum voltage from PWM

LiquidCrystal lcd (18, 17, 16, 15, 14, 19);

int gTimeStamp = 0;
int gCounter = 0;
int gOldValueEncoder;
int gShutdownCounter = 0;
bool gShutdownState = false;

void setup() {
  // put your setup code here, to run once:
  pinMode(ENCODER_B, INPUT_PULLUP);
  pinMode(ENCODER_A, INPUT_PULLUP);

  analogWriteFrequency(PWM, PWM_FREQ);
  analogWriteResolution(6);
  analogWrite(PWM, gCounter);
  
  lcd.begin(20, 4);
  //lcd.setCursor(0, 1);
  //lcd.print(gCounter);

  gOldValueEncoder = digitalRead(ENCODER_A);
  
}

//Read the B encoder to increase or decrease the value of the counter
void increment() {
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

void loop() {
  // put your main code here, to run repeatedly:
  int currentValueEncoder = 0;

  // We can't affect the digital encoder while in shutdown procedure
  if (gShutdownState == false) {
    currentValueEncoder = digitalRead(ENCODER_A);

    // Transition state of encoder A to read the rotation direction
    if (gOldValueEncoder == LOW && currentValueEncoder == HIGH) { 
      gShutdownCounter = 0; // Reset shutdown counter if encoder is used
      increment();
      analogWrite(PWM, gCounter);
    }
  }

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

  gOldValueEncoder = currentValueEncoder;
  
}
