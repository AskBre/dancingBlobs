#include "dancingBlob.h"

void DancingBlob::setup(int bufferSize, int sampleRate) {
    // Set default values
    int nPoints = 10;
    origo.set(ofGetWidth()/2, ofGetHeight()/2);
    points.resize(nPoints);
    bands.setup("default", 512, bufferSize, sampleRate);
    smoothBands.resize(bands.nBands);
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

    drawDebug();

    ofBeginShape();
    for(int i=0; i<points.size()+3; i++) {
        // Iterate through the start to connect it all
        point p = points.at(i%points.size());
        ofCurveVertex(p.x, p.y);
    }
    ofEndShape();
}

void DancingBlob::audioIn(float *input, int bufferSize) {
	bands.audioIn(input, bufferSize, 1);
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

//--------------------------------------------------------------
void DancingBlob::updateDists() {
    int i = 0;
    float offset = (float)bands.nBands / (float)(points.size()-1);
    float averaged = 0;
    float gain = ofGetHeight();

    for(int j=0; j<bands.nBands; j++) {
	smoothBands[j] *= 0.99;

        if(smoothBands[j] < bands.energies[j]) smoothBands[j] = bands.energies[j];

        averaged += smoothBands[j] / offset;

        if(j > i*offset) {
            points.at(i).d = averaged * gain;
            i++;
            averaged = 0;
        }
    }
}

void DancingBlob::drawDebug() {
    ofSetHexColor(0xFF0000);
    for(auto p : points) {
        ofDrawCircle(p.x, p.y, 2);
    }

    float gain = ofGetHeight();
    float offset = (float)ofGetWidth()/(float)bands.nBands;
    float xPos;

    ofPolyline line;
    for(int i=0; i<bands.nBands; i++) {
        line.curveTo(xPos, ofGetHeight()-(bands.energies[i]*gain));
        xPos+=offset;
    }
    ofSetHexColor(0xFFFFFF);
    line.draw();

    xPos = 0;
    ofPolyline smoothLine;
    for(int i=0; i<bands.nBands; i++) {
        smoothLine.curveTo(xPos, ofGetHeight()-(smoothBands[i]*gain));
        xPos+=offset;
    }

    ofSetHexColor(0xFFFFFF);
    smoothLine.draw();
}
