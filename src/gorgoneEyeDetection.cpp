#include "gorgoneEyeDetection.h"

// #include "EyeRegionExtraction.h"
#include "FindHighLights.h"
#include "FindEyelidCurve.h"
#include "EncodeLee.h"
#include "ImageUtility.h"
#include "Normalization.h"

using namespace cv;
using namespace ofxCv;

void gorgoneEyeDetection::setup(const Mat& img){
  ofLogNotice("gorgoneEyeDetection") << "---------- SETUP----------" << endl;
  gui.setup("Eye detection", "settings.xml", ofGetWidth() - 200, 10);
  gui.add(param1.set("Hough 1st parameter",104,0,255));
  gui.add(param2.set("Hough 2nd parameter",12,0,255));
  gui.add(paramThresh.set("threshold", 0, 0, 180));
  gui.add(paramMarging.set("marging", 20, 0, 50));
  gui.add(paramScore.set("focus",0,0,1));
  scale=1.;

  eyeFinder.setup("cascade/haarcascade_eye_tree_eyeglasses.xml");
  eyeFinder.setRescale(100./(float)img.rows);
  reset();
  bSetup = true;
}

void gorgoneEyeDetection::reset(){
  bSetup = false;
  flag = false;
  bestScore = 1.; // minimum focus to process frame
  newCode = false;
  if(eye.isAllocated()) eye.clear();
  if(eyeProc.isAllocated()) eyeProc.clear();
  if(irisProc.isAllocated()) irisProc.clear();
  if(bestEyeNorm.isAllocated()) bestEyeNorm.clear();
  if(codeImg.isAllocated()) codeImg.clear();
}

bool gorgoneEyeDetection::updateBool(Mat& img){

  Mat drawing, subMat;
  Mat eyeRoiMat;
  Vec3f iris, pupil;
  Rect eyeRoi;
  double score=0;

  ofLogVerbose("gorgoneEyeDetection") << "---------- UPDATE ----------" << endl;
  if(!bSetup) setup(img);

  eyeFinder.update(img);
  jamoma->mEyeDetectedReturn.set("value", eyeFinder.size());
  ofLogVerbose("gorgoneEyeDetection") << "found eyes : " << eyeFinder.size() << endl;

  if ( eyeFinder.size() == 0) {
    jamoma->mIrisDetectedReturn.set("value", false);
    jamoma->mPupilDetectedReturn.set("value", false);
    return false;
  }

  ofRectangle rect = eyeFinder.getObject(0);
  double marging = paramMarging / 100.;
  rect.x -= rect.width * marging;
  rect.y -= rect.height * marging;
  rect.width *= 1 + 2 * marging;
  rect.height *= 1 + 2 * marging;
  try {
    Rect pupilRect;
    pupilRect.x = rect.width*0.05;
    pupilRect.y = rect.height*0.05;
    pupilRect.width = rect.width * 0.9;
    pupilRect.height = rect.height * 0.9;
    subMat = img(toCv(rect));
    score = computeFocus(subMat);
    equalizeHist(subMat, subMat);
    Mat pupilMat = subMat(pupilRect);
  } catch ( cv::Exception ) {
    ofLogVerbose("gorgoneEyeDetection") << "oups wrong ROI" << endl;
    jamoma->mIrisDetectedReturn.set("value", false);
    jamoma->mPupilDetectedReturn.set("value", false);
    return false;
  }

  jamoma->mFocusDetectedReturn.set("value", score);
  if ( score < bestScore ) {
    jamoma->mIrisDetectedReturn.set("value", false);
    jamoma->mPupilDetectedReturn.set("value", false);
    return false;
  }

  bool _iris = findIris(subMat, iris);
  jamoma->mIrisDetectedReturn.set("value", _iris);
  if (!_iris) {
    jamoma->mPupilDetectedReturn.set("value", false);
    return false;
  }
  bool _pupil = findPupil(subMat, iris, pupil);
  jamoma->mPupilDetectedReturn.set("value", _pupil);
  if (!_pupil) return false;

  bestEye = subMat.clone();
  bestIris = iris;
  bestPupil = pupil;
  bestScore = score;
  subMat2ofImg(subMat, eye);

  paramScore = score;
  ofLogVerbose("gorgoneEyeDetection") << "eye focus : " << score << endl;
  return true;
}

Mat gorgoneEyeDetection::getIrisCode(){
  return codeMat;
}

void gorgoneEyeDetection::drawEyes(){

  if(eye.isAllocated()) eye.draw(10,10,200,200);
  if(eyeProc.isAllocated()) eyeProc.draw(10,250,200,200);
  if(irisProc.isAllocated()) irisProc.draw(10,500,200,200);
  int height = bestEyeNorm.getHeight()*ofGetWidth()/bestEyeNorm.getWidth();
  if(bestEyeNorm.isAllocated()) bestEyeNorm.draw(0,ofGetHeight()-height,ofGetWidth(),height);

  string drawString = "best image -- score " + ofToString(bestScore);
  ofDrawBitmapStringHighlight(drawString, 10, 750);

  if(codeImg.isAllocated()) codeImg.draw(500,10);
  else { ofLogVerbose("gorgoneEyeDetection") << "codeImg is not allocated" << endl;}
#ifndef TARGET_RASPBERRY_PI
  gui.draw();
#endif
}

double gorgoneEyeDetection::computeFocus(Mat& mat){
    Mat sobel;
    Sobel(mat, sobel, -1, 1, 1);
    double score = norm(sum(sobel)) / sobel.total(); // compute image quality

    return score;
}

void gorgoneEyeDetection::save(){
  string basename = "images/" + ZeroPadNumber(ofGetYear()) + ZeroPadNumber(ofGetMonth()) + ZeroPadNumber(ofGetDay());
  basename += "-" + ZeroPadNumber(ofGetHours()) + ZeroPadNumber(ofGetMinutes()) + ZeroPadNumber(ofGetSeconds());

  ofLogVerbose("gorgoneEyeDetection") << "save eyes to " << basename << endl;
  eye .save(basename + "-crop.bmp" );
  bestEyeNorm.save(basename + ".bmp");
}

bool gorgoneEyeDetection::findIris(Mat& roiImg, Vec3f& iris){
  // assume src is grayscale

  vector<Vec3f> circles;

  Mat blurred;

  blur( roiImg, blurred, Size(3,3) );

  int minRad = 0.65 * roiImg.cols / 2.; // relative ratio of pupil computed from the extracted eyepair
  int maxRad = 0.87 * roiImg.cols / 2.;

  HoughCircles( blurred, circles, CV_HOUGH_GRADIENT, 1, roiImg.rows/2, param1, param2, minRad, maxRad );
  // cout << circles.size() << " cirlces found" << endl;

  if ( circles.size() != 1 ){
    ofLogVerbose("gorgoneEyeDetection") << "can't find any iris circle or too many" << endl;
    return false;
  }

  /// Draw the circles detected
  int idx = -1;
  bool rtn = false;
  double bestDistance = 1;
  for( size_t i = 0; i < circles.size(); i++ )
  {
    Point center(round(circles[i][0]), round(circles[i][1]));
    int radius = round(circles[i][2]);
    // circle center

    circle( roiImg, center, 3, Scalar(255,255,255), -1, 8, 0 );
    // circle outline
    circle( roiImg, center, radius, Scalar(255,255,255), 1, 8, 0 );

    //iris += circles[i];

    if ( circles[i][2] < 40 ) {
      ofLogVerbose("gorgoneEyeDetection") << "iris too small" << endl;
    } else {

      double distance = pow((circles[i][0] - roiImg.cols/2) / roiImg.cols,2)
                         + pow((circles[i][1] - roiImg.rows/2) / roiImg.rows,2);

      if ( distance< 0.2 )
      {
        rtn = true;
        if ( distance < bestDistance ){
          bestDistance = distance;
          idx = i;
        }
      }
    }
  }

if ( idx >= 0 ){
  iris[0] = circles[idx][0];
  iris[1] = circles[idx][1];
  iris[2] = circles[idx][2];
}

  ofLogVerbose("gorgoneEyeDetection") << "iris " << iris[0] << ";" << iris[1] << " " << iris[2] << endl;

  subMat2ofImg(roiImg, irisProc);

  return rtn;
}


bool gorgoneEyeDetection::findPupil(Mat& src_gray, const Vec3f& iris, Vec3f& pupil){

  vector<Vec3f> circles;
  // now find the pupil in a square inside the iris
  int r = floor( iris[2] / sqrt(2) );
  ofLogVerbose("gorgoneEyeDetection") << "r " << r << endl;
  Rect pupilRoi = Rect(iris[0] - r, iris[1] - r, r * 2, r * 2);
  printRect(pupilRoi, "pupilRoi");
  Mat roiImg;
  try {
    roiImg = src_gray(pupilRoi).clone();
  } catch (cv::Exception e) {
    return false;
  }

  equalizeHist(roiImg, roiImg);

  cv::threshold(roiImg, roiImg, 240, 0, THRESH_TOZERO_INV);
  //cv::threshold(roiImg, roiImg, 30, 255, THRESH_BINARY);
  erode(roiImg, roiImg, 2);
  blur(roiImg,roiImg, Size(3,3));

  //blur( roiImg, blurred, Size(3,3) );
  HoughCircles( roiImg, circles, CV_HOUGH_GRADIENT, 1, roiImg.cols, param1, param2, iris[2]*0.15, iris[2]*0.8);

  if ( circles.empty() ){
    ofLogVerbose("gorgoneEyeDetection") << "can't find any pupil circle" << endl;
    return false;
  }

  int idx = -1;
  bool rtn = false;
  double bestDistance = 1;
  for( size_t i = 0; i < circles.size(); i++ )
  {
      Point center(round(circles[i][0] + pupilRoi.x ), round(circles[i][1] + pupilRoi.y));
      int radius = round(circles[i][2]);
      // circle center
      circle( roiImg, Point(circles[i][0], circles[i][1]), radius, 128, 1, 8, 0);
      // circle outline
      circle( src_gray, center, radius, Scalar(255,255,255), -1, 8, 0 );

      if ( circles[i][2] < 40 ) {
      ofLogVerbose("gorgoneEyeDetection") << "iris too small" << endl;
    } else {

      double distance = pow((circles[i][0] - roiImg.cols/2) / roiImg.cols,2)
                         + pow((circles[i][1] - roiImg.rows/2) / roiImg.rows,2);

      if ( distance < 0.2 )
      {
        rtn |= true;
        if ( distance < bestDistance ){
          bestDistance = distance;
          idx = i;
        }
      }
    }
  }

  if ( idx >= 0 ){
    pupil[0] = circles[idx][0] + pupilRoi.x;
    pupil[1] = circles[idx][1] + pupilRoi.y;
    pupil[2] = circles[idx][2];
  }

  ofLogVerbose("gorgoneEyeDetection") << "pupil " << pupil[0] << ";" << pupil[1] << " " << pupil[2] << endl;

  subMat2ofImg(roiImg, eyeProc);

  return rtn;
}

// most of the code below is taken from VASIR CreateTemplate::newCreateIrisTemplate(...) method

Masek::IMAGE* gorgoneEyeDetection::findEyelid(Mat& img, const Vec3f& pupil, const Vec3f& iris){
  //find the upper and lower eyelids
  // TODO mermory leak in ImageUtility and probably in FindEyelidCurve too
  double x[3]={0}, ty[3]={0}, by[3]={0};
  ImageUtility *imgUtil = NULL;
  FindEyelidCurve *eyelid = NULL;
  IplImage eyeImg = img;
  Masek::IMAGE* noiseImage = imgUtil->convertIplToImage(&eyeImg);
  delete imgUtil;

  eyelid->findCurves(&eyeImg, pupil[0], pupil[1], pupil[2],
                            iris[0],  iris[1],  iris[2],
                            x, ty, by);

  int size =(int)(x[2]-x[0]+1);
  int *destTY = new int[size];
  int *destBY = new int[size];

  eyelid->calcCurvePoints(&eyeImg, x, ty, destTY);
  eyelid->calcCurvePoints(&eyeImg, x, by, destBY);

  // error at this function
  eyelid->maskOutNoise(noiseImage, x, destTY, destBY);
  delete[] destTY;
  delete[] destBY;
  delete eyelid;

  /// \todo Possible to optimize?
  //Find the eyelashes and reflections on the iris region
  const int min=3, max=250;
  //FindHighLights::removeHighLights2(noiseImage, min, max);//5, 230
  FindHighLights::removeHighLights2(noiseImage,min, max);

  return noiseImage;
}

void gorgoneEyeDetection::threadedFunction()
{
  if ( !bestEye.total() > 0 ) return;
  noise  = findEyelid(bestEye,  bestPupil,  bestIris);

  encodeIris(noise, bestIris, bestPupil, codeMat);

  freeMasekImage(noise);

  ofLogVerbose("gorgoneEyeDetection") << "leftCode : " << codeMat.cols << "x" << codeMat.rows << endl;
  subMat2ofImg(codeMat, codeImg);
  newCode=true;
}

void gorgoneEyeDetection::encodeIris(Masek::IMAGE* noiseImage, const Vec3f iris, const Vec3f pupil, Mat& codeMat){
   /********************************************************
   * Iris Normalization
   *********************************************************/
  /// \todo Possible to optimize?
  //size of the normalized image

  //Evaluation: April 11 2012 (better)
  int radialRes = 34;//orginal value: 20
  int angularRes = 260;//orignal value: 240

  if ( noiseImage == NULL ) return;

  Masek::filter polarArray;
  Masek::IMAGE noiseArray;
  Masek::filter* imgWithNoise;
  imgWithNoise = (Masek::filter*) malloc(sizeof(Masek::filter));
  imgWithNoise->hsize[0] = noiseImage->hsize[0];
  imgWithNoise->hsize[1] = noiseImage->hsize[1];
  imgWithNoise->data = (double*) malloc(sizeof(double)*noiseImage->hsize[0]*noiseImage->hsize[1]);

  for (int y = 0; y < noiseImage->hsize[0]; y++)
  {
    for (int x = 0; x < noiseImage->hsize[1]; x++)
    {
      if(noiseImage->data[x + y*noiseImage->hsize[1]] < 1)
        imgWithNoise->data[x + y*imgWithNoise->hsize[1]] = sqrt((double) -1);
      else
        imgWithNoise->data[x + y*imgWithNoise->hsize[1]] = (double)noiseImage->data[x + y*noiseImage->hsize[1]];
    }
  }
  // don't free here since noise is held by parent
  //free(noiseImage->data);
  //free(noiseImage);

  Normalization::normalizeiris(imgWithNoise, iris[0], iris[1], iris[2],
    pupil[0], pupil[1], pupil[2], (const int)radialRes, (const int)angularRes,
    &polarArray, &noiseArray);

  free(imgWithNoise->data);
  free(imgWithNoise);


  /********************************************************
  /* Iris Encoding
  *********************************************************/

  const int encodeScales = 1;
  const int mult = 1; //not applicable if using encodeScales = 1
  int minWaveLength = 18;
  double sigmaOnf = 0.55;//0.5
    //float coefThresRate = 0.0f;// for FX: 0.25 and 0.10

  float magLowerThresRate = 0.02f;
  float magUpperThresRate = 0.85f;

  int w,h;
  int *code, *mask;

  EncodeLee::newEncodeLee(&polarArray, &noiseArray, encodeScales, (const int)minWaveLength,
    mult, (const double)sigmaOnf, &code, &mask, &w, &h,
    magLowerThresRate, magUpperThresRate);

  codeMat = Mat(h, w, CV_8UC1);
  for ( int j = 0; j < h ; j++){
    for ( int i = 0; i < w ; i++){
      codeMat.at<uchar>(j,i) = code[j*w + i] * 255;
    }
  }

  free(polarArray.data);
  free(noiseArray.data);
  free(mask);
  free(code);
}
