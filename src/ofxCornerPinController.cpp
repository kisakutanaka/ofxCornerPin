//
//  ofxCornerPinController.cpp
//  example
//
//  Created by 田中喜作 on 2018/10/06.
//

#include "ofxCornerPinController.h"
#include "ofxJsonUtils.h"

ofxCornerPinController::ofxCornerPinController(){
    this->deselect();
    editerArea={0,0,(float)ofGetWidth(),(float)ofGetHeight()};
    setEditerArea(ofGetWindowSize(), editerArea);
}

ofxCornerPinController::~ofxCornerPinController(){
    
}

void ofxCornerPinController::add(ofxCornerPin * _pinData){
    pinData=_pinData;
}

void ofxCornerPinController::enable(){
    if(!bEnable){
        ofAddListener(ofEvents().mousePressed,this,&ofxCornerPinController::mousePressed);
        ofAddListener(ofEvents().mouseDragged,this,&ofxCornerPinController::mouseDragged);
        ofAddListener(ofEvents().mouseReleased,this,&ofxCornerPinController::mouseReleased);
        ofAddListener(ofEvents().keyPressed, this, &ofxCornerPinController::keyPressed);
        ofAddListener(ofEvents().keyReleased, this, &ofxCornerPinController::keyReleased);
        bEnable=true;
    }
}

void ofxCornerPinController::disable(){
    if(bEnable){
        ofRemoveListener(ofEvents().mousePressed,this,&ofxCornerPinController::mousePressed);
        ofRemoveListener(ofEvents().mouseDragged,this,&ofxCornerPinController::mouseDragged);
        ofRemoveListener(ofEvents().mouseReleased,this,&ofxCornerPinController::mouseReleased);
        ofRemoveListener(ofEvents().keyPressed, this, &ofxCornerPinController::keyPressed);
        ofRemoveListener(ofEvents().keyReleased, this, &ofxCornerPinController::keyReleased);
        bEnable=false;
    }
}

void ofxCornerPinController::setEnable(bool _bEnable){
    if(_bEnable){
        this->enable();
    }
    else{
        this->disable();
    }
}

void ofxCornerPinController::setEditerArea(ofVec2f _displaySize, ofRectangle _editerArea){
    editerArea=_editerArea;
    sizeRate=_displaySize/ofVec2f(editerArea.width,editerArea.height);
    
}

void ofxCornerPinController::draw(){
    vector<ofPoint> p = pinData->getCorners();
    ofPushMatrix();
    ofTranslate(editerArea.position);
    ofScale(1/sizeRate.x,1/sizeRate.y);
    ofPushStyle();
    for(int i=0;i<4;i++){
        if(bActive[i]){
            ofSetColor(255,0,0);
        }
        else{
            ofSetColor(0, 255, 0);
        }
        ofDrawCircle(p[i],10*sizeRate.x);
    }
    if(bDrawRect){
        ofSetColor(127, 127, 127,50);
        ofDrawRectangle(selectRect);
    }
    ofPopStyle();
    ofPopMatrix();
}

void ofxCornerPinController::mousePressed(ofMouseEventArgs &arg){
    arg-=editerArea.position;
    arg*=sizeRate;
    retainedPoint=arg;
    if(this->hit(arg)) {
        bDrag=true;
    }
    else {
        if(!shiftOn){
            this->deselect();
        }
        bDrawRect=true;
        selectRect.position=retainedPoint;
        selectRect.setSize(arg.x-retainedPoint.x, arg.y-retainedPoint.y);
    }
}

void ofxCornerPinController::mouseDragged(ofMouseEventArgs &arg){
    arg-=editerArea.position;
    arg*=sizeRate;
    if(bDrag){
        ofPoint move=arg-retainedPoint;
        vector<ofPoint> p = pinData->getCorners();
        for(int i=0;i<4;i++){
            if(bActive[i]){
                p[i]+=move;
            }
        }
        pinData->setCorners(p);
        retainedPoint=arg;
    }
    else if(bDrawRect){
        selectRect.setSize(arg.x-retainedPoint.x, arg.y-retainedPoint.y);
    }
}

void ofxCornerPinController::mouseReleased(ofMouseEventArgs &arg){
    arg-=editerArea.position;
    arg*=sizeRate;
    if(bDrawRect){
        vector<ofPoint> p = pinData->getCorners();
        selectRect.scale(sizeRate);
        for(int i=0;i<4;i++){
            if(selectRect.inside(p[i])){
                bActive[i]=true;
            }
        }
    }
    bDrag=false;
    bDrawRect=false;
}

void ofxCornerPinController::keyPressed(ofKeyEventArgs &arg){
    if(arg.key==OF_KEY_SHIFT){
        shiftOn=true;
    }
    vector<ofPoint> p = pinData->getCorners();
    for(int i=0;i<4;i++){
        if(bActive[i]){
            if(arg.key==OF_KEY_UP){
                p[i].y--;
            }
            else if (arg.key==OF_KEY_DOWN){
                p[i].y++;
            }
            else if (arg.key==OF_KEY_LEFT){
                p[i].x--;
            }
            else if (arg.key==OF_KEY_RIGHT){
                p[i].x++;
            }
        }
    }
    pinData->setCorners(p);
}

void ofxCornerPinController::keyReleased(ofKeyEventArgs &arg){
    if(arg.key==OF_KEY_SHIFT){
        shiftOn=false;
    }
}

bool ofxCornerPinController::hit(ofPoint _p){
    vector<ofPoint> p = pinData->getCorners();
    for(int i=0;i<4;i++){
        if(p[i].x-10*sizeRate.x<_p.x&&p[i].x+10*sizeRate.x>_p.x&&p[i].y-10*sizeRate.y<_p.y&&p[i].y+10*sizeRate.y>_p.y){
            if(!bActive[i]){
                if(!shiftOn){
                    this->deselect();
                }
                bActive[i]=true;
            }
            return true;
        }
    }
    return false;
}

void ofxCornerPinController::deselect(){
    for(int i=0;i<4;i++){
        bActive[i]=false;
    }
}

void ofxCornerPinController::save(string filename){
    vector<ofPoint> corners=vector<ofPoint>(4);
    corners=pinData->getCorners();
    ofJson json = ofxJsonUtils::create(kv(corners));
    ofxJsonUtils::writeToFile(filename, json);
}

void ofxCornerPinController::load(string filename){
    ofJson json = ofxJsonUtils::loadFromFile(filename);
    vector<ofPoint> corners=vector<ofPoint>(4);
    ofxJsonUtils::load(json, kv(corners));
    pinData->setCorners(corners);
}
