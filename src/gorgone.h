#pragma once

#include "ofMain.h"

#include "ofxCv.h"
#include "gorgoneEyeDetection.h"
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

    void keyPressed      (ofKeyEventArgs&);
    void keyReleased     (ofKeyEventArgs&);

    void messageReceived (ofMessage&);

    void detectEyeRegion(ofImage& input);
    void selectBestEye(IplImage* currentImg, int index, int &bestIndex, IplImage* bestImg, double& bestScore);
    void drawEye();

    int camWidth, camHeight;

    EyeDetection* eyeDetection;

    crossVideoGrabber vidGrabber;
    ofTexture videoTexture;

    ofImage         m_colorImg, m_grayImg, m_leftEye, m_rightEye;

    gorgoneEyeDetection eyeFinder;
};
