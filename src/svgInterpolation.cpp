#include "svgInterpolation.h"

//--------------------------------------------------------------
void svgInterpolation::setup(){

  selectedId = -1;

  ofDirectory dir;
  dir.listDir("formes_interpol/");
  dir.sort(); // in linux the file system doesn't return file lists ordered in alphabetical order

  lineSize = 10000;

  for(int i = 0; i < (int)dir.size(); i++){
    // if ( i == 0 ) cout << "load : " << dir.getPath(i) << endl;
    ofxSVG svg;
    svg.load(dir.getPath(i));
    vector<ofVec3f> myLine;
    ofVec2f ptMin = ofVec2f(1000.,1000.), ptMax = ofVec2f(-1000.,-1000.);

  	for (int j = 0; j < svg.getNumPath(); j++){
  		ofPath p = svg.getPathAt(j);
  		// svg defaults to non zero winding which doesn't look so good as contours
  		p.setPolyWindingMode(OF_POLY_WINDING_ODD);
  		vector<ofPolyline>& lines = const_cast<vector<ofPolyline>&>(p.getOutline());
  		for(int k=0;k<(int)lines.size();k++){
        lineSize = min(lineSize, (int) lines[k].size());
        ofPolyline line=lines[k];
        for(int n=0;n<line.size();n++){

          ofVec3f pt = line[n];
          pt/=40;
          pt-=1.;
          ptMin.x = std::min(pt.x, ptMin.x);
          ptMin.y = std::min(pt.y, ptMin.y);
          ptMax.x = std::max(pt.x, ptMax.x);
          ptMax.y = std::max(pt.y, ptMax.y);

          myLine.push_back(pt);

        }
      }
  	}
    // cout << "min : " << ptMin.x << " " << ptMin.y << endl;
    // cout << "max : " << ptMax.x << " " << ptMax.y << endl;
    lines.push_back(myLine);
  }

  dir.listDir("formes_statiques /");
  dir.sort(); // in linux the file system doesn't return file lists ordered in alphabetical order

  for(int i = 0; i < (int)dir.size(); i++){
    ofxSVG svg;
    svg.load(dir.getPath(i));
    vector<ofVec3f> myLine;
    ofVec2f ptMin = ofVec2f(1000.,1000.), ptMax = ofVec2f(-1000.,-1000.);

    for (int i = 0; i < svg.getNumPath(); i++){
      ofPath p = svg.getPathAt(i);
      // svg defaults to non zero winding which doesn't look so good as contours
      p.setPolyWindingMode(OF_POLY_WINDING_ODD);
      vector<ofPolyline>& lines = const_cast<vector<ofPolyline>&>(p.getOutline());

      for(int k=0;k<(int)lines.size();k++){
        ofPolyline line=lines[k];
        for(int n=0;n<line.size();n++){

          ofVec3f pt = line[n];
          pt/=40;
          pt-=1.;
          ptMin.x = std::min(pt.x, ptMin.x);
          ptMin.y = std::min(pt.y, ptMin.y);
          ptMax.x = std::max(pt.x, ptMax.x);
          ptMax.y = std::max(pt.y, ptMax.y);

          myLine.push_back(pt);

        }
      }
    static_lines.push_back(myLine);
    }
  }
}


//--------------------------------------------------------------
void svgInterpolation::update(){
  multiInterpolation();
  draw_static();
}

//--------------------------------------------------------------
void svgInterpolation::draw(){

	ofDrawBitmapString(ofToString(ofGetFrameRate()),20,20);
	ofPushMatrix();
  ofTranslate(ofGetWidth() / 2., ofGetHeight() / 2.);
	ofScale(20, 20, 1.);
	ofNoFill();

  ofBeginShape();
  for (int j = 0; j < interpolatedLine.size(); j++){
    ofVertex(interpolatedLine[j]);
  }
  if ( interpolatedLine.size() ) ofVertex(interpolatedLine[0]);
  ofEndShape();

	ofPopMatrix();
}

void svgInterpolation::multiInterpolation(){

  if ( !dirtyFlag ) return;

  dirtyFlag=false;

  interpolatedLine.clear();

  float sum(0.);

  for (float f : coeff)
    sum += f;

  // cout << "sum : " << sum << endl;

  // cout << "interpolatedLine : " << endl;

  for (int i = 0; i < lineSize; i++){
    ofVec3f pt;
    for (int j = 0; j < min(lines.size(), coeff.size()); j++){
      pt += coeff[j] * lines[j][i]; // [0] assumes that there is only one line on each ofPolyLine
    }
    interpolatedLine.push_back(pt);
  }

  ofVec3f ptMin(999999. ,999999.);
  ofVec3f ptMax(-999999.,-999999.);
  for ( ofVec3f pt : interpolatedLine ){
    ptMin.x = min(pt.x,ptMin.x);
    ptMin.y = min(pt.y,ptMin.y);
    ptMax.x = max(pt.x,ptMax.x);
    ptMax.y = max(pt.y,ptMax.y);
  }
  // cout << "ptMin : " << ptMin.x << " \t " << ptMin.y << endl;
  // cout << "ptMax : " << ptMax.x << " \t " << ptMax.y << endl;

  ofVec3f offset, diff;
  float scale;
  offset = (ptMax + ptMin)/2.;
  diff = ptMax - ptMin;
  scale = max(diff.x,diff.y) / 2.;

  // cout << "scale : " << scale << endl;
  // cout << "offset : " << offset << endl;
  cout << "normalized line : " << endl;
  int i(0);
  for ( ofVec3f& pt : interpolatedLine ){
    pt -= offset;
    pt /= scale;
    cout << i++ << " : " << pt.x << " \t " << pt.y << endl;
  }

}

void svgInterpolation::draw_static(){
  if ( selectedId < 0 ) return;
  if ( selectedId > (static_lines.size() - 1)) return;

  interpolatedLine.clear();
  interpolatedLine = static_lines[selectedId];
  selectedId = -1;
}
