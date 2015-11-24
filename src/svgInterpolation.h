#pragma once

#include "ofMain.h"
#include "ofxSvg.h"

class svgInterpolation : public ofBaseApp {

public:
    void setup();
    void update();
    void draw();
    void multiInterpolation();
    void draw_static();

    vector<ofxSVG> svgs;
    float step;
    vector<vector<ofVec3f>> lines, static_lines;
    vector<float> coeff; // interpolation coefficient
    vector<ofVec3f> interpolatedLine; // forme interpolée
    int lineSize, selectedId;

    bool dirtyFlag, dirtyStaticFlag;
private:
   ofxPanel gui;
   ofParameter<float> scaleParam, offsetParam;
};
