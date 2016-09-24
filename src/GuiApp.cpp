#include "GuiApp.h"

void GuiApp::setup() {
	ofBackground(0);
	ofSetVerticalSync(false);

	space.set(" ");

	panel.setup();
	panel.add(frameRate.set("Framerate", 0));
	panel.add(isDebug);

	panel.add(space);
	panel.add(force.set("Global Force", 1, -2, 2));
	panel.add(maxPoints.set("Max points", 1, 1, 10000));

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

	/*
	for(unsigned i=0; i<volsPtr->size(); i++) {
		ofSetHexColor(0xFFFFFF);
		int gap = 5;
		int w = (ofGetWidth()/volsPtr->size()) - gap;
		int mh = ofGetHeight();
		int h = volsPtr->at(i) * mh;
		ofVec2f p((i *w+gap), mh);
		ofDrawRectangle(p, w, -h);
	}
	*/
}

void GuiApp::setVolsPtr(vector<float> *_volsPtr) {
	volsPtr = _volsPtr;
}

//--------------------------------------------------------------

