#pragma once

#include "ofMain.h"
#include "ofxCv.h"

#ifdef TARGET_RASPBERRY_PI
#include "ofxCvPiCam.h"
#endif // TARGET_RASPBERRY_PI

class crossVideoGrabber {
public:
  void setup(){setup("");};
  void setup(string filename);
  void update();
  void draw(){draw(0,0);};
  void draw(int x, int y);
#ifdef TARGET_RASPBERRY_PI
  cv::Mat getFrame(){return frame;};
  bool isFrameNew(){return newFrame;};
  int getWidth(){return 1920;};
#else
  cv::Mat getFrame(){if (videoFlag) return ofxCv::toCv(videoPlayer); else return ofxCv::toCv(cam);};
  bool isFrameNew(){if (videoFlag) return videoPlayer.isFrameNew(); else return cam.isFrameNew(); };
  int getWidth(){if (videoFlag) return videoPlayer.getWidth(); else return cam.getWidth(); };
#endif

private:
#ifdef TARGET_RASPBERRY_PI
  ofxCvPiCam cam;
  cv::Mat frame;
  bool newFrame;
#else
  ofVideoGrabber cam;
#endif

  bool videoFlag;
  ofVideoPlayer  videoPlayer;
};
