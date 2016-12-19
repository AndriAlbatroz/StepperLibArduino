#include "gara.h"

#define a 2
#define b 3

gara u = gara();

void setup() {
  Serial.begin(9600);
  u.encSetup1(a,b);
  attachInterrupt(0,updateEnc,CHANGE);
  attachInterrupt(1,updateEnc,CHANGE);
}

void loop() {

}

void updateEnc() {
    int value = u.encRead(digitalRead(a), digitalRead(b));
}
