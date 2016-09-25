#pragma once

#include "ofMain.h"
#include "ofxGui.h"

// TODO TODO TODO TODO
// This is a bad idea to spend time on. I know I'm using four blobs, so let's just make the gui static!!!
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
