#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class GuiApp : public ofBaseApp {
	public:
		void setup();
		void update();
		void draw();

		ofxPanel panel;

		ofParameter<unsigned> maxPoints;
		ofParameter<bool> isDebug;

		vector<ofParameter<ofVec2f>> blobVals;

		ofxButton save;
		ofxButton clear;

	private:
		ofParameter<string> space;
		ofParameter<float> frameRate;

};
