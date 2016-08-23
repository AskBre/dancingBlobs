#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    ofEnableSmoothing();
    ofBackground(0);

    int pointCount = 6;
    int fftSize = 512;
    int audioBufferSize = 512;
    blob.setup();
    blob.setPointCount(pointCount);

//    fft.setup(16384);
    fft.setup(fftSize, OF_FFT_WINDOW_SINE, OF_FFT_BASIC, audioBufferSize, 44100);
    fft.setUseNormalization(true);
}

void ofApp::update(){
    fft.update();
    blob.setPointDists(fft.getBins());
    blob.update();
}

void ofApp::draw(){
    blob.draw();

    ofDrawBitmapString(ofToString(ofGetFrameRate()), 10, 10);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
}

void ofApp::keyReleased(int key){
}

void ofApp::mouseMoved(int x, int y ){
}

void ofApp::mouseDragged(int x, int y, int button){
    blob.setOrigo(ofVec2f(x, y));
}

void ofApp::mousePressed(int x, int y, int button){
    switch (button) {
        case 0:
            blob.addPoint();
            break;
        case 2:
            blob.removePoint();
        default:
            break;
    }
}

void ofApp::mouseReleased(int x, int y, int button){
}

void ofApp::mouseEntered(int x, int y){
}

void ofApp::mouseExited(int x, int y){
}

void ofApp::windowResized(int w, int h){
}

void ofApp::gotMessage(ofMessage msg){
}

void ofApp::dragEvent(ofDragInfo dragInfo){
}
//--------------------------------------------------------------

