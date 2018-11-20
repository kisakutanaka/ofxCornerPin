//
//  ofxCornerPinController.h
//  example
//
//  Created by 田中喜作 on 2018/10/06.
//

#ifndef ofxCornerPinController_h
#define ofxCornerPinController_h

#include "ofxCornerPin.h"
#include "ofEvent.h"

class ofxCornerPinController {
    ofxCornerPin * pinData;
    ofPoint retainedPoint;
    ofRectangle selectRect;
    ofRectangle editerArea;
    bool bEnable=false;
    bool bDrawRect=false;
    bool bDrag=false;
    bool shiftOn=false;
    bool bActive[4];
    ofVec2f sizeRate={1,1};
    
public:
    ofxCornerPinController();
    ~ofxCornerPinController();
    void add(ofxCornerPin * _pinData);
    void enable();
    void disable();
    void setEnable(bool _bEnable);
    void setEditerArea(ofVec2f _displaySize,ofRectangle _editerArea);
    void draw();
    void mousePressed(ofMouseEventArgs &arg);
    void mouseDragged(ofMouseEventArgs &arg);
    void mouseReleased(ofMouseEventArgs &arg);
    void keyPressed(ofKeyEventArgs &arg);
    void keyReleased(ofKeyEventArgs &arg);
    bool hit(ofPoint _p);
    void deselect();
    void save(string filename);
    void load(string filename);
};

#endif /* ofxCornerPinController_h */
