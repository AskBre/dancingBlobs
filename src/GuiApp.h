#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class GuiApp : public ofBaseApp {
	public:
		void setup();
		void update();
		void draw();

		void setVolsPtr(vector<float> *_volsPtr);

		ofParameter<string> space;

		ofParameter<float> frameRate;

		ofParameter<float> force;
		ofParameter<unsigned> maxPoints;
		ofParameter<bool> isDebug;

		ofxButton save;
		ofxButton clear;

	private:
		vector<float> *volsPtr;

		ofxPanel panel;
};
