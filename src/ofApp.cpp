#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    ofEnableSmoothing();
    
    ofBackground(0);
    blob.setup();
}

//--------------------------------------------------------------
void ofApp::update(){
    blob.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    blob.draw();
    
    ofDrawBitmapString(ofToString(ofGetFrameRate()), 10, 10);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    blob.setOrigo(ofVec2f(x, y));
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    switch (button) {
        case 0:
            blob.addPoint();
            break;
        case 1:
            blob.removePoint();
            break;
        case 2:
            blob.setPointCount(100);
        default:
            break;
    }
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
