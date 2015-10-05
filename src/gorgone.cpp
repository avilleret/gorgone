#include "gorgone.h"

int accum = 0;

void gorgone::setup()
{

  cout << "screen resolution : " << ofGetWidth() << "x" << ofGetHeight() << endl;
  string cascadeFilePath = ofFilePath::getAbsolutePath("cascade/parojosG_45x11.xml");
  try {
    eyeDetection = new EyeDetection(cascadeFilePath.c_str());
  } catch (const char* msg) {
    cout << "Error: Failed to load the cascade " << msg << endl;
  }

  eyeFinder.setup("cascade/parojosG_45x11.xml");
#ifdef TARGET_RASPBERRY_PI
  eyeFinder.setRescale(0.1);
#endif
  // eyeFinder.setPreset(ofxCv::ObjectFinder::Accurate);

  vidGrabber.setup();
  ofSetVerticalSync(true);
}

void gorgone::update()
{
  vidGrabber.update();
  if(vidGrabber.isFrameNew()){
    cv::Mat frame = vidGrabber.getFrame();

    cout << "new frame to process : " << frame.cols << "x" << frame.rows << endl;

    eyeFinder.update(frame);

    accum += eyeFinder.size();
    cout << "find " << accum << " eyes" << endl << endl << endl;

    if ( eyeFinder.size() > 0 ) {
      eyeFinder.computeScore(frame);
    }

  } else {
    cout << "no new frame to process" << endl;
  }
}

void gorgone::draw()
{
  cout << ofGetFrameRate() << " fps" << endl;
  // vidGrabber.draw(0,0);
  // eyeFinder.draw();
  eyeFinder.drawEyes();
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
