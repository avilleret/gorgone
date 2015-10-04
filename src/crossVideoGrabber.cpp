#include "crossVideoGrabber.h"

#ifdef TARGET_RASPBERRY_PI
void crossVideoGrabber::setup(){
  cam.setup(1920,1080,false);
}

void crossVideoGrabber::update(){
  newFrame = cam.isFrameNew();
  frame = cam.grab();
}

void crossVideoGrabber::draw(int x, int y){

}

#else
void crossVideoGrabber::setup(){
  initGrabber(640, 480);
}
#endif
