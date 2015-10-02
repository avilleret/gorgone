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

  setupVideoGrabber();
}

void gorgone::update()
{
  vidGrabber.update();
  if(vidGrabber.isFrameNew()){
    eyeFinder.update(vidGrabber);

    if ( eyeFinder.size() > 0 ) {
      eyeFinder.computeScore(vidGrabber);
    }
  }
}

void gorgone::draw()
{
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

void gorgone::setupVideoGrabber()
{
  camWidth = 640;  // try to grab at this size.
  camHeight = 480;

  //we can now get back a list of devices.
  vector<ofVideoDevice> devices = vidGrabber.listDevices();

  for(int i = 0; i < devices.size(); i++){
      if(devices[i].bAvailable){
          // ofLogNotice() << devices[i].id << ": " << devices[i].deviceName;
      } else {
          // ofLogNotice() << devices[i].id << ": " << devices[i].deviceName << " - unavailable ";
      }
  }

  vidGrabber.setDeviceID(0);
  vidGrabber.setDesiredFrameRate(60);
  vidGrabber.initGrabber(camWidth, camHeight);

  ofSetVerticalSync(true);
}
