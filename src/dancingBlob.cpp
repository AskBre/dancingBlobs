#include "dancingBlob.h"

void DancingBlob::setup() {
    // Set default values
    origo.set(ofGetWidth()/2, ofGetHeight()/2);
    points.resize(10);
}

void DancingBlob::update() {
    
    float angleChangePerPt = TWO_PI / (float)points.size();
    float angle = 0;
    
    for (auto &p : points) {
        if(p.r > 5) {
            p.r += ofRandom(-0.5, 0.5);
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
    
    // Iterate through points and curve to each
    // Go through three first again to connect
    for(int i=0; i<points.size()+3; i++) {
        ofVec2f pt;
        pt.x = points.at(i % points.size()).x;
        pt.y = points.at(i % points.size()).y;
        blob.curveTo(pt);
    }
    
    blob.draw();
}

//--------------------------------------------------------------

void DancingBlob::addPoint() {
    point p;
    p.r = points[ofRandom(points.size()-1)].r;
    points.insert(points.begin()+ofRandom(points.size()), p);
}

void DancingBlob::removePoint() {
    if(points.size() > 1){
        points.erase(points.begin()+ofRandom(points.size()));
    }
}

void DancingBlob::setPointCount(int count) {
    if(count < 1) {
        cerr << "Must have at least one point" << endl;
        return;
    }
    
    if(count < points.size()) {
        points.resize(count);
    }
    
    while(count > points.size()) {
        addPoint();
    }
}