#include "gorgone.h"

void gorgone::setup()
{
  string cascadeFilePath = ofFilePath::getAbsolutePath("cascade/parojosG_45x11.xml");
  try {
    eyeDetection = new EyeDetection(cascadeFilePath.c_str());
  } catch (const char* msg) {
    cout << "Error: Failed to load the cascade " << msg << endl;
  }

  eyeFinder.setup("cascade/parojosG_45x11.xml");
  // eyeFinder.setPreset(ofxCv::ObjectFinder::Accurate);

  vidGrabber.setup();
  ofSetVerticalSync(true);
}

void gorgone::update()
{
  vidGrabber.update();
  if(vidGrabber.isFrameNew()){
    cv::Mat origin = vidGrabber.getFrame();
    cv::Mat frame;

    cout << "new frame to process : " << origin.cols << "x" << origin.rows << endl;

    if ( origin.cols > 640 || origin.rows > 480 ){
      cv::resize(origin,frame,cv::Size(0,0),640./float(origin.cols),640./float(origin.cols));
    } else {
      frame = origin;
    }

    cout << "process frame : " << frame.cols << "x" << frame.rows << endl;

    eyeFinder.update(frame);
/*
    if ( eyeFinder.size() > 0 ) {
      eyeFinder.computeScore(frame);
    }
*/
  } else {
    cout << "no new frame to process" << endl;
  }
}

void gorgone::draw()
{
  cout << ofGetFrameRate() << " fps" << endl;
  vidGrabber.draw(0,0);
  eyeFinder.draw();
  if (eyeFinder.leftEye.isAllocated())  eyeFinder.leftEye.draw(0,0);
  if (eyeFinder.rightEye.isAllocated()) eyeFinder.rightEye.draw(0,50);
}

void gorgone::keyPressed(ofKeyEventArgs& key)
{
}

void gorgone::keyReleased(ofKeyEventArgs& key)
{
}

void gorgone::messageReceived(ofMessage& message)
{
}
