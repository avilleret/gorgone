#include "gnublin.h"

class brightPi{
  gnublin_i2c i2c;

public:
  brightPi(){
    i2c.setAddress(0x70);
  };

  void switchOnIR(){
    printf("switchOnIR\n");
    i2c.send(0x00, (unsigned char) 0xa5); // turn on all IR LED
    i2c.send(0x09, (unsigned char) 0x0f); // push global brightness to full
    i2c.send(0x01, (unsigned char) 0x32); // then turn brightness of each IR LED to full
    i2c.send(0x03, (unsigned char) 0x32);
    i2c.send(0x06, (unsigned char) 0x32);
    i2c.send(0x08, (unsigned char) 0x32);
  };

  void switchOffIR(){
    i2c.send(0x00,0x00);
  };

  void switchOnWhite(){
    printf("switchOnWhite\n");
    i2c.send(0x00, (unsigned char) 0x5a);
  }
};
