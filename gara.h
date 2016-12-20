#ifndef gara_h
#define gara_h
 
#if ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
  #include "pins_arduino.h"
  #include "WConstants.h"
#endif

class gara {
  public:
    gara();
    int strToint(char *s);
    void ptoSetup(int dir, int en, int cp);
    void impGen(int n, boolean dir, int d);
    void encSetup1(int pin_a, int pin_b);
    void encSetup2(int pin_a, int pin_b);
    int encRead(int b);
    boolean done = false;
};

#endif
