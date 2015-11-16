#include "svgInterpolation.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetVerticalSync(true);

	ofBackground(0);
	ofSetColor(255);

  dir.listDir("");
  dir.sort(); // in linux the file system doesn't return file lists ordered in alphabetical order

  //allocate the vector to have as many ofImages as files
  if( dir.size() ){
    svgs.assign(dir.size(), ofxSVG());
  }

  lineSize = 10000;

  for(int i = 0; i < (int)dir.size(); i++){
    svgs[i].load(dir.getPath(i));
    cout << "load : " << dir.getPath(i) << endl;
  	ofPolyline centroidLine;
    ofxSVG svg = svgs[i];
    cout << "with " << svg.getNumPath() << " paths" << endl;
    vector<ofPolyline> outlines;
  	for (int j = 0; j < svg.getNumPath(); j++){
  		ofPath p = svg.getPathAt(j);
  		// svg defaults to non zero winding which doesn't look so good as contours
  		p.setPolyWindingMode(OF_POLY_WINDING_ODD);
  		vector<ofPolyline>& lines = const_cast<vector<ofPolyline>&>(p.getOutline());
      cout << "number of line in the path : " << lines.size() << endl;
  		for(int k=0;k<(int)lines.size();k++){
        cout << "number of point in this line : " << lines[k].size() << endl;
        lineSize = min(lineSize, (int) lines[k].size());
  			outlines.push_back(lines[k]);
        centroidLine.addVertex(lines[k].getCentroid2D());
        ofPolyline line=lines[k];
        for(int n=0;n<line.size();n++){
          ofVec3f pt = line[n];
          cout << " point " << n << " : " << pt.x << ";" << pt.y << endl;
        }
      }
  	}
    outliness.push_back(outlines);

  	ofPoint center = centroidLine.getCentroid2D();
    centers.push_back(center);
  	cout << "center " << center.x << " ; " << center.y << endl;
  }
}


//--------------------------------------------------------------
void ofApp::update(){
	step += 0.001;
	if (step > 1) {
		step -= 1;
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofDrawBitmapString(ofToString(ofGetFrameRate()),20,20);
	ofPushMatrix();
	ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
	// ofRotate(mouseX);
	// float scale = ofMap(mouseY, 0, ofGetHeight(), .5, 10);
	// ofScale(4., 4., 4.);
  ofPoint center = centers[0];
	ofTranslate(-center.x, -center.y);
	ofNoFill();

  double index = outliness.size() * step;
  vector<ofPolyline> outlinesA = outliness[(int) index];
  vector<ofPolyline> outlinesB = outliness[(int) fmod((index+1),outliness.size())];

  for (int i = 0; i < min( (int)outlinesA.size(), (int)outlinesB.size()); i++){
    ofPolyline & lineA = outlinesA[i];
    ofPolyline & lineB = outlinesB[i];

    ofBeginShape();
    for (int j = 0; j < lineSize; j++){
      ofVec3f pt = lineA[j].getInterpolated(lineB[j], fmod(index,1.));
      ofVertex(pt);
    }
    ofVec3f pt = lineA[0].getInterpolated(lineB[0], fmod(index,1.));
    ofVertex(pt);
    ofEndShape();
  }

	ofPopMatrix();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}
