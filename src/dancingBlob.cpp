#include "dancingBlob.h"

void DancingBlob::setup() {
    // Set default values
    origo.set(ofGetWidth()/2, ofGetHeight()/2);
    nPoints = 10;
    radius = 100;
    
    float angleChangePerPt = TWO_PI / (float)nPoints;
    float angle = 0;
    
    for (int i=0; i < nPoints; i++) {
        ofVec2f pt;
        
        pt.x = origo.x + radius * sin(angle);
        pt.y = origo.y + radius * cos(angle);
        
        points.push_back(pt);
        angle += angleChangePerPt;
    }
}

void DancingBlob::update() {
    for (auto &p : points) {
        p.x += ofRandom(-0.5, 0.5);
        p.y += ofRandom(-0.5, 0.5);
    }
}

void DancingBlob::draw() {
    ofSetHexColor(0xFFFFFF);
    
    ofPolyline blob;
    
    for(int i=0; i<nPoints+3; i++) {
        blob.curveTo(points[i%nPoints]);
    }
    
//    for(auto p : points) {
//        blob.curveTo(p);
//    }
    
    blob.draw();
}