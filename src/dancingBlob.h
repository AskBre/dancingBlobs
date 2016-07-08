#pragma once

#include "ofMain.h"

class DancingBlob : public ofBaseApp {
    
public:
    void setup();
    void update();
    void draw();
    
private:
    vector<ofVec2f> points;
    int nPoints;
    ofVec2f origo;
    float radius;
};
