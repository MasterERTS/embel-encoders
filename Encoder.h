#ifndef ENCODER_H
#define ENCODER_H

#define ENCODER_A    0
#define ENCODER_B    1

// ENCA transitionning from LOW TO HIGH : change in the direction
// ENCB value is low => CLOCKWISE
// ENCB value is high => gCounter CLOCKWISE 

void setupEncoders();
int getEncoders();
void incrementEncoders();



#endif /* ENCODER_H */