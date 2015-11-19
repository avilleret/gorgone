#include "svgInterpolation.h"

//--------------------------------------------------------------
void svgInterpolation::setup(){
	ofSetVerticalSync(true);

	ofBackground(0);
	ofSetColor(255);

  dir.listDir("formes/");
  dir.sort(); // in linux the file system doesn't return file lists ordered in alphabetical order

  //allocate the vector to have as many ofImages as files
  if( dir.size() ){
    svgs.assign(dir.size(), ofxSVG());
  }

  lineSize = 10000;

  for(int i = 0; i < (int)dir.size(); i++){
    svgs[i].load(dir.getPath(i));
  	ofPolyline centroidLine;
    ofxSVG svg = svgs[i];
    vector<ofPolyline> outlines;
  	for (int j = 0; j < svg.getNumPath(); j++){
  		ofPath p = svg.getPathAt(j);
  		// svg defaults to non zero winding which doesn't look so good as contours
  		p.setPolyWindingMode(OF_POLY_WINDING_ODD);
  		vector<ofPolyline>& lines = const_cast<vector<ofPolyline>&>(p.getOutline());
  		for(int k=0;k<(int)lines.size();k++){
        lineSize = min(lineSize, (int) lines[k].size());
  			outlines.push_back(lines[k]);
        centroidLine.addVertex(lines[k].getCentroid2D());
        ofPolyline line=lines[k];
        for(int n=0;n<line.size();n++){
          ofVec3f pt = line[n];
        }
      }
  	}
    outliness.push_back(outlines);

  	ofPoint center = centroidLine.getCentroid2D();
    centers.push_back(center);
  }
}


//--------------------------------------------------------------
void svgInterpolation::update(){
	step += 0.001;
	if (step > 1) {
		step -= 1;
	}
}

//--------------------------------------------------------------
void svgInterpolation::draw(){
	ofDrawBitmapString(ofToString(ofGetFrameRate()),20,20);
	ofPushMatrix();
	// ofTranslate(ofGetWidth() / 4, ofGetHeight() / 4);
	// ofRotate(mouseX);
	// float scale = ofMap(mouseY, 0, ofGetHeight(), .5, 10);
	ofScale(0.25, 0.25, 0.25);
  /// ofPoint center = centers[0];
	// ofTranslate(-ofGetWidth(), -ofGetHeight());
	ofNoFill();

  double index = outliness.size() * step;
  vector<ofPolyline> outlinesA = outliness[(int) index];
  vector<ofPolyline> outlinesB = outliness[(int) fmod((index+1),outliness.size())];

  ofBeginShape();
  for (int j = 0; j < interpolatedLine.size(); j++){
    ofVertex(interpolatedLine[j]);
  }
  if ( interpolatedLine.size() ) ofVertex(interpolatedLine[0]);
  ofEndShape();

	ofPopMatrix();
}

void svgInterpolation::multiInterpolation(){

  cout << "compute shape interpolation" << endl;

  interpolatedLine.clear();

  for (int i = 0; i < lineSize; i++){
    ofVec3f pt;
    for (int j = 0; j < min(outliness.size(), coeff.size()); j++){
      pt += coeff[j] * outliness[j][0][i]; // [0] assumes that there is only one line on each ofPolyLine
    }
    interpolatedLine.push_back(pt);
  }
}
