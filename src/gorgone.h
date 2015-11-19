#pragma once

#include "ofxJamoma.h"

#include "ofMain.h"
#include "ofxArgParser.h"

#include "ofxCv.h"
#include "gorgoneEyeDetection.h"
#include "svgInterpolation.h"
#include "crossVideoGrabber.h"

#include "EyeDetection.h"
#include "ImageUtility.h"
#include "ImageQuality.h"

class gorgone : public ofBaseApp
{
  public:
    void setup  ();
    void update ();
    void draw   ();

    void keyPressed      (int key);

    void messageReceived (ofMessage&);
    ofxJamoma jamoma;
    bool bTracking, bDisplaying, bComputeCode;
    svgInterpolation svgInterp;
    crossVideoGrabber vidGrabber;

private:
    void detectEyeRegion(ofImage& input);
    void selectBestEye(IplImage* currentImg, int index, int &bestIndex, IplImage* bestImg, double& bestScore);
    void parseCmdLineOptions();

    string filename, appName;

    int camWidth, camHeight;

    ofTexture videoTexture;

    cv::Mat frame;

    ofImage m_colorImg, m_grayImg, m_leftEye, m_rightEye;

    gorgoneEyeDetection irisDetector;
};
