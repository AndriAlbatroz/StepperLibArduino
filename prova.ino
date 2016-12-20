#include "gara.h"
#include <string.h>

#define a 2
#define b 3

int asci, i = 0;
char s[10];

gara u = gara();

void setup() {
  Serial.begin(9600);
  u.encSetup1(a,b);
  //attachInterrupt(0,updateEnc,CHANGE);
  //attachInterrupt(1,updateEnc,CHANGE);
}

void loop() {
   do {
     if (Serial.available() > 0) {
        asci = Serial.read();
        s[i] = asci;
        i++;
     }
   } while (asci != '!');
   asci = ' ';
   i = 0;
   u.impGen(u.strToint(s),true,500);
}

void updateEnc() {
    int value = u.encRead(digitalRead(a), digitalRead(b));
}
