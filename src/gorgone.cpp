#include "gorgone.h"
using namespace cv;
using namespace ofxCv;
int accum = 0;

void gorgone::setup()
{
  masterIp = "Mac-Pro-de-10-52.local";
  appName = "gorgone-1";
  parseCmdLineOptions();
  vidGrabber.setup(filename);
  svgInterp.setup();
  jamoma.setup((void*) this, appName, masterIp);
  motionDetector.setup(&jamoma);
}

void gorgone::exit(){
  setPwm(0);
#ifdef TARGET_RASPBERRY_PI
  vidGrabber.led.switchOffIR();
#endif
}

void gorgone::update()
{
  // cout << ofGetFrameRate() << " fps" << endl;

  vidGrabber.update();

  if ( vidGrabber.isFrameNew() ){
    frame = vidGrabber.getFrame();

    if ( bMotion ){
      motionDetector.update(frame);
    }

    if( bTracking ){

      if ( frame.cols == 0 ) return;

      cv::Mat gray;
      if ( frame.channels() == 1 ){
        gray = frame.clone();
      } else {
        cv::cvtColor(frame, gray, CV_RGB2GRAY);
      }

      cout << "new frame to process : " << gray.cols << "x" << gray.rows << endl;

      irisDetector.update(gray);
    }
  }

  if (bComputeCode) {
    irisDetector.computeCode();
    bComputeCode=false;
    jamoma.mComputeIrisCodeParameter.set("value", bComputeCode);

/*
// desactivated because Max doesn't handle list longer than 256 item, yes this still happens in 2015...
    TTValue v;
    Mat code = irisDetector.getIrisCode();
    v.push_back(code.cols);
    v.push_back(code.rows);
    uchar* p;
    for (int i = 0; i < code.rows; i++ ){
      p=code.ptr<uchar>(i);
      for (int j = 0; j < code.cols; j++ ){
        v.push_back((int) p[j]);
      }
    }
    cout << "v size : " << v.size() << endl;
    jamoma.mTrackingIrisCodeReturn.set("value",v);
*/
  }

  Mat img = irisDetector.getIrisCode();
  if( bDisplaying && irisDetector.newCode && img.total() > 0 ) {

    if ( irisDetector.newCode ){
      svgInterp.coeff.clear();
      cout << "code image resolution : " << img.cols << "x" << img.rows << endl;
      uchar* p;
      for (int i = 0; i < img.rows; i++ ){
        float avg=0;
        p=img.ptr<uchar>(i);
        for (int j = 0; j < img.cols; j++ ){
          avg+=p[j] / 255.;
        }
        avg/=img.cols;
        svgInterp.coeff.push_back(avg);
      }
      irisDetector.newCode = false;
    }

    TTValue v;
    for (int i = 0; i<svgInterp.coeff.size(); i++){
      v.push_back(svgInterp.coeff[i]);
    }
    jamoma.mDrawingCoeffParameter.set("value", v);
    svgInterp.dirtyFlag = true;
  }
}

void gorgone::draw()
{
  // cout << ofGetFrameRate() << " fps" << endl;
  //vidGrabber.draw(0,0);
  drawMat(frame,0,0);
  if ( svgInterp.updateBool() ){
    TTValue x,y;
    vector<ofVec3f> line = svgInterp.interpolatedLine;

    for (int i=0; i<line.size(); i++){
      x.push_back(line[i].x);
      y.push_back(line[i].y);
    }

    jamoma.mDrawingShapeXReturn.set("value", x);
    jamoma.mDrawingShapeYReturn.set("value", y);
  }
  if ( bTracking )
    irisDetector.drawEyes();
  if ( bDisplaying )
    svgInterp.draw();
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
    case 'c':
      bComputeCode=true;
      break;
    case 't':
      bTracking = !bTracking;
      if ( bTracking ) irisDetector.reset();
#ifdef TARGET_RASPBERRY_PI
      if ( bTracking ) vidGrabber.led.switchOnIR();
      else vidGrabber.led.switchOffIR();
#endif
      break;
    case 'd':
      bDisplaying = !bDisplaying;
      break;
#ifdef TARGET_RASPBERRY_PI
    case 'i':
      vidGrabber.led.switchOnIR();
      break;
    case 'o':
      vidGrabber.led.switchOffIR();
      break;
    case 'w':
      vidGrabber.led.switchOnWhite();
      break;
    case 'x':
      vidGrabber.led.switchOffWhite();
      break;
#endif
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
    if ( keys[i] == "f" )   filename   = ofxArgParser::getValue(keys[i]);
    if ( keys[i] == "name" ) appName =  ofxArgParser::getValue(keys[i]);
    if ( keys[i] == "masterIp" ) masterIp =  ofxArgParser::getValue(keys[i]);
    cout << "key: " << keys[i] << ", value: " << ofxArgParser::getValue(keys[i]) << endl;
  }
}


void gorgone::setPwm(float pc){
#ifdef TARGET_RASPBERRY_PI
  ofstream file;
  file.open("/dev/servoblaster", ios::in);
  file << "0=" << pc << "%" << endl;
  file.close();
#endif
}
