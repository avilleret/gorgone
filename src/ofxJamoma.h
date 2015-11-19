#pragma once

#include "TTModular.h"

// Callback function to get data's value back
TTErr DemoAppDataReturnValueCallback(const TTValue& baton, const TTValue& v);

class ofxJamoma
{
  public:
    void setup  (void* parent, string name);
    void exit   ();

  // private:
    // Declare the application manager, our application and another one
    TTObject mApplicationManager;
    TTObject mApplicationLocal;
    TTObject mApplicationRemote;

    TTString mAppLocalName, mAppRemoteName;

    // Declare protocol units to use
    TTObject mProtocolMinuit;
    TTObject mProtocolWebSocket;

        // Declare publicly all datas of our application to retreive them from the callback function
    TTObject mTrackEnableParameter;     // a parameter is relative to the state of our application
    TTObject mDrawingEnableParameter;   // a parameter is relative to the state of our application
    TTObject mComputeIrisCodeParameter; // a parameter is relative to the state of our application
    TTObject mDrawingCoeffParameter; // drawing coefficient
    TTObject mTrackingIrisCodeReturn; // iris code return
    TTObject mTrackingLedBrightness; // IR led brightness

    TTPtr mParent;

    void setupJamomaApp();
    void registerJamomaParam();

    friend TTErr DemoAppDataReturnValueCallback(const TTValue& baton, const TTValue& v);

};
