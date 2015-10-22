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
  gui.setup("Eye detection");
  gui.add(param1.set("Hough 1st parameter",104,0,255));
  gui.add(param2.set("Hough 2nd parameter",12,0,255));
  gui.add(paramThresh.set("rotation threshold", 0, 0, 180));
  scale=1.;

  reset();
}

void gorgoneEyeDetection::reset(){
  bSetup = true;
  flag = false;
  bestScore = 0.;
}

void gorgoneEyeDetection::update(Mat& img){

  Mat drawing;
  Mat eyeRoiMat;
  Vec3f iris, pupil;
  Rect eyeRoi;

  cout << "---------- UPDATE ----------" << endl;
  if(!bSetup) setup(img);
    imgRoi = img;
    /*
    Ptr<CLAHE> clahe = createCLAHE();
    clahe->setClipLimit(4);
    clahe->apply(imgRoi,normalized);
    **/
    equalizeHist(imgRoi, normalized);
    drawing = normalized.clone();
    // Rect roi = Rect(img.cols/4,img.rows/4, img.cols/2,img.rows/2);
    cout << "drawing size : " << drawing.cols << "x" << drawing.rows << endl;
    eyeRoi = Rect( (img.cols - img.rows )/2, 0, img.rows, img.rows); // take only the center square into account

    findPupil(drawing, pupil);
    subMat2ofImg(drawing,bothEyesNorm);

    Mat sobel;
    Sobel(normalized, sobel, -1, 1, 1);
    double score = norm(sum(sobel)) / sobel.total(); // compute image quality

    bool best = false;

    cout << "score is : " << score << endl;
    if ( score >  bestScore ){
      best=true;
    } else { return; }
    /*
    if ( findIris (leftRoiMat, leftIris)
         && findPupil(leftRoiMat,  leftIris, leftPupil)
         && findIris (rightRoiMat, rightIris)
         && findPupil(rightRoiMat, rightIris, rightPupil))
    {

      Point a = Point ( leftIris[0],   leftIris[1]);
      Point a2 = Point ( leftPupil[0], leftPupil[1]);
      Point b = Point (rightIris[0],  rightIris[1]);
      Point b2 = Point (rightPupil[0], rightPupil[1]);

      if ( norm(a-a2) > leftPupil[2] || norm(b-b2) > rightPupil[2] ){
        cout << "iris center outside pupil : wrong detection" << endl;
        return;
      } else {
        // image could be considered as "best" only if it is focused enough AND pupil are successfully detected
        bestScore = score;
        subMat2ofImg(normalized,bestEyesNorm);
      }

      a += Point ( leftRoi.x,   leftRoi.y);
      b += Point ( rightRoi.x, rightRoi.y);
      line(drawing, a, b, 255);


      leftRoi2  = Rect( leftIris[0] - leftIris[2] + leftRoi.x,
                        leftIris[1] - leftIris[2] + leftRoi.y,
                        leftIris[2] * 2,
                        leftIris[2] * 2);

      rightRoi2 = Rect(rightIris[0] - rightIris[2] + rightRoi.x,
                       rightIris[1] - rightIris[2] + rightRoi.y,
                       rightIris[2] * 2,
                       rightIris[2] * 2);

      leftEyeMat = normalized(leftRoi2);
      rightEyeMat = normalized(rightRoi2);

      // alignEye(normalized, leftRoi2, rightRoi2, leftIris, rightIris);

      leftNoise  = findEyelid(leftEyeMat,  leftPupil,  leftIris);
      rightNoise = findEyelid(rightEyeMat, rightPupil, rightIris);

      encodeIris(leftNoise, leftIris, leftPupil, leftCodeMat);
      encodeIris(rightNoise, rightIris, rightPupil, rightCodeMat);

      freeMasekImage(leftNoise);
      freeMasekImage(rightNoise);

      cout << "leftCode : " << leftCodeMat.cols << "x" << leftCodeMat.rows << endl;
      subMat2ofImg( leftCodeMat, leftCodeImg);
      subMat2ofImg(rightCodeMat, rightCodeImg);

      printVec (leftIris,  "leftIris");
      printVec (rightIris, "rightIris");
      printRect(leftRoi,   "leftRoi");
      printRect(rightRoi,  "rightRoi");
      printRect(leftRoi2,  "leftRoi2");
      printRect(rightRoi2, "rightRoi2");

      subMat2ofImg(leftEyeMat, leftEye);
      subMat2ofImg(rightEyeMat, rightEye);
    }
    */
}

void gorgoneEyeDetection::drawEyes(){
  //drawMat(bothEyesNorm,0,ofGetHeight()-bothEyesNorm.rows,ofGetWidth(),bothEyesNorm.rows*ofGetWidth()/bothEyesNorm.cols);
  if(eye.isAllocated()) eye.draw(10,10,200,200);
  if(eyeProc.isAllocated()) eyeProc.draw(10,250,200,200);
  int height = bothEyesNorm.getHeight()*ofGetWidth()/bothEyesNorm.getWidth();
  if(bothEyesNorm.isAllocated()) bothEyesNorm.draw(0,ofGetHeight()-height,ofGetWidth(),height);

  // if (bestEyesNorm.isAllocated()) bestEyesNorm.draw(500,250,bestEyesNorm.getWidth()*0.4, bestEyesNorm.getHeight()*0.4);
  string drawString = "best image -- score " + ofToString(bestScore);
  ofDrawBitmapStringHighlight(drawString, 500, 250);

  ofDrawBitmapStringHighlight(drawString, 0, ofGetHeight());

  if(codeImg.isAllocated()) codeImg.draw(500,10);
  else { cout << "codeImg is not allocated" << endl;}

  gui.draw();
}

void gorgoneEyeDetection::save(){
  string basename = "images/" + ZeroPadNumber(ofGetYear()) + ZeroPadNumber(ofGetMonth()) + ZeroPadNumber(ofGetDay());
  basename += "-" + ZeroPadNumber(ofGetHours()) + ZeroPadNumber(ofGetMinutes()) + ZeroPadNumber(ofGetSeconds());

  cout << "save eyes to " << basename << endl;
  eye .save(basename + "-crop.bmp" );
  bothEyesNorm.save(basename + ".bmp");
}

bool gorgoneEyeDetection::findPupil(Mat& img, Vec3f& iris){
  // assume src is grayscale

  vector<Vec3f> circles;
  Mat thresh;
  // threshold(img,thresh,paramThresh);
  Mat img_scaled = img;

  int minRad, maxRad, minDist;
  Mat blurred;
  blur( img_scaled, blurred, Size(3,3) );


  minRad = 75;
  maxRad = 200;
  minDist = 500;

  cout << "minRad : " << minRad << " maxRad : " << maxRad << endl;

  HoughCircles( blurred, circles, CV_HOUGH_GRADIENT, 2, minDist, param1, param2, minRad, maxRad );
  // cout << circles.size() << " cirlces found" << endl;

  if ( circles.empty() ){
    cout << "can't find any iris circle" << endl;
    return false;
  }
  double lowestBrightness = 255.;
  int darkestCircle = -1;

  for( size_t i = 0; i < circles.size(); i++ )
  {
    Rect roi = Rect(circles[i][0] - circles[i][2], circles[i][1] - circles[i][2], circles[i][2] * 2, circles[i][2] * 2);
    printRect(roi, "roi");
    // if ( roi.x > 0 && roi.y > 0 && roi.width >  2 && roi.height > 2 ) {
    try {
      Mat subMat = img(roi);
      Mat mask = Mat(subMat.size(), CV_8UC1, Scalar(0,0,0));
      circle(mask, Point(mask.cols/2, mask.rows/2), mask.cols/2, Scalar(255,255,255), -1, 8, 0);
      Mat masked;
      subMat.copyTo(masked, mask);
      double brightness = sum(subMat)[0] / subMat.total();
      if ( brightness < lowestBrightness ){
        darkestCircle = i;
        lowestBrightness = brightness;
      }
    } catch ( cv::Exception ) {
      cout << "invalid Roi" << endl;
    }
  }

  if ( darkestCircle < 0 ){
    cout << "no valid roi found" << endl;
  }
  cout << "lowestBrightness : " << lowestBrightness << " darkestCircle : " << darkestCircle << endl;

  int i = darkestCircle;

  Point center(round(circles[i][0] * scale), round(circles[i][1] * scale));
  int radius = round(circles[i][2] * scale);
  // circle center

  circle( img, center, 3, Scalar(255,255,255), -1, 8, 0 );
  // circle outline
  circle( img, center, radius, Scalar(255,255,255), 1, 8, 0 );

  //iris += circles[i];

  //iris /= (double)circles.size();

  iris[0] = circles[0][0];
  iris[1] = circles[0][1];
  iris[2] = circles[0][2];
  cout << "iris " << iris[0] << ";" << iris[1] << " " << iris[2] << endl;

  if ( iris[2] < 40 ) {
    cout << "iris too small" << endl;
    return false;
  }

  return true;
}

bool gorgoneEyeDetection::findIris(Mat& src_gray, const Vec3f& iris, Vec3f& pupil){

  vector<Vec3f> circles;
  // now find the pupil in a square inside the iris
  int r = floor( iris[2] / sqrt(2) );
  cout << "r " << r << endl;
  Rect pupilRoi = Rect(iris[0] - r, iris[1] - r, r * 2, r * 2);
  printRect(pupilRoi, "pupilRoi");
  Mat roiImg;
  try {
    roiImg = src_gray(pupilRoi).clone();
  } catch (cv::Exception e) {
    cout << "pupilRoi seems to be wrong" << endl;
    return false;
  }

  equalizeHist(roiImg, roiImg);

  cv::threshold(roiImg, roiImg, 240, 0, THRESH_TOZERO_INV);
  //cv::threshold(roiImg, roiImg, 30, 255, THRESH_BINARY);
  erode(roiImg, roiImg, 2);
  blur(roiImg,roiImg, Size(3,3));

  //blur( roiImg, blurred, Size(3,3) );
  HoughCircles( roiImg, circles, CV_HOUGH_GRADIENT, 1, roiImg.cols, param1, param2, 0, iris[2]/3);

  if ( circles.empty() ){
    cout << "can't find any pupil circle" << endl;
    return false;
  }

  for( size_t i = 0; i < circles.size(); i++ )
  {
      Point center(round(circles[i][0] + pupilRoi.x ), round(circles[i][1] + pupilRoi.y));
      int radius = round(circles[i][2]);
      // circle center
      circle( roiImg, Point(circles[i][0], circles[i][1]), radius, 128, 1, 8, 0);
      // circle outline
      circle( src_gray, center, radius, Scalar(255,255,255), -1, 8, 0 );
  }

  pupil[0] = circles[0][0] + pupilRoi.x;
  pupil[1] = circles[0][1] + pupilRoi.y;
  pupil[2] = circles[0][2];

  cout << "pupil " << pupil[0] << ";" << pupil[1] << " " << pupil[2] << endl;

  return true;
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
