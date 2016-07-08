#pragma once

#include "ofMain.h"

class DancingBlob : public ofBaseApp {
    
public:
    void setup();
    void update();
    void draw();
        
private:
    
    struct point {
        float x;
        float y;
        float r;
    };
    
    vector<point> points;
    int nPoints;
    ofVec2f origo;
    float radius;
};
