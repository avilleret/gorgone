#pragma once

#include "ofMain.h"
#include "ofxSvg.h"

class svgInterpolation : public ofBaseApp {

public:
    void setup();
    bool updateBool();
    void draw();
    bool multiInterpolation();
    bool draw_static();

    vector<ofxSVG> svgs;
    float step;
    vector<ofPolyline> lines, static_lines;
    vector<float> coeff; // interpolation coefficient
    ofPolyline interpolatedLine; // forme interpolée
    int lineSize, selectedId;

    bool dirtyFlag, dirtyStaticFlag;
private:
   ofxPanel gui;
   ofParameter<float> scaleParam, offsetParam;
};
