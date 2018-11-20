#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    img.load("test2.png");
    cornerPin.setup(img.getWidth()*500/img.getHeight(),500,img.getWidth(),img.getHeight());
    controller.add(&cornerPin);
    controller.enable();
//    controller.add(&cornerPin);
//    controller.enable();
    
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    if(bGuide){
        cornerPin.drawGuide();
    }
    else{
        img.getTexture().bind();
        cornerPin.draw();
        img.getTexture().unbind();
    }
    
    ofDrawBitmapString(ofGetFrameRate(), 100, 100);
    
    controller.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key=='g'){
        bGuide=!bGuide;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

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
