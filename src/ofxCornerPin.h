//
//  ofxCornerPin.h
//  example
//
//  Created by 田中喜作 on 2018/10/01.
//

#ifndef ofxCornerPin_h
#define ofxCornerPin_h

#include "ofMain.h"
#include "ofEvents.h"

class ofxCornerPin {
    ofPoint lt;
    ofPoint rt;
    ofPoint rb;
    ofPoint lb;
    
    ofPoint center;
    float v1,v2;
    ofMesh mesh;
    int u,v;
    
public:
    void setup(int w,int h,int _u,int _v);
    void setMesh();
    void setLeftTop(ofPoint _lt);
    void setRightTop(ofPoint _rt);
    void setRightBottom(ofPoint _rb);
    void setLeftBottom(ofPoint _lb);
    void setCorners(vector<ofPoint> _corners);
    void setV1(float _v1);
    void setV2(float _v2);
    vector<ofPoint> getCorners();
    void draw();
    void drawGuide();
    void mouseMoved(ofMouseEventArgs &mouse);
};

#endif /* ofxCornerPin_h */
