#include "gorgone.h"
using namespace cv;
using namespace ofxCv;
int accum = 0;

void gorgone::setup()
{
  parseCmdLineOptions();
  vidGrabber.setup(filename);
}

void gorgone::update()
{
  vidGrabber.update();

  if(vidGrabber.isFrameNew()){

    frame = vidGrabber.getFrame();

    if ( frame.cols == 0 ) return;

    cv::Mat gray;
    if ( frame.channels() == 1 ){
      gray = frame;
    } else {
      cv::cvtColor(frame, gray, CV_RGB2GRAY);
    }

    cout << "new frame to process : " << gray.cols << "x" << gray.rows << endl;

    irisDetector.update(gray);
   }
 }

void gorgone::draw()
{
  // cout << ofGetFrameRate() << " fps" << endl;
  // vidGrabber.draw(0,0);
  // drawMat(frame,0,0);
  irisDetector.drawEyes();
}

void gorgone::keyPressed(int key)
{
  switch (key){
    case 's':
      irisDetector.save();
      break;
    case ' ':
      irisDetector.reset();
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
