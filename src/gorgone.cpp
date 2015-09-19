#include "gorgone.h"

void gorgone::setup()
{
  string cascadeFilePath = ofFilePath::getAbsolutePath("Cascade/parojosG_45x11.xml");
  try {
    eyeDetection = new EyeDetection(cascadeFilePath.c_str());
  } catch (const char* msg) {
    cout << "Error: Failed to load the cascade " << msg << endl;
  }

  faceFinder.setup("haarcascade_frontalface_default.xml");
  faceFinder.setPreset(ObjectFinder::Fast);

  eyeFinder.setup("parojosG_45x11.xml");

  setupVideoGrabber();
}

void gorgone::update()
{
  vidGrabber.update();
}

void gorgone::draw()
{
  vidGrabber.draw(0, 0, ofGetWidth(), ofGetHeight());

  if(vidGrabber.isFrameNew()){
    m_colorImg.setFromPixels(vidGrabber.getPixels());
    m_grayImg = m_colorImg;
    detectEyeRegion(m_grayImg);
  }

  drawEye();

  // m_grayImg.draw(0, 0, ofGetWidth(), ofGetHeight());
}

void gorgone::exit()
{
  if(eyeDetection != NULL)
    delete eyeDetection;
}

void gorgone::keyPressed(ofKeyEventArgs& key)
{
}

void gorgone::keyReleased(ofKeyEventArgs& key)
{
}

void gorgone::messageReceived(ofMessage& message)
{
}

void gorgone::setupVideoGrabber()
{
  camWidth = 640;  // try to grab at this size.
  camHeight = 480;

  //we can now get back a list of devices.
  vector<ofVideoDevice> devices = vidGrabber.listDevices();

  for(int i = 0; i < devices.size(); i++){
      if(devices[i].bAvailable){
          // ofLogNotice() << devices[i].id << ": " << devices[i].deviceName;
      } else {
          // ofLogNotice() << devices[i].id << ": " << devices[i].deviceName << " - unavailable ";
      }
  }

  vidGrabber.setDeviceID(0);
  vidGrabber.setDesiredFrameRate(60);
  vidGrabber.initGrabber(camWidth, camHeight);

  ofSetVerticalSync(true);
}

void gorgone::detectEyeRegion(ofxCvGrayscaleImage& input)
{
  // Video scales. 4: 2048x2048(MBGC Data), 2: 1024x1024, 1: 512x512
  const int scales = 1;
  // Eye region rectangl adjustment (pixel unit)
  const int val = 4;
  // Set the minimum size of the two eye regions to avoid false detection
  int w = 20, h = 4;

  // Use for the image quality measurement
  IplImage* img = NULL;

  int indexLeft = -1;
  int indexRight = -1;
  double prevLeftScore = -1;
  double prevRightScore = -1;
  try
  {
  // Check whether or not the cascade was loaded
    if(!eyeDetection)
    {
      cerr << "Load a cascade first" << endl;
      return;
    }
    else
    {
      int i = 1; //Number of detected images

      img = input.getCvImage();

      if (img == NULL) {
        cerr << "There is no more next image" << endl;
      }

      if(img != NULL) {
        m_res = eyeDetection->detect(img, scales, val, w, h);

        if (m_res == NULL)
        {
          cerr << "No eyes were detected" << endl;
        } else {
          // Draw rectangles for each detected eye region
          // imgWidget->addRectange(res->leftRect);
          // imgWidget->addRectange(res->rightRect);
          drawEye();
          cout << "Index: " << i << endl;

          //select the best-eye image without the pupil position alignment
          selectBestEye(m_res->leftImg, i, indexLeft, m_leftEye.getCvImage(), prevLeftScore);
          selectBestEye(m_res->rightImg, i, indexRight, m_rightEye.getCvImage(), prevRightScore);

          //select the best-eye image with the pupil position alignment
          //selectBestEyePairImage(res->leftImg, res->bothImg, i, indexLeft, imgForLeftEye, prevLeftScore);
          //selectBestEyePairImage(res->rightImg, res->bothImg, i, indexRight, imgForRightEye, prevRightScore);

          //@Analysis purpose
          // Save detected left and right image
#if 0
          ImageUtility::SaveImageOptions(res->leftImg, fileName, j, "L", i, imgSrc->getNumberOfImages());
          ImageUtility::SaveImageOptions(res->rightImg, fileName, j, "R", i, imgSrc->getNumberOfImages());
#endif

          i++;
        }
      }

      // drawBestImage(fileName, indexLeft, indexRight, imgForLeftEye, imgForRightEye);

      //This is an option
      /*//Align the left and right eye position using pupil information and then extract the eye region
      IplImage* extractedLeftImg = NULL;
      IplImage* extractedRightImg = NULL;
      alignExractEyeImage(imgForLeftEye, imgForRightEye, NIR_FACE_VIDEO, "bmp", extractedLeftImg, extractedRightImg);
      cvReleaseImage(&imgForLeftEye);
      cvReleaseImage(&imgForRightEye);

      // Draw best-eye image
      drawBestImage(fileName, indexLeft, indexRight, extractedLeftImg, extractedRightImg);//with pupil alignment
      cvReleaseImage(&extractedLeftImg);
      cvReleaseImage(&extractedRightImg);*/

    }
  }
  catch (const char* msg)
  {
    cout << "Error: " << msg << endl;
  }
}

void gorgone::selectBestEye(IplImage* currentImg, int index, int &bestIndex, IplImage* bestImg, double& bestScore)
{
  // Calculate the quality score
  double score = ImageQuality::doProcess(currentImg, 0);//0: SOBEL
  cout << "Quality score: " << score << endl;

  // Select the best image quality score
  if (score > bestScore)
  {
    // Release previous - if any
    if (bestImg != NULL)
      cvReleaseImage(&bestImg);

    // Copy the best image to bestImg
    bestImg = cvCloneImage(currentImg);
    bestScore = score;
        bestIndex = index;
  }
}

void gorgone::drawEye()
{
  if (m_res){
    CvRect left, right;
    left = m_res->leftRect;
    right = m_res->rightRect;
    ofDrawRectangle(left.x,left.y,left.width,left.height);
    ofDrawRectangle(right.x,right.y,right.width,right.height);
  }
}
