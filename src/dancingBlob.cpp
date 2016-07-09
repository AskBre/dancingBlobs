#include "dancingBlob.h"

void DancingBlob::setup(int nPoints) {
    // Set default values
    origo.set(ofGetWidth()/2, ofGetHeight()/2);
    points.resize(nPoints);
}

void DancingBlob::update() {
    
    float angleChangePerPt = TWO_PI / (float)points.size();
    float angle = 0;
    
    for (auto &p : points) {
        if(p.d > 5) {
            p.d += ofRandom(-0.5, 0.5);
        } else {
            p.d += ofRandom(0.5);
        }
        p.x = origo.x + p.d * sin(angle);
        p.y = origo.y + p.d * cos(angle);
        
        angle += angleChangePerPt;
    }
}

void DancingBlob::draw() {
    ofSetHexColor(0xFFFFFF);
    
    ofPolyline blob;
    
    // Iterate through points and curve to each
    // Go through three first again to connect end
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
    p.d = points[ofRandom(points.size()-1)].d;
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

void DancingBlob::setPointDists(vector<float> &dists) {
    if(dists.size() != points.size()) {
        cerr << "Couldn't set point dists in setPointDists, vectors are of different length." << endl;
        return;
    } else {
        for(int i=0; i<dists.size(); i++) {
            points.at(i).d = dists.at(i);
        }
    }
}

void DancingBlob::getPointDists() {
    vector<float> dists;
    for(auto p : points) {
        dists.push_back(p.d);
    }
    return dists;
}