#pragma once

#include "ofMain.h"
#include "ofxCv.h"

#ifdef TARGET_RASPBERRY_PI
#include "ofxCvPiCam.h"
class crossVideoGrabber {
public:
  void setup();
  void update();
  void draw(){draw(0,0);};
  void draw(int x, int y);
  cv::Mat getFrame(){return frame;};
  bool isFrameNew(){return newFrame;};

private:
  ofxCvPiCam cam;
  cv::Mat frame;
  bool newFrame;
};

#else
class crossVideoGrabber : public ofVideoGrabber {
public:
  cv::Mat getFrame(){return ofxCv::toCv(*this);};
  void setup();
};
#endif
