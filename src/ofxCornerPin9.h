//
//  ofxCornerPin9.h
//  PanX2018movieEmitter
//
//  Created by 田中喜作 on 2018/10/20.
//

#ifndef ofxCornerPin9_h
#define ofxCornerPin9_h

#include "ofMain.h"
#include "ofEvents.h"

class ofxCornerPin9 {
    vector<ofPoint> vertices=vector<ofPoint>(9);
    vector<ofPoint> points;
    ofPoint center;
    float v1,v2;
    ofMesh mesh;
    int u,v;
    
public:
    void setup(int w,int h,int _u,int _v);
    void setMesh();
    void setCorners(vector<ofPoint> _corners);
    void setV1(float _v1);
    void setV2(float _v2);
    vector<ofPoint> getCorners();
    void draw();
    void drawGuide();
    void mouseMoved(ofMouseEventArgs &mouse);
};

#endif /* ofxCornerPin9_h */
