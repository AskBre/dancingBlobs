#pragma once

#include "ofMain.h"
#include "ofxAubio.h"

class DancingBlob : public ofBaseApp {

	public:
		void setup(int bufferSize, int sampleRate);
		void update();
		void draw();

		void audioIn(float * input, int bufferSize);

		void setOrigo(ofVec2f pos){origo = pos;};
		ofVec2f getOrigo(){return origo;};

		void addPoint();
		void removePoint();
		void setPointCount(int count);
		int getPointCount(){return points.size();};

	private:
		struct point {
		float x = 0;
		float y = 0;
		float d = 0;
		};

		ofxAubioMelBands bands;
		vector<float> smoothBands;
		vector<point> points;

		ofVec2f origo;

		void updateDists();

		void drawDebug();
};
