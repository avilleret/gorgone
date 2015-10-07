#include "crossVideoGrabber.h"

void crossVideoGrabber::setup(string filename){

  videoFlag = videoPlayer.load("movies/"+filename);
  if (videoFlag) {
    videoPlayer.setLoopState(OF_LOOP_NORMAL);
    videoPlayer.play();
  } else {
#ifdef TARGET_RASPBERRY_PI
    cam.setup(1920,1080,false);
#else
    cam.initGrabber(640, 480);
#endif
  }
}

void crossVideoGrabber::update(){
  if ( videoFlag ) {
    videoPlayer.update();
  } else {
#ifdef TARGET_RASPBERRY_PI
    newFrame = cam.isFrameNew();
    frame = cam.grab();
#else
    cam.update();
#endif
  }
}
void crossVideoGrabber::draw(int x, int y){
  if ( videoFlag ){
    videoPlayer.draw(x,y);
  } else {
#ifndef TARGET_RASPBERRY_PI
    cam.draw(x,y);
#endif
  }
}
