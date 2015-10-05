#include "gorgoneEyeDetection.h"

using namespace cv;
using namespace ofxCv;

gorgoneEyeDetection::gorgoneEyeDetection(){
  reset();
}

void gorgoneEyeDetection::computeScore(Mat img){
  if ( size() == 0 ){
    return;
  }
  for ( int i = 0; i < size() ; i++ ){
    cv::Rect rect = objects[i];
    Mat imgRoi(img, rect); // get the region of interest (ROI), i.e. the eyes, from origin image.
    ofImage origin;

    Mat sobel, normalized;
    equalizeHist(imgRoi, normalized);
    Sobel(normalized, sobel, -1, 1, 1);
    double score = norm(sum(sobel)) / sobel.total(); // compute image quality

    cout << "score is : " << score << endl;
    if ( score > bestScore ){
      bestScore = score;

      toOf(img, origin);

      int eyeWidth = rect.width * 0.4;
      leftEye.cropFrom(origin, rect.x, rect.y, eyeWidth, rect.height);
      rightEye.cropFrom(origin, rect.x + rect.width - eyeWidth, rect.y, eyeWidth, rect.height);
    }
    bothEyes.cropFrom(origin,rect.x,rect.y,rect.width,rect.height);
  }
}

void gorgoneEyeDetection::reset(){
  bestScore = 0.;
}

void gorgoneEyeDetection::drawEyes(){
  if (leftEye.isAllocated())  leftEye.draw(0,0);
  if (rightEye.isAllocated()) rightEye.draw(ofGetWidth()-rightEye.getWidth(),0);
  if (bothEyes.isAllocated()) bothEyes.draw(0,ofGetHeight()-bothEyes.getHeight());
}

void gorgoneEyeDetection::save(){
  string basename = ZeroPadNumber(ofGetYear()) + ZeroPadNumber(ofGetMonth()) + ZeroPadNumber(ofGetDay());
  basename += "-" + ZeroPadNumber(ofGetHours()) + ZeroPadNumber(ofGetMinutes()) + ZeroPadNumber(ofGetSeconds());

  cout << "save eyes to " << basename << endl;
  if (leftEye.isAllocated()) leftEye.save(basename + "-left.bmp" );
  if (rightEye.isAllocated()) leftEye.save(basename + "-right.bmp");
  if (bothEyes.isAllocated()) bothEyes.save(basename + ".bmp");
}
