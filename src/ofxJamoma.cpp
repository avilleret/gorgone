#include "ofxJamoma.h"
#include "gorgone.h"

void ofxJamoma::setup(void* parent)
{
  mParent = TTPtr(parent);
  mAppLocalName = "gorgone-1";
  mAppRemoteName = "master";
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


    // Get registered application names
    mApplicationManager.get("applicationNames", out);
    for (TTElementIter it = out.begin() ; it != out.end() ; it++) {
        TTSymbol name = TTElement(*it);
        TTLogMessage("%s application is well registered into the application manager \n", name.c_str());
    }


    TTLogMessage("\n*** Enable Minuit communication ***\n");
    ////////////////////////////////////////////////////////////////////////

    // Create a Minuit protocol unit
    err = mApplicationManager.send("ProtocolInstantiate", "Minuit", out);

    if (err) {
        TTLogError("Error : can't create Minuit protocol unit \n");
        return;
    }
    else
        mProtocolMinuit = out[0];

    // Get Minuit Protocol attribute names and types
    mProtocolMinuit.get("parameterNames", out);
    for (TTElementIter it = out.begin() ; it != out.end() ; it++) {
        TTSymbol name = TTElement(*it);
        TTSymbol type = mProtocolMinuit.attributeType(name);
        TTLogMessage("Minuit %s parameter is a %s \n", name.c_str(), type.c_str());
    }

    // Register mymyRemoteAppApp and myRemoteApp to the Minuit protocol
    mProtocolMinuit.send("ApplicationRegister", mAppLocalName.c_str(), out);
    mProtocolMinuit.send("ApplicationRegister", mAppRemoteName.c_str(), out);

    // Select gorgone-1 to set its protocol parameters
    mProtocolMinuit.send("ApplicationSelect", mAppLocalName.c_str(), out);
    mProtocolMinuit.set("port", 9998);
    mProtocolMinuit.set("ip", "127.0.0.1");

    // Select myRemoteApp to set its protocol parameters
    mProtocolMinuit.send("ApplicationSelect", mAppRemoteName.c_str(), out);
    mProtocolMinuit.set("port", 13579);
    mProtocolMinuit.set("ip", "192.168.2.1");

    // Get Minuit parameters for each registered application
    mProtocolMinuit.get("applicationNames", out);
    for (TTElementIter it = out.begin() ; it != out.end() ; it++) {
        TTSymbol name = TTElement(*it);

        mProtocolMinuit.send("ApplicationSelect", name, out);
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
    mApplicationManager.get("protocolNames", out);
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
    err = mApplicationLocal.send("ObjectRegister", args, out);

    if (err)
        TTLogError("Error : can't register data at /tracking/enable address \n");

    else {
        address = out[0];
        TTLogMessage("\n /tracking/enable : effective registration address is %s \n", address.c_str());
    }

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
    err = mApplicationLocal.send("ObjectRegister", args, out);

    if (err)
        TTLogError("Error : can't register data at /drawing/enable address \n");

    else {
        address = out[0];
        TTLogMessage("\n /drawing/enable : effective registration address is %s \n", address.c_str());
    }

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
    err = mApplicationLocal.send("ObjectRegister", args, out);

    if (err)
        TTLogError("Error : can't register data at /tracking/computecode address \n");

    else {
        address = out[0];
        TTLogMessage("\n /tracking/computecode : effective registration address is %s \n", address.c_str());
    }

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
    err = mApplicationLocal.send("ObjectRegister", args, out);

    if (err)
        TTLogError("Error : can't register data at /drawing/coeff address \n");

    else {
        address = out[0];
        TTLogMessage("\n /drawing/coeff : effective registration address is %s \n", address.c_str());
    }


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
    err = mApplicationLocal.send("ObjectRegister", args, out);

    if (err)
        TTLogError("Error : can't register data at /tracking/iriscode address \n");

    else {
        address = out[0];
        TTLogMessage("\n /tracking/iriscode : effective registration address is %s \n", address.c_str());
    }

    // Create a new brightness parameter
    mTrackingLedBrightness = TTObject("Data", "parameter");

    // Setup the callback mechanism to get the value back
    args = TTValue(mParent, mTrackingLedBrightness);
    mTrackingLedBrightness.set("baton", args);
    mTrackingLedBrightness.set("function", TTPtr(&DemoAppDataReturnValueCallback));

    // Setup the data attributes depending of its use inside the application
    mTrackingLedBrightness.set("type", "integer");
    mTrackingLedBrightness.set("description", "iris code");
    mTrackingLedBrightness.set("rangeBounds", TTValue(0, 1023));
    mTrackingLedBrightness.set("rangeClipmode", "both");

    // Register the parameter data into gorgone-1 at an address
    args = TTValue("/tracking/ledbrightness", mTrackingLedBrightness);
    err = mApplicationLocal.send("ObjectRegister", args, out);

    if (err)
        TTLogError("Error : can't register data at /tracking/ledbrightness address \n");

    else {
        address = out[0];
        TTLogMessage("\n /tracking/ledbrightness : effective registration address is %s \n", address.c_str());
    }
}


TTErr
DemoAppDataReturnValueCallback(const TTValue& baton, const TTValue& value)
{
    gorgone*  gorgoneApp = (gorgone*)TTPtr(baton[0]);
    TTObject    anObject = baton[1];

    std::cout << "received value size : " << value.size() << std::endl;

  // Reteive which data has been updated
    if (anObject.instance() == gorgoneApp->jamoma.mTrackEnableParameter.instance()) {

        gorgoneApp->bTracking = value[0];
        return kTTErrNone;
    }

    if (anObject.instance() == gorgoneApp->jamoma.mDrawingEnableParameter.instance()) {
        gorgoneApp->bDisplaying = value[0];
        return kTTErrNone;
    }

    if (anObject.instance() == gorgoneApp->jamoma.mComputeIrisCodeParameter.instance()) {
        gorgoneApp->bComputeCode = value[0];
        return kTTErrNone;
    }

    if (anObject.instance() == gorgoneApp->jamoma.mDrawingCoeffParameter.instance()) {
        gorgoneApp->svgInterp.coeff.clear();
        for (int i = 0; i < value.size(); i++)
            gorgoneApp->svgInterp.coeff.push_back(value[i]);
        gorgoneApp->svgInterp.multiInterpolation();
        return kTTErrNone;
    }

#ifdef TARGET_RASPBERRY_PI
    if (anObject.instance() == gorgoneApp->jamoma.mTrackingLedBrightness.instance()) {
        gorgoneApp->vidGrabber.led.setBrightness(value[0]);
        return kTTErrNone;
    }
#endif

    return kTTErrGeneric;
}
