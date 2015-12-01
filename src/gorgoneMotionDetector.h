#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "ofxGui.h"
#include "ofxBiquadFilter.h"

using namespace cv;
using namespace ofxCv;

class gorgoneMotionDetector {
public:
  ofxCv::FlowFarneback flow;
  ofxJamoma* jamoma;
  ofxBiquadFilter1f filter;

  void setup(ofxJamoma * j){
    jamoma = j;
    filter.setFc(0.1);
  };
  void update(Mat& img){
    if ( img.total() > 0 ){
      Mat small;
      cv::resize(img,small,cv::Size(320,240));
      flow.calcOpticalFlow(small);
      ofVec2f f = flow.getTotalFlow();
      filter.update(f.length());
      jamoma->mTrackingFlowReturn.set("value", filter.value());
      ofLogVerbose("gorgoneMotionDetector") << "flow magnitude : " << filter.value() << endl;
    }
  };
};
