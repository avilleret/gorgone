#include "gorgone.h"

int accum = 0;

void gorgone::setup()
{

  parseCmdLineOptions();

  cout << "screen resolution : " << ofGetWidth() << "x" << ofGetHeight() << endl;
  string cascadeFilePath = ofFilePath::getAbsolutePath("cascade/parojosG_45x11.xml");
  try {
    eyeDetection = new EyeDetection(cascadeFilePath.c_str());
  } catch (const char* msg) {
    cout << "Error: Failed to load the cascade " << msg << endl;
  }

  vidGrabber.setup(filename);

  eyeFinder.setup("cascade/parojosG_45x11.xml");
#ifdef TARGET_RASPBERRY_PI
  eyeFinder.setRescale(0.1);
#endif
  // eyeFinder.setPreset(ofxCv::ObjectFinder::Accurate);
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

    eyeFinder.computeScore(frame);
  }
}

void gorgone::draw()
{
  // cout << ofGetFrameRate() << " fps" << endl;
  //vidGrabber.draw(0,0);
  //eyeFinder.draw();
  eyeFinder.drawEyes();
}

void gorgone::keyPressed(int key)
{
  switch (key){
    case 's':
      eyeFinder.save();
      break;
    default :
      break;
  }
}

void gorgone::messageReceived(ofMessage& message)
{
}


void gorgone::parseCmdLineOptions(){
  vector<string> keys = ofxArgParser::allKeys();
  for (int i = 0; i < keys.size(); i++) {
         if ( keys[i] == "f" )   { filename     = ofxArgParser::getValue(keys[i]); }

    cout << "key: " << keys[i] << ", value: " << ofxArgParser::getValue(keys[i]) << endl;
  }
}
