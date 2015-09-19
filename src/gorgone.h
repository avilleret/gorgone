#pragma once

#include "ofMain.h"

#include "ofxOpenCv.h"
#include "ofxCv.h"

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

    void keyPressed      (ofKeyEventArgs&);
    void keyReleased     (ofKeyEventArgs&);

    void messageReceived (ofMessage&);

    void setupVideoGrabber();
    void detectEyeRegion(ofxCvGrayscaleImage& input);
    void selectBestEye(IplImage* currentImg, int index, int &bestIndex, IplImage* bestImg, double& bestScore);
    void drawEye();

    int camWidth, camHeight;

    EyeDetection* eyeDetection;

    ofVideoGrabber vidGrabber;
    ofTexture videoTexture;

    ofxCvColorImage         m_colorImg;
    ofxCvGrayscaleImage     m_grayImg, m_leftEye, m_rightEye;

    EyeDetection::RESULT* m_res = NULL;

    ofxCv::ObjectFinder faceFinder, eyeFinder;

};
