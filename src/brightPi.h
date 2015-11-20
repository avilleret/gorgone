#include "gnublin.h"

class brightPi{
  gnublin_i2c i2c;

public:
  brightPi(){
    i2c.setAddress(0x70);
    wled.push_back(0b00000010);
    wled.push_back(0b00001000);
    wled.push_back(0b00010000);
    wled.push_back(0b01000000);
  };

  vector<unsigned char> wled;

  void switchOnIR(){
    unsigned char status;
    i2c.receive(0x00, &status, 1);
    status |= 0xa5;
    i2c.send(0x00, (unsigned char) status); // turn on all IR LED
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

  void setBrightness(uint brightness){
    uint global = (brightness >> 6) & 0x0F;
    uint individual = brightness & 0x3F;
    cout << "Brightness global : " << std::hex << global << ", individual : " << std::hex << individual << endl;
    i2c.send(0x09, (unsigned char) global); // push global brightness to full
    i2c.send(0x01, (unsigned char) individual); // then turn brightness of each IR LED to full
    i2c.send(0x03, (unsigned char) individual);
    i2c.send(0x06, (unsigned char) individual);
    i2c.send(0x08, (unsigned char) individual);
  }

  void setWBrightness(vector<unsigned char> b){
    cout << "setWBrightness received " << b.size() << " values" << endl;
    unsigned char status;
    i2c.receive(0x00, &status, 1);
    for ( int i=0; i<min(b.size(),wled.size()); i++ ){
      if (b[i] > 0) status |= wled[i];
      else status &= ~wled[i];
      cout << "set led " << i << " at address " << std::hex << static_cast<unsigned>(wled[i]) << " to " << static_cast<unsigned>(b[i]) << endl;
      i2c.send(wled[i], (unsigned char) b[i]);
    }
    i2c.send(0x00, status);
  }
};
