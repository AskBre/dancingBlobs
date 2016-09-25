#pragma once

#include "ofMain.h"
#include "ofxAubio.h"

enum type_t {
	DIRECT,
	EASE,
	EASE_OUT,
	EASE_IN,
};

class DancingBlob : public ofBaseApp {

	public:
		DancingBlob(type_t type);
		~DancingBlob() {
			ofRemoveListener(ofEvents().mousePressed, this, &DancingBlob::mousePressed);
			ofRemoveListener(ofEvents().mouseReleased, this, &DancingBlob::mouseReleased);
			ofRemoveListener(ofEvents().mouseDragged, this, &DancingBlob::mouseDragged);
		};

		void update(vector<float> &_bands);
		void draw();
		void drawDebug();

		void addPoint();
		void removePoint();
		void setPointCount(unsigned count);

		void newGain();

		void mousePressed(ofMouseEventArgs &mouseArgs);
		void mouseReleased(ofMouseEventArgs &mouseArgs);
		void mouseDragged(ofMouseEventArgs &mouseArgs);

		type_t type;
		ofParameter<float> gain;
		ofParameter<float> speed;

	private:
		struct point {
			float x = 0;
			float y = 0;
			float d = 0;
		};

		vector<float> bands;
		vector<float> smoothBands;
		vector<point> points;

		// TODO save origo between sessions
		ofVec2f origo;
		bool beingDragged = false;


		void updateDists();

		void updateDirect();
		void updateEase();
		void updateEaseOut();
		void updateEaseIn();
};
