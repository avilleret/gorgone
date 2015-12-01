#include "svgInterpolation.h"

//--------------------------------------------------------------
void svgInterpolation::setup(){

  selectedId = -1;

  ofDirectory dir;

  shapeSize = 500;

  ofLogNotice("svgInterpolation") << "load SVG from formes_interpol" << endl;
  dir.listDir("formes_interpol/");
  dir.sort(); // in linux the file system doesn't return file lists ordered in alphabetical order
  ofLogNotice("svgInterpolation") << "found " << (int)dir.size() << " images to load." << endl;
  lineSize = 10000;

  for(int i = 0; i < (int)dir.size(); i++){
    // if ( i == 0 ) cout << "load : " << dir.getPath(i) << endl;
    ofxSVG svg;
    svg.load(dir.getPath(i));
    ofPolyline myLine;
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

          myLine.addVertex(pt);
        }
      }
  	}
    myLine.close();
    lines.push_back(myLine);
    ofLogVerbose("svgInterpolation") << "min : " << ptMin.x << " " << ptMin.y << endl;
    ofLogVerbose("svgInterpolation") << "max : " << ptMax.x << " " << ptMax.y << endl;
  }

  ofLogNotice("svgInterpolation") << "load SVG from formes_statiques" << endl;
  dir.listDir("formes_statiques/");
  dir.sort(); // in linux the file system doesn't return file lists ordered in alphabetical order

  for(int i = 0; i < (int)dir.size(); i++){
    ofxSVG svg;
    svg.load(dir.getPath(i));
    ofLogNotice("svgInterpolation") << "load : " << dir.getPath(i) << "with " << svg.getNumPath() << " paths" << endl;
    ofPolyline myLine;
    ofVec2f ptMin = ofVec2f(1000.,1000.), ptMax = ofVec2f(-1000.,-1000.);

    for (int i = 0; i < svg.getNumPath(); i++){
      ofPath p = svg.getPathAt(i);
      // svg defaults to non zero winding which doesn't look so good as contours
      p.setPolyWindingMode(OF_POLY_WINDING_ODD);
      vector<ofPolyline>& lines = const_cast<vector<ofPolyline>&>(p.getOutline());
      ofLogNotice("svgInterpolation") << "path " << i << " has " << lines.size() << " points " << endl;
      for(int k=0;k<(int)lines.size();k++){
        ofPolyline line=lines[k];
        for(int n=0;n<line.size();n++){

          ofVec3f pt = line[n];
          ptMin.x = std::min(pt.x, ptMin.x);
          ptMin.y = std::min(pt.y, ptMin.y);
          ptMax.x = std::max(pt.x, ptMax.x);
          ptMax.y = std::max(pt.y, ptMax.y);

          myLine.addVertex(pt);
	        ofLogVerbose("svgInterpolation") << n << " : " << pt.x << ";" << pt.y << endl;
        }
      }
      ofLogVerbose("svgInterpolation") << "normalize shape" << endl;
      ofVec2f offset, amplitude;
      float scale;
      offset = (ptMin + ptMax) /2.;
      amplitude = (ptMax - ptMin)/2;
      scale = max(amplitude.x,amplitude.y);
      for (auto & pt : myLine){
      	pt-=offset;
      	pt/=scale;
      	ofLogVerbose("svgInterpolation") << pt.x << ";" << pt.y << endl;
      }
    myLine.close();
    static_lines.push_back(myLine);
    }
  }

  ofLogNotice("svgInterpolation") << "lineSize : " << lineSize << endl;
}


//--------------------------------------------------------------
bool svgInterpolation::updateBool(){
  return multiInterpolation() || draw_static();
}

//--------------------------------------------------------------
void svgInterpolation::draw(){

	ofDrawBitmapString(ofToString(ofGetFrameRate()),20,20);
	ofPushMatrix();
  ofTranslate(ofGetWidth() / 2., ofGetHeight() / 2.);
	ofScale(ofGetHeight() / 3., ofGetHeight() / 3., 1.);
	ofNoFill();

  ofBeginShape();
  for (int j = 0; j < interpolatedLine.size(); j++){
    ofVertex(interpolatedLine[j]);
  }
  if ( interpolatedLine.size() ) ofVertex(interpolatedLine[0]);
  ofEndShape();

	ofPopMatrix();
}

bool svgInterpolation::multiInterpolation(){

  if ( !dirtyFlag ) return false;

  interpolatedLine.clear();

  float sum(0.);

  for (float f : coeff)
    sum += f;

  // cout << "sum : " << sum << endl;

  // cout << "interpolatedLine : " << endl;
  ofLogNotice("svgInterpolation") << "lineSize : " << lineSize << endl;
  ofLogNotice("svgInterpolation") << "nombre de formes chargées : " << lines.size() << endl;
  ofLogNotice("svgInterpolation") << "taille de coeff : " << coeff.size() << endl;

  for (int i = 0; i < lineSize; i++){
    ofVec3f pt;
    for (int j = 0; j < min(lines.size(), coeff.size()); j++){
      pt += coeff[j] * lines[j][i]; // [0] assumes that there is only one line on each ofPolyLine
    }
    interpolatedLine.addVertex(pt);
  }

  ofVec3f ptMin(999999. ,999999.);
  ofVec3f ptMax(-999999.,-999999.);
  for ( ofVec3f pt : interpolatedLine ){
    ptMin.x = min(pt.x,ptMin.x);
    ptMin.y = min(pt.y,ptMin.y);
    ptMax.x = max(pt.x,ptMax.x);
    ptMax.y = max(pt.y,ptMax.y);
  }
  ofLogVerbose("svgInterpolation") << "ptMin : " << ptMin.x << " \t " << ptMin.y << endl;
  ofLogVerbose("svgInterpolation") << "ptMax : " << ptMax.x << " \t " << ptMax.y << endl;

  ofVec3f offset, diff;
  float scale;
  offset = (ptMax + ptMin)/2.;
  diff = ptMax - ptMin;
  scale = max(diff.x,diff.y) / 2.;

  ofLogVerbose("svgInterpolation") << "scale : " << scale << endl;
  ofLogVerbose("svgInterpolation") << "offset : " << offset << endl;
  ofLogVerbose("svgInterpolation") << "normalized line : " << endl;
  int i(0);
  for ( ofVec3f& pt : interpolatedLine ){
    pt -= offset;
    pt /= scale;
    ofLogVerbose("svgInterpolation") << i++ << " : " << pt.x << " \t " << pt.y << endl;
  }

  interpolatedLine = interpolatedLine.getResampledByCount(shapeSize);
  ofLogVerbose("svgInterpolation") << "interpolatedLine.size() : " << interpolatedLine.size() << endl;

  dirtyFlag=false;

  return true;
}

bool svgInterpolation::draw_static(){
  if ( selectedId < 0 ) return false;
  if ( selectedId > (static_lines.size() - 1)) return false;

  interpolatedLine.clear();
  interpolatedLine = static_lines[selectedId].getResampledByCount(shapeSize);

  selectedId = -1;
  return true;
}
