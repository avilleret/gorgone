#include "ofxJamoma.h"
#include "gorgone.h"

void ofxJamoma::setup(void* parent, string name, string masterIp)
{
  mParent = TTPtr(parent);
  mAppLocalName = name;
  mAppRemoteName = "master";
  mAppRemoteName2 = "laser-" + name.substr(8);
  mAppRemoteIp = masterIp;
  setupJamomaApp();
  registerJamomaParam();
}

void ofxJamoma::exit()
{
}

void ofxJamoma::setupJamomaApp(){
    TTValue     args, v, out, none;
    TTAddress   address;
    TTErr       err;

    TTLogMessage("\n*** Initialisation of Modular environnement ***\n");
    /////////////////////////////////////////////////////////////////////

    // Init the Modular library (passing the folder path where all the dylibs are)
    TTModularInit("/usr/local/jamoma/lib/jamoma/");

    // Create an application manager
    mApplicationManager = TTObject("ApplicationManager");


    TTLogMessage("\n*** Creation of %s and %s applications ***\n", mAppLocalName.c_str(), mAppRemoteName.c_str());
    ////////////////////////////////////////////////////////////////////////////////

    // Create a local application called "gorgone-1" and get it back
    mApplicationLocal = mApplicationManager.send("ApplicationInstantiateLocal", mAppLocalName.c_str());
    mApplicationRemote = mApplicationManager.send("ApplicationInstantiateDistant", mAppRemoteName.c_str());
    mApplicationRemote2 = mApplicationManager.send("ApplicationInstantiateDistant", mAppRemoteName2.c_str());


    // Get registered application names
    mApplicationManager.get("applicationNames", out);
    for (TTElementIter it = out.begin() ; it != out.end() ; it++) {
        TTSymbol name = TTElement(*it);
        TTLogMessage("%s application is well registered into the application manager \n", name.c_str());
    }


    TTLogMessage("\n*** Enable Minuit communication ***\n");
    ////////////////////////////////////////////////////////////////////////

    // Create a Minuit protocol unit
    mProtocolMinuit = mApplicationManager.send("ProtocolInstantiate", "Minuit");

    // Get Minuit Protocol attribute names and types
    mProtocolMinuit.get("parameterNames", out);
    for (TTElementIter it = out.begin() ; it != out.end() ; it++) {
        TTSymbol name = TTElement(*it);
        TTSymbol type = mProtocolMinuit.attributeType(name);
        TTLogMessage("Minuit %s parameter is a %s \n", name.c_str(), type.c_str());
    }

    // Register mymyRemoteAppApp and myRemoteApp to the Minuit protocol
    mProtocolMinuit.send("ApplicationRegister", mAppLocalName.c_str());
    mProtocolMinuit.send("ApplicationRegister", mAppRemoteName.c_str());
    mProtocolMinuit.send("ApplicationRegister", mAppRemoteName2.c_str());

    // Select gorgone-1 to set its protocol parameters
    mProtocolMinuit.send("ApplicationSelect", mAppLocalName.c_str());
    mProtocolMinuit.set("port", 9998);
    mProtocolMinuit.set("ip", "127.0.0.1");

    // Select gorgone-1 to set its protocol parameters
    mProtocolMinuit.send("ApplicationSelect", mAppRemoteName2.c_str());
    mProtocolMinuit.set("port", 9999);
    mProtocolMinuit.set("ip", "127.0.0.1");

    // Select myRemoteApp to set its protocol parameters
    mProtocolMinuit.send("ApplicationSelect", mAppRemoteName.c_str());
    mProtocolMinuit.set("port", 13579);
    mProtocolMinuit.set("ip", mAppRemoteIp.c_str());

    // Get Minuit parameters for each registered application
    mProtocolMinuit.get("applicationNames", out);
    for (TTElementIter it = out.begin() ; it != out.end() ; it++) {
        TTSymbol name = TTElement(*it);

        mProtocolMinuit.send("ApplicationSelect", name);
        TTLogMessage("Minuit setup for %s application : \n", name.c_str());

        mProtocolMinuit.get("ip", v);
        TTSymbol ip = v[0];
        TTLogMessage("- ip = %s \n", ip.c_str());

        mProtocolMinuit.get("port", v);
        TTUInt16 port = v[0];
        TTLogMessage("- port = %d \n", port);
    }

    // Enable Minuit communication
    mProtocolMinuit.send("Run");

    TTLogMessage("\n*** Current Protocol Setup ***\n");
    // Get protocol names
    mApplicationManager.get("protocolNames",out);
    for (TTElementIter it = out.begin() ; it != out.end() ; it++) {
        TTSymbol name = TTElement(*it);
        TTLogMessage("%s protocol is well registered into the application manager \n", name.c_str());
    }
}

void ofxJamoma::registerJamomaParam(){
    TTValue     args, v, out, none;
    TTAddress   address;
    TTErr       err;
      TTLogMessage("\n*** Creation and registration of a decimal parameter ***\n");
    /////////////////////////////////////////////////////////

    // Create a decimal parameter data and set its callback function and baton and some attributes
    mTrackEnableParameter = TTObject("Data", "parameter");

    // Setup the callback mechanism to get the value back
    args = TTValue(mParent, mTrackEnableParameter);
    mTrackEnableParameter.set("baton", args);
    mTrackEnableParameter.set("function", TTPtr(&DemoAppDataReturnValueCallback));

    // Setup the data attributes depending of its use inside the application
    mTrackEnableParameter.set("type", "boolean");
    mTrackEnableParameter.set("description", "start/stop tracking");

    // Register the parameter data into gorgone-1 at an address
    args = TTValue("/tracking/enable", mTrackEnableParameter);
    out = mApplicationLocal.send("ObjectRegister", args);
    address = out[0];
    TTLogMessage("\n /tracking/enable : effective registration address is %s \n", address.c_str());

        // Create a decimal parameter data and set its callback function and baton and some attributes
    mDrawingEnableParameter = TTObject("Data", "parameter");

    // Setup the callback mechanism to get the value back
    args = TTValue(mParent, mDrawingEnableParameter);
    mDrawingEnableParameter.set("baton", args);
    mDrawingEnableParameter.set("function", TTPtr(&DemoAppDataReturnValueCallback));

    // Setup the data attributes depending of its use inside the application
    mDrawingEnableParameter.set("type", "boolean");
    mDrawingEnableParameter.set("description", "start/stop drawing");

    // Register the parameter data into gorgone-1 at an address
    args = TTValue("/drawing/enable", mDrawingEnableParameter);
    out = mApplicationLocal.send("ObjectRegister", args);

    address = out[0];
    TTLogMessage("\n /drawing/enable : effective registration address is %s \n", address.c_str());

    // Create a new boolean parameter
    mMotionFlowEnableParameter = TTObject("Data", "parameter");

    // Setup the callback mechanism to get the value back
    args = TTValue(mParent, mMotionFlowEnableParameter);
    mMotionFlowEnableParameter.set("baton", args);
    mMotionFlowEnableParameter.set("function", TTPtr(&DemoAppDataReturnValueCallback));

    // Setup the data attributes depending of its use inside the application
    mMotionFlowEnableParameter.set("type", "boolean");
    mMotionFlowEnableParameter.set("description", "start/stop motion detection");

    // Register the parameter data into gorgone-1 at an address
    args = TTValue("/motion/enable", mMotionFlowEnableParameter);
    out = mApplicationLocal.send("ObjectRegister", args);
    address = out[0];
    TTLogMessage("\n /motion/enable : effective registration address is %s \n", address.c_str());

    // Create a new boolean parameter
    mComputeIrisCodeParameter = TTObject("Data", "parameter");

    // Setup the callback mechanism to get the value back
    args = TTValue(mParent, mComputeIrisCodeParameter);
    mComputeIrisCodeParameter.set("baton", args);
    mComputeIrisCodeParameter.set("function", TTPtr(&DemoAppDataReturnValueCallback));

    // Setup the data attributes depending of its use inside the application
    mComputeIrisCodeParameter.set("type", "boolean");
    mComputeIrisCodeParameter.set("description", "start/stop drawing");

    // Register the parameter data into gorgone-1 at an address
    args = TTValue("/tracking/computecode", mComputeIrisCodeParameter);
    out = mApplicationLocal.send("ObjectRegister", args);
    address = out[0];
    TTLogMessage("\n /tracking/computecode : effective registration address is %s \n", address.c_str());

    // Create a new array parameter
    mDrawingCoeffParameter = TTObject("Data", "parameter");

    // Setup the callback mechanism to get the value back
    args = TTValue(mParent, mDrawingCoeffParameter);
    mDrawingCoeffParameter.set("baton", args);
    mDrawingCoeffParameter.set("function", TTPtr(&DemoAppDataReturnValueCallback));

    // Setup the data attributes depending of its use inside the application
    mDrawingCoeffParameter.set("type", "array");
    mDrawingCoeffParameter.set("description", "shape coefficient");

    // Register the parameter data into gorgone-1 at an address
    args = TTValue("/drawing/coeff", mDrawingCoeffParameter);
    out = mApplicationLocal.send("ObjectRegister", args);
    address = out[0];
    TTLogMessage("\n /drawing/coeff : effective registration address is %s \n", address.c_str());

    // Create a new array return for iris code
    mTrackingIrisCodeReturn = TTObject("Data", "return");

    // Setup the callback mechanism to get the value back
    args = TTValue(mParent, mTrackingIrisCodeReturn);
    mTrackingIrisCodeReturn.set("baton", args);
    mTrackingIrisCodeReturn.set("function", TTPtr(&DemoAppDataReturnValueCallback));

    // Setup the data attributes depending of its use inside the application
    mTrackingIrisCodeReturn.set("type", "array");
    mTrackingIrisCodeReturn.set("description", "iris code");

    // Register the parameter data into gorgone-1 at an address
    args = TTValue("/tracking/iriscode", mTrackingIrisCodeReturn);
    out = mApplicationLocal.send("ObjectRegister", args);
    address = out[0];
    TTLogMessage("\n /tracking/iriscode : effective registration address is %s \n", address.c_str());

    // Create a new array return for iris code
    mTrackingIrisBlobAreaReturn = TTObject("Data", "return");

    // Setup the callback mechanism to get the value back
    args = TTValue(mParent, mTrackingIrisBlobAreaReturn);
    mTrackingIrisBlobAreaReturn.set("baton", args);
    mTrackingIrisBlobAreaReturn.set("function", TTPtr(&DemoAppDataReturnValueCallback));

    // Setup the data attributes depending of its use inside the application
    mTrackingIrisBlobAreaReturn.set("type", "array");
    mTrackingIrisBlobAreaReturn.set("description", "iris code");

    // Register the parameter data into gorgone-1 at an address
    args = TTValue("/tracking/iriscode_blobarea", mTrackingIrisBlobAreaReturn);
    out = mApplicationLocal.send("ObjectRegister", args);
    address = out[0];
    TTLogMessage("\n /tracking/iriscode_blobarea : effective registration address is %s \n", address.c_str());

        // Create a new array return for drawing shape
    mDrawingShapeXReturn = TTObject("Data", "return");

    // Setup the callback mechanism to get the value back
    args = TTValue(mParent, mDrawingShapeXReturn);
    mDrawingShapeXReturn.set("baton", args);
    mDrawingShapeXReturn.set("function", TTPtr(&DemoAppDataReturnValueCallback));

    // Setup the data attributes depending of its use inside the application
    mDrawingShapeXReturn.set("type", "array");
    mDrawingShapeXReturn.set("description", "drawing shape X");

    // Register the parameter data into gorgone-1 at an address
    args = TTValue("/drawing/shape/x", mDrawingShapeXReturn);
    out = mApplicationLocal.send("ObjectRegister", args);
    address = out[0];
    TTLogMessage("\n /drawing/shape/x : effective registration address is %s \n", address.c_str());

    // Create a new array return for drawing shape
    mDrawingShapeYReturn = TTObject("Data", "return");

    // Setup the callback mechanism to get the value back
    args = TTValue(mParent, mDrawingShapeYReturn);
    mDrawingShapeYReturn.set("baton", args);
    mDrawingShapeYReturn.set("function", TTPtr(&DemoAppDataReturnValueCallback));

    // Setup the data attributes depending of its use inside the application
    mDrawingShapeYReturn.set("type", "array");
    mDrawingShapeYReturn.set("description", "Drawing shape Y");

    // Register the parameter data into gorgone-1 at an address
    args = TTValue("/drawing/shape/y", mDrawingShapeYReturn);
    out = mApplicationLocal.send("ObjectRegister", args);
    address = out[0];
    TTLogMessage("\n /drawing/shape/y : effective registration address is %s \n", address.c_str());

    // Create a new brightness parameter
    mTrackingLedBrightness = TTObject("Data", "parameter");

    // Setup the callback mechanism to get the value back
    args = TTValue(mParent, mTrackingLedBrightness);
    mTrackingLedBrightness.set("baton", args);
    mTrackingLedBrightness.set("function", TTPtr(&DemoAppDataReturnValueCallback));

    // Setup the data attributes depending of its use inside the application
    mTrackingLedBrightness.set("type", "integer");
    mTrackingLedBrightness.set("description", "LED brightness");
    mTrackingLedBrightness.set("rangeBounds", TTValue(0, 1023));
    mTrackingLedBrightness.set("rangeClipmode", "both");

    // Register the parameter data into gorgone-1 at an address
    args = TTValue("/tracking/ledbrightness", mTrackingLedBrightness);
    out = mApplicationLocal.send("ObjectRegister", args);
    address = out[0];
    TTLogMessage("\n /tracking/ledbrightness : effective registration address is %s \n", address.c_str());

        // Create a new brightness parameter
    mWhiteLedBrightness = TTObject("Data", "parameter");

    // Setup the callback mechanism to get the value back
    args = TTValue(mParent, mWhiteLedBrightness);
    mWhiteLedBrightness.set("baton", args);
    mWhiteLedBrightness.set("function", TTPtr(&DemoAppDataReturnValueCallback));

    // Setup the data attributes depending of its use inside the application
    mWhiteLedBrightness.set("type", "array");
    mWhiteLedBrightness.set("description", "white LED brightness");
    mWhiteLedBrightness.set("rangeBounds", TTValue(0, 63));
    mWhiteLedBrightness.set("size", 4);
    mWhiteLedBrightness.set("rangeClipmode", "both");

    // Register the parameter data into gorgone-1 at an address
    args = TTValue("/wled/brightness", mWhiteLedBrightness);
    out = mApplicationLocal.send("ObjectRegister", args);
    address = out[0];
    TTLogMessage("\n /wled/brightness : effective registration address is %s \n", address.c_str());

    // Create a new brightness parameter
    mTrackingLaserBrightness = TTObject("Data", "parameter");

    // Setup the callback mechanism to get the value back
    args = TTValue(mParent, mTrackingLaserBrightness);
    mTrackingLaserBrightness.set("baton", args);
    mTrackingLaserBrightness.set("function", TTPtr(&DemoAppDataReturnValueCallback));

    // Setup the data attributes depending of its use inside the application
    mTrackingLaserBrightness.set("type", "decimal");
    mTrackingLaserBrightness.set("description", "laser brightness");
    mTrackingLaserBrightness.set("rangeBounds", TTValue(0., 100.));
    mTrackingLaserBrightness.set("rangeClipmode", "both");

    // Register the parameter data into gorgone-1 at an address
    args = TTValue("/drawing/laserbrightness", mTrackingLaserBrightness);
    out = mApplicationLocal.send("ObjectRegister", args);
    address = out[0];
    TTLogMessage("\n /drawing/laserbrightness : effective registration address is %s \n", address.c_str());

    // Create a new array return for drawing shape
    mTrackingFlowReturn = TTObject("Data", "return");

    // Setup the callback mechanism to get the value back
    args = TTValue(mParent, mTrackingFlowReturn);
    mTrackingFlowReturn.set("baton", args);
    mTrackingFlowReturn.set("function", TTPtr(&DemoAppDataReturnValueCallback));

    // Setup the data attributes depending of its use inside the application
    mTrackingFlowReturn.set("type", "decimal");
    mTrackingFlowReturn.set("description", "Total motion flow");

    // Register the parameter data into gorgone-1 at an address
    args = TTValue("/motion/flow", mTrackingFlowReturn);
    out = mApplicationLocal.send("ObjectRegister", args);
    address = out[0];
    TTLogMessage("\n /motion/flow : effective registration address is %s \n", address.c_str());

    // Create a new array return for drawing shape
    mEyeDetectedReturn = TTObject("Data", "return");

    // Setup the callback mechanism to get the value back
    args = TTValue(mParent, mEyeDetectedReturn);
    mEyeDetectedReturn.set("baton", args);
    mEyeDetectedReturn.set("function", TTPtr(&DemoAppDataReturnValueCallback));

    // Setup the data attributes depending of its use inside the application
    mEyeDetectedReturn.set("type", "boolean");
    mEyeDetectedReturn.set("description", "Total motion flow");

    // Register the parameter data into gorgone-1 at an address
    args = TTValue("/tracking/detected/eye", mEyeDetectedReturn);
    out = mApplicationLocal.send("ObjectRegister", args);
    address = out[0];
    TTLogMessage("\n/tracking/detected/eye : effective registration address is %s \n", address.c_str());

    // Create a new array return for drawing shape
    mIrisDetectedReturn = TTObject("Data", "return");

    // Setup the callback mechanism to get the value back
    args = TTValue(mParent, mIrisDetectedReturn);
    mIrisDetectedReturn.set("baton", args);
    mIrisDetectedReturn.set("function", TTPtr(&DemoAppDataReturnValueCallback));

    // Setup the data attributes depending of its use inside the application
    mIrisDetectedReturn.set("type", "boolean");
    mIrisDetectedReturn.set("description", "Return true if iris is well recognized");

    // Register the parameter data into gorgone-1 at an address
    args = TTValue("/tracking/detected/iris", mIrisDetectedReturn);
    out = mApplicationLocal.send("ObjectRegister", args);
    address = out[0];
    TTLogMessage("\n/tracking/detected/iris : effective registration address is %s \n", address.c_str());

    // Create a new array return for drawing shape
    mFocusDetectedReturn = TTObject("Data", "return");

    // Setup the callback mechanism to get the value back
    args = TTValue(mParent, mFocusDetectedReturn);
    mFocusDetectedReturn.set("baton", args);
    mFocusDetectedReturn.set("function", TTPtr(&DemoAppDataReturnValueCallback));

    // Setup the data attributes depending of its use inside the application
    mFocusDetectedReturn.set("type", "decimal");
    mFocusDetectedReturn.set("description", "Return eye focus");

    // Register the parameter data into gorgone-1 at an address
    args = TTValue("/tracking/detected/focus", mFocusDetectedReturn);
    out = mApplicationLocal.send("ObjectRegister", args);
    address = out[0];
    TTLogMessage("\n/tracking/detected/focus : effective registration address is %s \n", address.c_str());


    // Create a new array return for drawing shape
    mPupilDetectedReturn = TTObject("Data", "return");

    // Setup the callback mechanism to get the value back
    args = TTValue(mParent, mPupilDetectedReturn);
    mPupilDetectedReturn.set("baton", args);
    mPupilDetectedReturn.set("function", TTPtr(&DemoAppDataReturnValueCallback));

    // Setup the data attributes depending of its use inside the application
    mPupilDetectedReturn.set("type", "boolean");
    mPupilDetectedReturn.set("description", "Return eye focus");

    // Register the parameter data into gorgone-1 at an address
    args = TTValue("/tracking/detected/pupil", mPupilDetectedReturn);
    out = mApplicationLocal.send("ObjectRegister", args);
    address = out[0];
    TTLogMessage("\n/tracking/detected/pupil : effective registration address is %s \n", address.c_str());

    // Create a new brightness parameter
    mStaticShapeParameter = TTObject("Data", "parameter");

    // Setup the callback mechanism to get the value back
    args = TTValue(mParent, mStaticShapeParameter);
    mStaticShapeParameter.set("baton", args);
    mStaticShapeParameter.set("function", TTPtr(&DemoAppDataReturnValueCallback));

    // Setup the data attributes depending of its use inside the application
    mStaticShapeParameter.set("type", "integer");
    mStaticShapeParameter.set("description", "static shape selection");

    // Register the parameter data into gorgone-1 at an address
    args = TTValue("/drawing/static_shape", mStaticShapeParameter);
    out = mApplicationLocal.send("ObjectRegister", args);
    address = out[0];
    TTLogMessage("\n /drawing/static_shape: effective registration address is %s \n", address.c_str());


        // Create a new brightness parameter
    mShapeSizeParameter = TTObject("Data", "parameter");

    // Setup the callback mechanism to get the value back
    args = TTValue(mParent, mShapeSizeParameter);
    mShapeSizeParameter.set("baton", args);
    mShapeSizeParameter.set("function", TTPtr(&DemoAppDataReturnValueCallback));

    // Setup the data attributes depending of its use inside the application
    mShapeSizeParameter.set("type", "integer");
    mShapeSizeParameter.set("description", "static shape selection");

    // Register the parameter data into gorgone-1 at an address
    args = TTValue("/drawing/shape/size", mShapeSizeParameter);
    out = mApplicationLocal.send("ObjectRegister", args);
    address = out[0];
    TTLogMessage("\n /drawing/shape/size: effective registration address is %s \n", address.c_str());

}


TTErr
DemoAppDataReturnValueCallback(const TTValue& baton, const TTValue& value)
{
    gorgone*  gorgoneApp = (gorgone*)TTPtr(baton[0]);
    TTObject    anObject = baton[1];

  // Reteive which data has been updated
    if (anObject.instance() == gorgoneApp->jamoma.mTrackEnableParameter.instance()) {

        gorgoneApp->bTracking = value[0];
        if ( gorgoneApp->bTracking ){
            gorgoneApp->irisDetector.reset();
        }
        return kTTErrNone;
    }

      // Reteive which data has been updated
    if (anObject.instance() == gorgoneApp->jamoma.mMotionFlowEnableParameter.instance()) {

        gorgoneApp->bMotion = value[0];
        return kTTErrNone;
    }

    if (anObject.instance() == gorgoneApp->jamoma.mDrawingEnableParameter.instance()) {
        gorgoneApp->bDisplaying = value[0];
        if ( value[0] ) {
            TTValue a;
            gorgoneApp->jamoma.mTrackingLaserBrightness.get("value",a);
            gorgoneApp->setPwm(a);
        } else {
            gorgoneApp->setPwm(0);
        }
        return kTTErrNone;
    }

    if (anObject.instance() == gorgoneApp->jamoma.mComputeIrisCodeParameter.instance()) {
        gorgoneApp->bComputeCode = value[0];
        return kTTErrNone;
    }

    if (anObject.instance() == gorgoneApp->jamoma.mDrawingCoeffParameter.instance()) {
        ofLogVerbose("ofxJamoma") << "received coeff parameter" << endl;
        if (gorgoneApp->svgInterp.dirtyFlag) return kTTErrNone; // return if already dirty
        gorgoneApp->svgInterp.coeff.clear();

        for (int i = 0; i < value.size(); i++) {
            gorgoneApp->svgInterp.coeff.push_back(value[i]);
            ofLogVerbose("ofxJamoma") << i << " : " << static_cast<float> (value[i]) << endl;
        }
        gorgoneApp->svgInterp.dirtyFlag = true;

        return kTTErrNone;
    }

    if (anObject.instance() == gorgoneApp->jamoma.mStaticShapeParameter.instance()) {
        gorgoneApp->svgInterp.selectedId = value[0];
        return kTTErrNone;
    }


    if (anObject.instance() == gorgoneApp->jamoma.mShapeSizeParameter.instance()) {
        gorgoneApp->svgInterp.shapeSize = value[0];
        return kTTErrNone;
    }

#ifdef TARGET_RASPBERRY_PI
    if (anObject.instance() == gorgoneApp->jamoma.mTrackingLedBrightness.instance()) {
        gorgoneApp->vidGrabber.led.setBrightness(value[0]);
        return kTTErrNone;
    }

    if (anObject.instance() == gorgoneApp->jamoma.mTrackingLaserBrightness.instance()) {
        gorgoneApp->setPwm(value[0]);
        return kTTErrNone;
    }

    if (anObject.instance() == gorgoneApp->jamoma.mWhiteLedBrightness.instance()) {
	vector<unsigned char> b;
	for (int i(0); i<value.size() || i<4; i++){
	  b.push_back(value[i]);
	}
        gorgoneApp->vidGrabber.led.setWBrightness(b);
        return kTTErrNone;
    }

#endif

    return kTTErrGeneric;
}
