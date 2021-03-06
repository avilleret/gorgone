#pragma once

#include "TTModular.h"

// Callback function to get data's value back
TTErr DemoAppDataReturnValueCallback(const TTValue& baton, const TTValue& v);

class ofxJamoma
{
  public:
    void setup  (void* parent, string name, string ip);
    void exit   ();

  // private:
    // Declare the application manager, our application and another one
    TTObject mApplicationManager;
    TTObject mApplicationLocal;
    TTObject mApplicationRemote, mApplicationRemote2;

    TTString mAppLocalName, mAppRemoteName, mAppRemoteName2, mAppRemoteIp;

    // Declare protocol units to use
    TTObject mProtocolMinuit;
    TTObject mProtocolWebSocket;

        // Declare publicly all datas of our application to retreive them from the callback function
    TTObject mTrackEnableParameter, mMotionFlowEnableParameter;     // a parameter is relative to the state of our application
    TTObject mDrawingEnableParameter;   // a parameter is relative to the state of our application
    TTObject mComputeIrisCodeParameter; // a parameter is relative to the state of our application
    TTObject mDrawingCoeffParameter; // drawing coefficient
    TTObject mTrackingIrisCodeReturn, mTrackingIrisBlobAreaReturn; // iris code returns
    TTObject mTrackingLedBrightness, mTrackingLaserBrightness, mWhiteLedBrightness; // white & IR led and laser brightness
    TTObject mDrawingShapeXReturn, mDrawingShapeYReturn, mShapeSizeParameter; // drawing shape return
    TTObject mTrackingFlowReturn; // Motion flow return
    TTObject mStaticShapeParameter; // id of static shape to draw
    TTObject mEyeDetectedReturn, mIrisDetectedReturn, mFocusDetectedReturn, mPupilDetectedReturn; // send a bang when an eye is detected

    TTPtr mParent;

    void setupJamomaApp();
    void registerJamomaParam();

    friend TTErr DemoAppDataReturnValueCallback(const TTValue& baton, const TTValue& v);

};
