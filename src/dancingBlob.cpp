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
    ofSetHexColor(0xFFFFFF);
    
    ofBeginShape();
        for(auto p : points) {
            ofCurveVertex(p.x, p.y);
        }
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
    if(dists.size() != points.size()) {
        cerr << "Couldn't set point dists in setPointDists, vectors are of different length." << endl;
        cout << "Changing point size to " << dists.size() << endl;
        setPointCount(dists.size());
    }
    
    fft = &dists;
    smoothFft.resize(fft->size());
    
//    } else {
//        for(int i=0; i<dists.size(); i++) {
//            if(points.at(i).d > 0) {
//                points.at(i).d += (dists.at(i)*(1+i*0.1));
//            } else {
//                points.at(i).d = 0.01;
//            }
//        }
//    }
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
    for(int i=0; i<fft->size(); i++) {
        smoothFft.at(i) *= 0.96;
        if(smoothFft.at(i) < fft->at(i)) smoothFft.at(i) = fft->at(i);
        
        points.at(i).d = smoothFft.at(i)*ofGetWidth()/4;
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