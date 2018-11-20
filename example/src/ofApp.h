#pragma once

#include "ofMain.h"
#include "ofxCornerPin.h"
#include "ofxCornerPinController.h"
#include "ofxCornerPin9.h"
#include "ofxCornerPinController9.h"


class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
    ofxCornerPin cornerPin;
    ofxCornerPinController controller;
    ofImage img;
    ofxCornerPin9 cornerPin9;
    ofxCornerPinController9 controller9;
    
    bool bGuide=false;
    
};
