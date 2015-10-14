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
  bestScore = 0.;
  gui.setup("Eye detection");
  gui.add(param1.set("Hough 1st parameter",104,0,255));
  gui.add(param2.set("Hough 2nd parameter",12,0,255));

  eyeFinder.setup("cascade/parojosG_45x11.xml");
  eyeFinder.setRescale(200./(float)img.cols);
  // eyeFinder.setPreset(ofxCv::ObjectFinder::Accurate);

  bSetup = true;
  flag = false;
}

void gorgoneEyeDetection::update(Mat& img){

  cout << "---------- UPDATE ----------" << endl;
  if(!bSetup) setup(img);

  eyeFinder.update(img);

  for ( int i = 0; i < eyeFinder.size() ; i++ ){
    ofRectangle rect = eyeFinder.getObject(i);
    if ( rect.width > img.cols/2 ) {
      imgRoi = img(toCv(rect)); // get the region of interest (ROI), i.e. the eyes, from origin image.

      int eyeWidth = rect.width * 0.18; // relative width of an eye in the detected eyes pair
      int eyeHeight = rect.height * 0.75;
      int eyeOffset = rect.width * 0.12;

      equalizeHist(imgRoi, normalized);
      Mat drawing = normalized.clone();

      Rect leftRoi =  Rect(eyeOffset,                         (rect.height-eyeHeight)/2, eyeWidth, eyeHeight);
      Rect rightRoi = Rect(rect.width - eyeOffset - eyeWidth, (rect.height-eyeHeight)/2, eyeWidth, eyeHeight);

      Rect leftRoi2, rightRoi2;
      Vec3f leftIris, rightIris, leftPupil, rightPupil;

      cout << "drawing size : " << drawing.cols << "x" << drawing.rows << endl;

      Mat leftRoiMat = drawing(leftRoi);
      Mat rightRoiMat = drawing(rightRoi);

      if ( findIris (leftRoiMat, leftIris) &&
           findPupil(leftRoiMat,  leftIris, leftPupil) &&
           findIris (rightRoiMat, rightIris) &&
           findPupil(rightRoiMat, rightIris, rightPupil))
      {

        Point a = Point ( leftIris[0],   leftIris[1]);
        Point a2 = Point ( leftPupil[0], leftPupil[1]);
        Point b = Point (rightIris[0],  rightIris[1]);
        Point b2 = Point (rightPupil[0], rightPupil[1]);

        if ( norm(a-a2) > leftPupil[2] || norm(b-b2) > rightPupil[2] ){
          cout << "iris center outside pupil : wrong detection" << endl;
          return;
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

        alignEye(normalized, leftRoi2, rightRoi2, leftIris, rightIris);


        Mat L = normalized(leftRoi2);
        Mat R = normalized(rightRoi2);
        leftNoise  = findEyelid(L,  leftPupil,  leftIris);
        rightNoise = findEyelid(R, rightPupil, rightIris);

        encodeIris(leftNoise, leftIris, leftPupil, leftCodeMat);
        encodeIris(rightNoise, rightIris, rightPupil, rightCodeMat);

        freeMasekImage(leftNoise);
        freeMasekImage(rightNoise);

        cout << "leftCode : " << leftCodeMat.cols << "x" << leftCodeMat.rows << endl;
        subMat2ofImg( leftCodeMat, leftCodeImg);
        subMat2ofImg(rightCodeMat, rightCodeImg);

        // rotate eye
        subMat2ofImg(drawing,bothEyesNorm);
        // subMat2ofImg( leftIrisMat, leftEye);
        // subMat2ofImg(rightIrisMat,rightEye);

        printVec (leftIris,  "leftIris");
        printVec (rightIris, "rightIris");
        printRect(leftRoi,   "leftRoi");
        printRect(rightRoi,  "rightRoi");
        printRect(leftRoi2,  "leftRoi2");
        printRect(rightRoi2, "rightRoi2");

        subMat2ofImg(imgRoi( leftRoi2 ), leftEye);
        subMat2ofImg(imgRoi( rightRoi2 ), rightEye);


      }

      Mat sobel;
      Sobel(normalized, sobel, -1, 1, 1);
      double score = norm(sum(sobel)) / sobel.total(); // compute image quality

      cout << "score is : " << score << endl;
      if ( rect.width > img.cols / 3 ){ // detected rectangle should be at least 1/3 of the image.
        bestScore = score;

        // leftEye.cropFrom(origin, rect.x, rect.y, eyeWidth, rect.height);
        // rightEye.cropFrom(origin, rect.x + rect.width - eyeWidth, rect.y, eyeWidth, rect.height);

        // alignExractEyeImage(imgRoi,imgRoi,1,"bmp",left,right);

        // alignExtractEyeNew(imgRoi, left, right, rect);
        // leftAligned.update();
        // rightAligned.update();
      }

      // bothEyes.cropFrom(origin, rect.x, rect.y, rect.width, rect.height);
    }
  }
}

void gorgoneEyeDetection::drawEyes(){
  string drawString = "score " + ofToString(bestScore);
  //drawMat(bothEyesNorm,0,ofGetHeight()-bothEyesNorm.rows,ofGetWidth(),bothEyesNorm.rows*ofGetWidth()/bothEyesNorm.cols);
  if(leftEye.isAllocated()) leftEye.draw(10,10,200,200);
  if(rightEye.isAllocated()) rightEye.draw(250,10,200,200);
  if(leftProc.isAllocated()) leftProc.draw(10,250,200,200);
  if(rightProc.isAllocated()) rightProc.draw(250,250,200,200);
  int height = bothEyesNorm.getHeight()*ofGetWidth()/bothEyesNorm.getWidth();
  if(bothEyesNorm.isAllocated()) bothEyesNorm.draw(0,ofGetHeight()-height,ofGetWidth(),height);

  if(leftCodeImg.isAllocated()) leftCodeImg.draw(500,10);
  else { cout << "leftCodeImg is not allocated" << endl;}
  if(rightCodeImg.isAllocated()) rightCodeImg.draw(500, 250);
  else { cout << "rightCodeImg is not allocated" << endl;}

  ofDrawBitmapStringHighlight(drawString, ofGetWidth()/2, 10);
  gui.draw();
}

void gorgoneEyeDetection::save(){
  string basename = "images/" + ZeroPadNumber(ofGetYear()) + ZeroPadNumber(ofGetMonth()) + ZeroPadNumber(ofGetDay());
  basename += "-" + ZeroPadNumber(ofGetHours()) + ZeroPadNumber(ofGetMinutes()) + ZeroPadNumber(ofGetSeconds());

  cout << "save eyes to " << basename << endl;
  //imwrite(basename + "-left.bmp", leftEye);
  //imwrite(basename + "-right.bmp", rightEye);
  //imwrite(basename + ".bmp", bothEyesNorm);
  leftEye .save(basename + "-left.bmp" );
  rightEye.save(basename + "-right.bmp");
  bothEyesNorm.save(basename + ".bmp");
}

//Align the left and right eye position using pupil information and then extract the eye region
void gorgoneEyeDetection::alignEye(Mat src_gray, const Rect leftRoi, const Rect rightRoi, Vec3f leftIris, Vec3f rightIris)
{
  // rotate eyeImg according to angle between two eyes
}

bool gorgoneEyeDetection::findIris(Mat& roiImg, Vec3f& iris){
  // assume src is grayscale

  vector<Vec3f> circles;

  Mat blurred;

  blur( roiImg, blurred, Size(3,3) );

  int minRad = 0.06 / 0.18 * roiImg.cols; // relative ratio of pupil computed from the extracted eyepair
  int maxRad = 0.07 / 0.18 * roiImg.cols;

  HoughCircles( blurred, circles, CV_HOUGH_GRADIENT, 1, roiImg.rows/8, param1, param2, minRad, maxRad );
  // cout << circles.size() << " cirlces found" << endl;

  if ( circles.empty() ){
    cout << "can't find any iris circle" << endl;
    return false;
  }

  /// Draw the circles detected
  for( size_t i = 0; i < circles.size(); i++ )
  {
      Point center(round(circles[i][0]), round(circles[i][1]));
      int radius = round(circles[i][2]);
      // circle center

      circle( roiImg, center, 3, Scalar(255,255,255), -1, 8, 0 );
      // circle outline
      circle( roiImg, center, radius, Scalar(255,255,255), 1, 8, 0 );

      //iris += circles[i];
  }
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

bool gorgoneEyeDetection::findPupil(Mat& src_gray, const Vec3f& iris, Vec3f& pupil){

  vector<Vec3f> circles;
  // now find the pupil in a square inside the iris
  int r = floor( iris[2] / sqrt(2) );
  cout << "r " << r << endl;
  Rect pupilRoi = Rect(iris[0] - r, iris[1] - r, r * 2, r * 2);
  printRect(pupilRoi, "pupilRoi");
  Mat roiImg = src_gray(pupilRoi).clone();
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

  flag = !flag;
  subMat2ofImg(roiImg, flag ? leftProc : rightProc);

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
