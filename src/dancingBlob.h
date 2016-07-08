#pragma once

#include "ofMain.h"

class DancingBlob : public ofBaseApp {
    
public:
    void setup();
    void update();
    void draw();
    
    void setOrigo(ofVec2f pos){origo = pos;};
    void addPoint();
    void removePoint();
    void setPointCount(int count);
    void getPointCount(){return points.size();};
    
private:
    struct point {
        float x = 0;
        float y = 0;
        float r = 0;
    };
    
    vector<point> points;
    ofVec2f origo;
};
