#pragma once

#include "ofMain.h"
#include "ofxCv.h"

class gorgoneEyeDetection : public ofxCv::ObjectFinder {
public:
  gorgoneEyeDetection();
  template <class T>
  void computeScore(T& img) {
    computeScore(ofxCv::toCv(img));
  }
  void computeScore(cv::Mat img);
  void reset();
  ofImage leftEye, rightEye; // save the best left and right eyes

private:
  double bestScore;

};