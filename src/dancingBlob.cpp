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
        float r = radius + ofRandom(-5, 5);
        
        p.x = origo.x + r * sin(angle);
        p.y = origo.y + r * cos(angle);
        
        angle += angleChangePerPt;
    }
}

void DancingBlob::draw() {
    ofSetHexColor(0xFFFFFF);
    
    ofPolyline blob;
    
    for(int i=0; i<nPoints+3; i++) {
        blob.curveTo(points[i%nPoints]);
    }
    
    blob.draw();
}