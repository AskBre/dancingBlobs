#pragma once

#include "ofMain.h"

class DancingBlob : public ofBaseApp {
    
public:
    void setup(int nPoints = 10);
    void update();
    void draw();
    
    void setOrigo(ofVec2f pos){origo = pos;};
    void getOrigo(){return origo;};
    
    void addPoint();
    void removePoint();
    void setPointCount(int count);
    void getPointCount(){return points.size();};
    
    void setPointDists(vector<float> &dists);
    void getPointDists();
    
    
private:
    struct point {
        float x = 0;
        float y = 0;
        float d = 0;
    };
    
    vector<point> points;
    vector<float> *fft;
    vector<float> smoothFft;
    
    ofVec2f origo;
    
    void updateDists();
    
    void drawFft(vector<float> &fs);
};