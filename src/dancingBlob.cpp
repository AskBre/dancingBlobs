#include "dancingBlob.h"

void DancingBlob::setup(int nPoints) {
    // Set default values
    origo.set(ofGetWidth()/2, ofGetHeight()/2);
    points.resize(nPoints);
}

void DancingBlob::update() {

    flatifyFft(*fft);

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
    drawDebug(*fft);

    ofBeginShape();
    for(int i=0; i<points.size()+3; i++) {
        // Iterate through the start to connect it all
        point p = points.at(i%points.size());
        ofCurveVertex(p.x, p.y);
    }
    ofEndShape();
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

auto DancingBlob::getPointDists() {
    vector<float> dists;
    for(auto p : points) {
        dists.push_back(p.d);
    }
    return dists;
}

//--------------------------------------------------------------
void DancingBlob::updateDists() {
    int i = 0;
    float offset = (float)fft->size() / (float)(points.size()-1);
    float averaged = 0;
    float gain = ofGetHeight();

    for(int j=0; j<fft->size(); j++) {
        smoothFft.at(j) *= 0.99;
        if(smoothFft.at(j) < fft->at(j)) smoothFft.at(j) = fft->at(j);

        averaged += smoothFft.at(j) / offset;

        if(j > i*offset) {
            points.at(i).d = averaged * gain;
            i++;
            averaged = 0;
        }
    }
}

void DancingBlob::drawDebug(vector<float> &fs) {
    ofSetHexColor(0xFF0000);
    for(auto p : points) {
        ofDrawCircle(p.x, p.y, 2);
    }

    float gain = ofGetHeight();
    float offset = (float)ofGetWidth()/(float)fs.size();
    float xPos;

    ofPolyline line;
    for(auto f : fs) {
        line.curveTo(xPos, ofGetHeight()-(f*gain));
        xPos+=offset;
    }

    ofSetHexColor(0xFFFFFF);
    line.draw();
}

void DancingBlob::flatifyFft(vector<float> &vec) {
    // The lower the freq, the less its worth
    int count = vec.size();
    for(int i=0; i<count; i++){
        float gain = (float)i/(float)count;
        vec.at(i) *= (gain + 0.2);
    }
}
