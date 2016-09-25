#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class GuiApp : public ofBaseApp {
	public:
		void setup();
		void update();
		void draw();

		void setBlobCount(unsigned count) {curBlob.set("Current blob", curBlob, 1, count);};

		ofxPanel panel;

		ofParameter<unsigned> maxPoints;
		ofParameter<unsigned> curBlob;
		ofParameter<bool> isDebug;

		vector<ofParameter<ofVec2f>> blobVals;

		ofxButton save;
		ofxButton clear;

	private:
		ofParameter<string> space;
		ofParameter<float> frameRate;

};
