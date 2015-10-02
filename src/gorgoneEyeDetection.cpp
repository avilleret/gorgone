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
    Sobel(imgRoi, sobel, -1, 1, 1);
    equalizeHist(sobel, normalized);
    double score = norm(sum(normalized)) / normalized.total(); // compute image quality

    cout << "score is : " << score << endl;
    if ( score > bestScore ){
      bestScore = score;

cout << "toOf()... " << endl;
      toOf(img, origin);
cout << "done." << endl;

      leftEye.cropFrom(origin,rect.x,rect.y,rect.width/3,rect.height);
      rightEye.cropFrom(origin,rect.x+2*rect.width/3,rect.y,rect.width/3,rect.height);
    }
  }
}

void gorgoneEyeDetection::reset(){
  bestScore = 0.;
}
