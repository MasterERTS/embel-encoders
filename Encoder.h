#ifndef ENCODER_H
#define ENCODER_H

#include <LiquidCrystal.h>


#define ENCODER_A    0
#define ENCODER_B    1
#define PWM          23

#define PWM_FREQ     25000

// ENCA transitionning from LOW TO HIGH : change in the direction
// ENCB value is low => CLOCKWISE
// ENCB value is high => gCounter CLOCKWISE 

void setupPWM();
void setupLCD();
void setupEncoders();
void refreshLCD();
int getEncoders();
void incrementEncoders();



#endif /* ENCODER_H */
