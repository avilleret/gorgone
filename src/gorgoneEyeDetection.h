#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "ofxGui.h"

class gorgoneEyeDetection : public ofxCv::ObjectFinder {
public:
  gorgoneEyeDetection();
  template <class T>
  void computeScore(T& img) {
    computeScore(ofxCv::toCv(img));
  }
  void computeScore(cv::Mat img);
  void reset();
  void drawEyes();
  void save();

  ofImage leftEye, rightEye, bothEyes; // save the best left and right eyes
  ofxPanel gui;
  ofParameter<int> x, y, z;

private:
  double bestScore;

  static std::string ZeroPadNumber(int num)
  {
      std::ostringstream ss;
      ss << std::setw( 2 ) << std::setfill( '0' ) << num;
      return ss.str();
  }

};
