#include "GuiApp.h"

void GuiApp::setup() {
	ofBackground(0);
	ofSetVerticalSync(false);

	blobVals.resize(2);

	space.set(" ");

	panel.setup();
	panel.add(frameRate.set("Framerate", 0));
	panel.add(isDebug.set("Debug-layer", true));

	panel.add(space);
	panel.add(curBlob.set("Current blob", 1, 1, 1));
	panel.add(maxPoints.set("Max points", 1, 1, 10000));

	panel.add(space);
	for(unsigned i=0; i<blobVals.size(); i++) {
		string name = ofToString("Speed and gain of blob " + i);
		panel.add(
				blobVals.at(i).set(name,
					ofVec2f(0.0001, 1050),
					ofVec2f(0, 1),
					ofVec2f(0.001, 10000)));
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
