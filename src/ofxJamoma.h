#pragma once

#include "TTModular.h"

// Callback function to get data's value back
TTErr DemoAppDataReturnValueCallback(const TTValue& baton, const TTValue& v);

class ofxJamoma
{
  public:
    void setup  ();
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
    TTObject mDataDecimalParameter;     // a parameter is relative to the state of our application
    TTObject mDataStringParameter;      // a parameter is relative to the state of our application
    TTObject mDataBoolParameter;        // a parameter is relative to the state of our application
    TTObject mDataMessage;              // a message is a kind of command to send to our application
    TTObject mDataReturn;               // a return is a kind of notification sent by our application

    void setupJamomaApp();
    void registerJamomaParam();

    friend TTErr DemoAppDataReturnValueCallback(const TTValue& baton, const TTValue& v);

};
