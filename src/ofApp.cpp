#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetVerticalSync(true);
	ofEnableSmoothing();
	ofBackground(0);

	int bufferSize = 256;
	int sampleRate = 44100;
	int blobCount = 2;

	channels.resize(blobCount);
	for(auto &c : channels) c.resize(bufferSize);

	for(auto f : channels.at(0)) cout << f << endl;

	for(int i=0; i<blobCount; i++) {
		blobs.push_back(DancingBlob());
		blobs.at(i).setup(EASE, bufferSize, sampleRate);

//		blobs.at(i).gain.makeReferenceTo(gui->blobPanels.at(i).gain);
//		blobs.at(i).speed.makeReferenceTo(gui->blobPanels.at(i).speed);
//		blobs.at(i).gain = gui->blobPanels.at(i).gain;
//		blobs.at(i).speed = gui->blobPanels.at(i).speed;
	}

	ofSoundStreamSetup(0, blobCount, this);
}

void ofApp::exit() {
	ofSoundStreamStop();
	ofSoundStreamClose();
}

void ofApp::update(){
	for(unsigned i=0; i<blobs.size(); i++) {
		auto &b = blobs.at(i);

		for(auto f : channels.at(i)) cout << f << endl;
		cout << endl;

		b.audioIn(&channels.at(i)[0], channels.at(i).size());
		b.update();
	}

//	blob.update();
}

void ofApp::draw(){
	for(auto &b: blobs) {
		b.draw();
		if(gui->isDebug) b.drawDebug();
	}
}

void ofApp::audioIn(float *input, int bufferSize, int nChannels) {
		for(unsigned i=0; i<bufferSize; i++) {
	for(unsigned j=0; j<nChannels; j++) {
//			cout << "i: " << i << " j: " << j << endl;
//			cout << "Channels " << channels.size() << " floats " << channels.at(j).size() << endl;
			channels.at(j).at(i) = 0.0002;
		}
	}

	/*
	for(unsigned i=0; i< blobs.size(); i++) {
		for(unsigned j=0; j<bufferSize; j+=blobs.size()) {
			channels[i][j]=input[j+i];
		}

		blobs.at(i).audioIn(channels[i], bufferSize);
	}
	*/

//	for(auto b : blobs) b.audioIn(chan, bufferSize, nChannels);
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
