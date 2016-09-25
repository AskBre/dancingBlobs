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
		~DancingBlob(){};

		void update(vector<float> &_bands);
		void draw();
		void drawDebug();

		void addPoint();
		void removePoint();
		void setPointCount(unsigned count);

		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseDragged(int x, int y, int button);

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
