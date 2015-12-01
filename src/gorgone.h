#pragma once

#include "ofxJamoma.h"

#include "ofMain.h"
#include "ofxArgParser.h"

#include "ofxCv.h"
#include "gorgoneEyeDetection.h"
#include "gorgoneMotionDetector.h"
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
    void exit   ();

    void keyPressed      (int key);

    void messageReceived (ofMessage&);
    ofxJamoma jamoma;
    bool bTracking, bDisplaying, bComputeCode, bMotion;
    svgInterpolation svgInterp;
    crossVideoGrabber vidGrabber;
    void setPwm(float pc);

private:
    void detectEyeRegion(ofImage& input);
    void selectBestEye(IplImage* currentImg, int index, int &bestIndex, IplImage* bestImg, double& bestScore);
    void parseCmdLineOptions();

    string filename, appName, masterIp;

    int camWidth, camHeight;

    ofTexture videoTexture;

    cv::Mat frame;

    ofImage m_colorImg, m_grayImg, m_leftEye, m_rightEye;

    gorgoneEyeDetection irisDetector;
    gorgoneMotionDetector motionDetector;
    int counter;
};
