#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "ofxGui.h"

using namespace cv;
using namespace ofxCv;

class gorgoneMotionDetector {
public:
  ofxCv::FlowFarneback flow;
  ofxJamoma* jamoma;

  void setup(ofxJamoma * j){ jamoma = j;};
  void update(Mat& img){
    if ( img.total() > 0 ){
      Mat small;
      cv::resize(img,small,cv::Size(320,240));
      flow.calcOpticalFlow(small);
      ofVec2f f = flow.getAverageFlow();
      jamoma->mTrackingFlowReturn.set("value", f.length());
    }
  };
};
