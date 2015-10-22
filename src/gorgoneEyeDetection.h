#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "ofxGui.h"
#include "Masek.h"

using namespace cv;
using namespace ofxCv;

class gorgoneEyeDetection {
public:
  template <class T>
  void computeScore(T& img) {
    computeScore(ofxCv::toCv(img));
  }
  void update(cv::Mat& img);
  void setup(const cv::Mat& img);
  void reset();
  void drawEyes();
  void save();
  bool findPupil(Mat& src_gray, Vec3f& iris);
  bool findIris(Mat& src_gray, const Vec3f& iris, Vec3f& pupil);
  Masek::IMAGE* findEyelid(Mat& img, const Vec3f& pupil, const Vec3f& iris);
  void encodeIris(Masek::IMAGE* noiseImage, const Vec3f iris, const Vec3f pupil, Mat& code);

  ofxPanel gui;
  ofParameter<int> param1, param2, paramThresh;

private:
  bool bSetup, flag, eyeCloseUp;
  double bestScore, scale;
  ofImage bothEyesNorm, bestEyesNorm, eye, eyeProc, codeImg;
  Mat normalized, imgRoi;
  Masek::IMAGE *noise;
  Mat eyeMat, codeMat;

  static std::string ZeroPadNumber(int num)
  {
    std::ostringstream ss;
    ss << std::setw( 2 ) << std::setfill( '0' ) << num;
    return ss.str();
  }

  static void subMat2ofImg(Mat subMat, ofImage& img){
    imitate(img,subMat);
    Mat tmp = toCv(img);
    subMat.copyTo(tmp);
    img.update();
  }

  static void printRect(const Rect& rect, const string& name){
    cout << name << " : " << rect.x << ";" << rect.y << " " << rect.width << "x" << rect.height << endl;
  }

  template <class T>
  static void printVec(T& vec, const string& name){
    cout << name << ": ";
    for (int i = 0; i <  Mat(vec).total(); i++)
      std::cout << vec[i] << ' ';
    cout << endl;
  }

  static void freeMasekImage(Masek::IMAGE *&img){
    if(img) {
      free(img->data);
      free(img);
      img=NULL;
    }
  }
};
