#include "dancingBlob.h"

void DancingBlob::setup() {
    // Set default values
    origo.set(ofGetWidth()/2, ofGetHeight()/2);
    nPoints = 10;
    radius = 100;
    
    float angleChangePerPt = TWO_PI / (float)nPoints;
    float angle = 0;
    points.resize(nPoints);
}

void DancingBlob::update() {
    
    float angleChangePerPt = TWO_PI / (float)nPoints;
    float angle = 0;
    
    for (auto &p : points) {
        if(p.r > 0) {
            p.r += ofRandom(-0.49, 0.5);
        } else {
            p.r += ofRandom(0.5);
        }
        p.x = origo.x + p.r * sin(angle);
        p.y = origo.y + p.r * cos(angle);
        
        angle += angleChangePerPt;
    }
}

void DancingBlob::draw() {
    ofSetHexColor(0xFFFFFF);
    
    ofPolyline blob;
    
    for(int i=0; i<nPoints+3; i++) {
        ofVec2f pt;
        pt.x = points[i%nPoints].x;
        pt.y = points[i%nPoints].y;
        blob.curveTo(pt);
    }
    
    blob.draw();
}