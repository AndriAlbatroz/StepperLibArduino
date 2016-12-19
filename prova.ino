#include "gara.h"

#define a 2
#define b 3

gara u = gara();

void setup() {
  Serial.begin(9600);
  u.encSetup1(a,b);
  attachInterrupt(0,u_a,RISING);
  attachInterrupt(0,d_a,FALLING);
  attachInterrupt(1,u_b,RISING);
  attachInterrupt(1,d_b,FALLING);
}

void loop() {
}

void u_a() {
  u.encRead(1,digitalRead(b));
}

void d_a() {
  u.encRead(0,digitalRead(b));
}

void u_b() {
  u.encRead(digitalRead(a),1);
}

void d_b() {
  u.encRead(digitalRead(a),0);
}
