#include "ofApp.h"

// TODO Enable selecting of different forms of audio-visual interaction
// TODO Change user interface to enable several blobs
// TODO Make second screen with basic GUI

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetVerticalSync(true);
	ofEnableSmoothing();
	ofBackground(0);

	int pointCount = 6;
	int bufferSize = 256;
	int sampleRate = 44100;

	blob.setup(bufferSize, sampleRate);
	blob.setPointCount(pointCount);

	ofSoundStreamSetup(0, 1, this);

}

void ofApp::exit() {
	ofSoundStreamStop();
	ofSoundStreamClose();
}

void ofApp::update(){
	blob.update();
}

void ofApp::draw(){
	blob.draw();
	if(gui->isDebug) blob.drawDebug();
}

void ofApp::audioIn(float *input, int bufferSize, int nChannels) {
// TODO Optimize by pushing audio-data only per frame update
	blob.audioIn(input, bufferSize);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
}

void ofApp::keyReleased(int key){
}

void ofApp::mouseMoved(int x, int y ){
}

void ofApp::mouseDragged(int x, int y, int button){
}

void ofApp::mousePressed(int x, int y, int button){
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

