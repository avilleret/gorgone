#include "ofxJamoma.h"

void ofxJamoma::setup()
{
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
    mDataDecimalParameter = TTObject("Data", "parameter");

    // Setup the callback mechanism to get the value back
    args = TTValue(TTPtr(this), mDataDecimalParameter);
    mDataDecimalParameter.set("baton", args);
    mDataDecimalParameter.set("function", TTPtr(&DemoAppDataReturnValueCallback));

    // Setup the data attributes depending of its use inside the application
    mDataDecimalParameter.set("type", "decimal");
    mDataDecimalParameter.set("rangeBounds", TTValue(-1., 1.));
    mDataDecimalParameter.set("rangeClipmode", "both");
    mDataDecimalParameter.set("rampDrive", "System");
    mDataDecimalParameter.set("description", "this parameter is useful for demo purpose");
    mDataDecimalParameter.set("valueDefault", 0);
    mDataDecimalParameter.set("value", 0.9);

    // Register the parameter data into gorgone-1 at an address
    args = TTValue("/myParameterDecimal", mDataDecimalParameter);
    err = mApplicationLocal.send("ObjectRegister", args, out);

    if (err)
        TTLogError("Error : can't register data at /myParameterDecimal address \n");

    else {
        address = out[0];
        TTLogMessage("\n /myParameterDecimal : effective registration address is %s \n", address.c_str());
    }

}


TTErr
DemoAppDataReturnValueCallback(const TTValue& baton, const TTValue& value)
{
    ofxJamoma*    demoApp = (ofxJamoma*)TTPtr(baton[0]);
    TTObject    anObject = baton[1];

    std::cout << "received value size : " << value.size() << std::endl;

  // Reteive which data has been updated
    if (anObject.instance() == demoApp->mDataDecimalParameter.instance()) {

        // print the returned value
        TTLogMessage("/myParameterDecimal has been updated to %s \n", value.toString().data());
        // demoApp->param2 = value[0];
        return kTTErrNone;
    }

    if (anObject.instance() == demoApp->mDataStringParameter.instance()) {

        // print the returned value
        TTLogMessage("/myParameterString has been updated to %s \n", value.toString().data());
        return kTTErrNone;
    }

    if (anObject.instance() == demoApp->mDataBoolParameter.instance()) {

        // print the returned value
        TTLogMessage("/myParameterBool has been updated to %s \n", value.toString().data());
        return kTTErrNone;
    }

    if (anObject.instance() == demoApp->mDataMessage.instance()) {

        // print the returned value
        TTLogMessage("/myMessage has been updated to %s \n", value.toString().data());
        return kTTErrNone;
    }

    if (anObject.instance() == demoApp->mDataReturn.instance()) {

        // print the returned value
        TTLogMessage("/myReturn has been updated to %s \n", value.toString().data());
        return kTTErrNone;
    }

    return kTTErrGeneric;
}
