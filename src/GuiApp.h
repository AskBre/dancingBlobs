#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class GuiApp : public ofBaseApp {
	public:
		void setup();
		void update();
		void draw();

		void setBlobCount(unsigned count) {
			blobCount = count;
			curBlob.set("Current blob", curBlob, 1, blobCount);
		};

		ofxPanel panel;

		ofParameter<unsigned> maxPoints;
		ofParameter<unsigned> curBlob;
		ofParameter<bool> isDebug;

		vector<ofParameter<float>> blobSpeeds;
		vector<ofParameter<float>> blobGains;
		vector<ofParameter<ofVec2f>> blobPos;

		unsigned blobCount = 1;

		ofxButton save;
		ofxButton clear;

	private:
		ofParameter<string> space;
		ofParameter<float> frameRate;
};
