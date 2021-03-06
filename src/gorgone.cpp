#include "gorgone.h"
using namespace cv;
using namespace ofxCv;
int accum = 0;

void gorgone::setup()
{
  ofSetLogLevel(OF_LOG_NOTICE);
  masterIp = "gorgone-master.local";
  appName = "gorgone-1";
  parseCmdLineOptions();
  vidGrabber.setup(filename);
  svgInterp.setup();
  jamoma.setup((void*) this, appName, masterIp);
  motionDetector.setup(&jamoma);
  irisDetector.setJamomaRef(&jamoma);
  counter = 0;
  if ( !csv.load("images/values.txt")){
      ofxCsvRow row;
      row.setString(0,"date");
      row.setString(1,"hour");
      row.setString(2,"blobarea");
      row.setString(3,"coeff1");
      row.setString(4,"coeff2");
      row.setString(5,"coeff3");
      row.setString(6,"coeff4");
      row.setString(7,"coeff5");
      row.setString(8,"coeff6");
      row.setString(9,"coeff7");
      row.setString(10,"coeff8");
      csv.addRow(row);
      csv.save("images/values.txt");
  }
}

void gorgone::exit(){
  setPwm(0);
#ifdef TARGET_RASPBERRY_PI
  vidGrabber.led.switchOffIR();
#endif
}

void gorgone::update()
{
  ofLogVerbose("gorgone") << ofGetFrameRate() << " fps" << endl;

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

      ofLogVerbose("gorgone") << "new frame to process : " << gray.cols << "x" << gray.rows << endl;

      irisDetector.updateBool(gray);
    }
  }

  Mat tmp = irisDetector.getIrisCode();
  if( irisDetector.newCode && tmp.size().area() > 0.) {
    Mat img;
    resize(tmp, img, Size(tmp.cols, tmp.rows/4.));
    bComputeCode=false;
    jamoma.mComputeIrisCodeParameter.set("value", bComputeCode);

    svgInterp.coeff.clear();
    ofLogNotice("gorgone") << "code image resolution : " << img.cols << "x" << img.rows << endl;
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
    ofxCsvRow row;
    stringstream date;
    date << std::setw( 2 ) << std::setfill( '0' );
    date << ofGetYear() << "/" << ofGetMonth() << "/" << ofGetDay();
    stringstream hour;
    hour << std::setw( 2 ) << std::setfill( '0' );
    hour << ofGetHours() << ":" << ofGetMinutes() << ":" << ofGetSeconds();

    row.setString(0,date.str());
    row.setString(1,hour.str());
    row.setFloat(2,irisDetector.blobArea);
    irisDetector.newCode = false;

    TTValue v, w;
    for (int i = 0; i<svgInterp.coeff.size(); i++){
      v.push_back(svgInterp.coeff[i]);
      row.setFloat(i+3,svgInterp.coeff[i]);
    }
    csv.addRow(row);
    csv.save("images/values.txt");
    jamoma.mTrackingIrisCodeReturn.set("value", v);

    w.push_back(irisDetector.blobArea);
    jamoma.mTrackingIrisBlobAreaReturn.set("value",w);
  }

  if ( bComputeCode ) {
    irisDetector.computeIrisCode();
    bComputeCode = false;
  }
}

void gorgone::draw()
{
  //vidGrabber.draw(0,0);
  drawMat(frame,0,0);
  if ( svgInterp.updateBool() ){
    TTValue x,y;
    ofPolyline line = svgInterp.interpolatedLine;
    // ofLogNotice("gorgone") << "update drawing with " << line.size() << "points" << endl;
    for (int i=0; i<line.size(); i++){
      x.push_back(line[i].x);
      y.push_back(line[i].y);
    }

    jamoma.mDrawingShapeXReturn.set("value", x);
    jamoma.mDrawingShapeYReturn.set("value", y);
  }
  if ( bTracking ) {
    ofDrawBitmapStringHighlight("eye tracking", 10, 400);
    irisDetector.drawEyes();
  }
  if ( bDisplaying ) {
    ofDrawBitmapStringHighlight("laser drawing", 200, 400);
    svgInterp.draw();
  }
  if ( bMotion ){
    ofDrawBitmapStringHighlight("motion detection", 400, 400);
  }
}

void gorgone::keyPressed(int key)
{
  ofLogVerbose("gorgone") << "keypressed : " << key << endl;
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
    case 'm':
      bMotion = !bMotion;
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
    case 357 : // arrow up
      svgInterp.selectedId = counter++;
      break;
    case 359: // arrow down
      svgInterp.selectedId = counter--;
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
    if ( keys[i] == "f" )   filename   = ofxArgParser::getValue(keys[i]);
    else if ( keys[i] == "name" ) appName =  ofxArgParser::getValue(keys[i]);
    else if ( keys[i] == "masterIp" ) masterIp =  ofxArgParser::getValue(keys[i]);
    else if ( keys[i] == "verbose" ) { // vebose level, value : 0..5, default 1 (OF_LOG_NOTICE)
      int logLevel;
      istringstream( ofxArgParser::getValue(keys[i]) ) >> logLevel;
      ofSetLogLevel((ofLogLevel) logLevel);
    }

    ofLogNotice("gorgone") << "key: " << keys[i] << ", value: " << ofxArgParser::getValue(keys[i]) << endl;
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
