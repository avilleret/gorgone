#include "gnublin.h"

class brightPi{
  gnublin_i2c i2c;

public:
  brightPi(){
    i2c.setAddress(0x70);
  };

  void switchOnIR(){
    unsigned char status;
    i2c.receive(0x00, &status, 1);
    status |= 0xa5;
    i2c.send(0x00, (unsigned char) status); // turn on all IR LED
    i2c.send(0x09, (unsigned char) 0x0f); // push global brightness to full
    i2c.send(0x01, (unsigned char) 0x32); // then turn brightness of each IR LED to full
    i2c.send(0x03, (unsigned char) 0x32);
    i2c.send(0x06, (unsigned char) 0x32);
    i2c.send(0x08, (unsigned char) 0x32);
  };

  void switchOffIR(){
    unsigned char status;
    i2c.receive(0x00, &status, 1);
    status &= 0x5a;
    i2c.send(0x00, status);
  };

  void switchOnWhite(){
    unsigned char status;
    i2c.receive(0x00, &status, 1);
    status |= 0x5a;
    i2c.send(0x00, status);
  }

  void switchOffWhite(){
    unsigned char status;
    i2c.receive(0x00, &status, 1);
    status &= 0xa5;
    i2c.send(0x00, status);
  }
};
