#include "dancingBlob.h"

void DancingBlob::setup(int nPoints) {
    // Set default values
    origo.set(ofGetWidth()/2, ofGetHeight()/2);
    points.resize(nPoints);
}

void DancingBlob::update() {
    
    float angleChangePerPt = TWO_PI / (float)points.size();
    float angle = 0;
    updateDists();
    for (auto &p : points) {
        p.x = origo.x + p.d * sin(angle);
        p.y = origo.y + p.d * cos(angle);
        
        angle += angleChangePerPt;
    }
}

void DancingBlob::draw() {
    
    ofBeginShape();
    for(int i=0; i<points.size()+3; i++) {
        // Iterate through the start to connect it all
        point p = points.at(i%points.size());
        ofCurveVertex(p.x, p.y);
        
        ofSetHexColor(0xFF0000);
        ofDrawCircle(p.x, p.y, 2);
    }
    ofSetHexColor(0xFFFFFF);
    ofEndShape();
    
    drawFft(smoothFft);
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
    fft = &dists;
    smoothFft.resize(fft->size());
}

void DancingBlob::getPointDists() {
    vector<float> dists;
    for(auto p : points) {
        dists.push_back(p.d);
    }
    return dists;
}

//--------------------------------------------------------------
void DancingBlob::updateDists() {
    int i = 0;
    float offset = fft->size()/points.size();
    float averaged = 0;
    
    for(int j=0; j<fft->size(); j++) {
        smoothFft.at(j) *= 0.96;
        if(smoothFft.at(j) < fft->at(j)) smoothFft.at(j) = fft->at(j);
        
        averaged += smoothFft.at(j) / offset;
        
        if(j> i*offset) {
            points.at(i).d = averaged * ofGetWidth()/4;
            averaged = 0;
            i++;
        }
    }
}

void DancingBlob::drawFft(vector<float> &fs) {
    float gain = ofGetHeight()/4;
    float offset = ofGetWidth()/fs.size();
    float xPos;
    
    ofPolyline line;
    ofSetHexColor(0xFFFFFF);
    
    for(auto f : fs) {
        line.curveTo(xPos, ofGetHeight()-(f*gain));
        xPos+=offset;
    }
    
    line.draw();
}