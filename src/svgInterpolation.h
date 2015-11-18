#pragma once

#include "ofMain.h"
#include "ofxSvg.h"

class svgInterpolation : public ofBaseApp {

public:
    void setup();
    void update();
    void draw();
    void multiInterpolation();

    vector<ofxSVG> svgs;
    float step;
    vector<ofPoint> centers;
    vector<vector<ofPolyline>> outliness;
    vector<float> coeff; // interpolation coefficient
    vector<ofVec3f> interpolatedLine; // forme interpolée
    int lineSize;

    ofDirectory dir;
};
