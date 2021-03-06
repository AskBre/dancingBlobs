#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetVerticalSync(true);
	ofEnableSmoothing();
	ofBackground(0);

	int bufferSize = 256;
	int sampleRate = 44100;

	blobs.push_back(DancingBlob(EASE));
	blobs.push_back(DancingBlob(DIRECT));

	gui->setBlobCount(blobs.size());
	gui->setup();

	for(unsigned i=0; i<blobs.size(); i++) {
		blobs.at(i).gain.makeReferenceTo(gui->blobGains.at(i));
		blobs.at(i).speed.makeReferenceTo(gui->blobSpeeds.at(i));
		blobs.at(i).origo.makeReferenceTo(gui->blobPos.at(i));
	}

	// Setup aubio-analyzers
	bands.resize(blobs.size());
	for(auto &b : bands) b.setup("default", bufferSize*2, bufferSize, sampleRate);
	ofSoundStreamSetup(0, blobs.size(), this);
}

void ofApp::exit() {
	ofSoundStreamStop();
	ofSoundStreamClose();
}

void ofApp::update(){
	for(unsigned i=0; i<blobs.size(); i++) {
		vector<float> vBands;
		for(unsigned j=0; j<bands.at(i).nBands; j++) {
			vBands.push_back(bands.at(i).energies[j]);
		}
		blobs.at(i).update(vBands);
	}
}

void ofApp::draw(){
	for(auto &b: blobs) {
		b.draw();
		if(gui->isDebug) b.drawDebug();
	}
}

void ofApp::audioIn(float *input, int bufferSize, int nChannels) {
	for(int i=0; i<nChannels; i++) {
		float channel[(bufferSize/nChannels)+1];
		int j=0;
		for(int k=0; k<bufferSize; k+=nChannels){
			channel[j] = input[k+i];
			j++;
		}

		bands.at(i).audioIn(channel, bufferSize/nChannels, 1);
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	// key-59 gives the number
	unsigned keyNum = key-48;
	if(keyNum >= 1 && keyNum <= blobs.size()) {
		gui->curBlob = keyNum;
	}
}

void ofApp::keyReleased(int key){
}

void ofApp::mouseMoved(int x, int y ){
}

void ofApp::mouseDragged(int x, int y, int button){
	blobs.at(gui->curBlob-1).mouseDragged(x, y, button);
}

void ofApp::mousePressed(int x, int y, int button){
	blobs.at(gui->curBlob-1).mousePressed(x, y, button);
}

void ofApp::mouseReleased(int x, int y, int button){
	blobs.at(gui->curBlob-1).mouseReleased(x, y, button);
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
