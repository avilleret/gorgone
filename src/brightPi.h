#include "gnublin.h"

class brightPi{
  gnublin_i2c i2c;

  brightPi(){
    i2c.setAddress(0x70);
  };

  void switchOnIR(){
    i2c.send(0x00, 0xa5); // turn on all IR LED
    i2c.send(0x09, 0x0f); // push global brightness to full
    i2c.send(0x01, 0x32); // then turn brightness of each IR LED to full
    i2c.send(0x03, 0x32);
    i2c.send(0x06, 0x32);
    i2c.send(0x08, 0x32);
  };

  void switchOffIR(){
    i2c.send(0x00,0x00);
  };
};
