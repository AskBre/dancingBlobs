#include "GuiApp.h"

void GuiApp::setup() {
	ofBackground(0);
	ofSetVerticalSync(false);

	blobSpeeds.resize(blobCount);
	blobGains.resize(blobCount);
	blobPos.resize(blobCount);

	space.set(" ");

	panel.setup();
	panel.add(frameRate.set("Framerate", 0));
	panel.add(isDebug.set("Debug-layer", true));

	panel.add(space);
	panel.add(curBlob.set("Current blob", 1, 1, blobCount));			
	panel.add(maxPoints.set("Max points", 1, 1, 10000));

	panel.add(space);
	for(unsigned i=0; i<blobCount; i++) {
		string name = "Blob " + ofToString(i+1) + " Speed";
		panel.add(blobSpeeds.at(i).set(name, 0.0001, 0.00001, 0.001));
		name = "Blob " + ofToString(i+1) + " Gain";
		panel.add(blobGains.at(i).set(name, 10500, 1, 100000));

		name = "Pos of blob " + ofToString(i+1);
		ofVec2f min = ofVec2f(0, 0);
		ofVec2f cur = ofVec2f(ofGetWidth()*0.5, ofGetHeight()*0.5);
		ofVec2f max = ofVec2f(ofGetWidth(), ofGetHeight());

		panel.add(blobPos.at(i).set(name, cur, min, max));
		panel.add(space);
	}

	// TODO Connect these to something
	panel.add(space);
	panel.add(save.setup("Save"));
	panel.add(clear.setup("Clear"));

	panel.setSize(500,500);
	panel.setWidthElements(500);
}

void GuiApp::update() {
	frameRate = ofGetFrameRate();
}

void GuiApp::draw() {
	panel.draw();
}
