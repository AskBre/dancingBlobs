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
		~DancingBlob() {
			ofRemoveListener(ofEvents().mousePressed, this, &DancingBlob::mousePressed);
			ofRemoveListener(ofEvents().mouseReleased, this, &DancingBlob::mouseReleased);
			ofRemoveListener(ofEvents().mouseDragged, this, &DancingBlob::mouseDragged);
		};

		void setup(type_t type, int bufferSize, int sampleRate);

		void update();
		void draw();
		void drawDebug();

		void audioIn(float * input, int bufferSize);

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

		ofxAubioMelBands bands;
		ofxAubioPitch pitch;

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
