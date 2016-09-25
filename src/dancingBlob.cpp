#include "dancingBlob.h"
// TODO Flatten FFT so bass doesn't have the extreme priority

DancingBlob::DancingBlob(type_t _type) {
	type = _type;

	// Set default values
	int nPoints = 10;

	speed.set("Speed", 0.0001, 0.00001, 0.01);
	gain.set("Gain", ofGetHeight()*10, 1, 1000);

	origo.set("Pos", ofVec2f(ofGetWidth()/2, ofGetHeight()/2));
	points.resize(nPoints);
	points.pop_back();

	smoothBands.resize(bands.size());
}

void DancingBlob::update(vector<float> &_bands) {
	// TODO This should be used as reference all the way
	bands = _bands;

	if(smoothBands.size() != bands.size()) smoothBands.resize(bands.size());

	switch (type) {
		case DIRECT:
			updateDirect();
			break;
		case EASE:
			updateEase();
			break;
		// TODO Ease_out and _in doesn't work
		case EASE_OUT:
			updateEaseOut();
			break;
		case EASE_IN:
			updateEaseIn();
			break;
		default:
			updateEase();
			break;
	}

	updateDists();
}

void DancingBlob::draw() {
	ofSetHexColor(0xFFFFFF);

	// TODO Test different forms of drawing and winding
	ofBeginShape();
	for(unsigned i=0; i<points.size()+3; i++) {
		// Iterate through the start to connect it all
		int mi = i%(points.size()-1);
		point p = points.at(mi);

		ofCurveVertex(p.x, p.y);
	}
	ofEndShape();
}

void DancingBlob::drawDebug() {
	ofSetHexColor(0xFF0000);
	for(auto p : points) {
		ofDrawCircle(p.x, p.y, 2);
	}

	float gain = ofGetHeight();
	float offset = (float)ofGetWidth()/(float)bands.size();
	float xPos;

	ofPolyline line;
	for(unsigned i=0; i<bands.size(); i++) {
		line.curveTo(xPos, ofGetHeight()-(bands.at(i)*gain));
		xPos+=offset;
	}
	ofSetHexColor(0xFFFFFF);
	line.draw();

	xPos = 0;
	ofPolyline smoothLine;
	for(unsigned i=0; i<bands.size(); i++) {
		smoothLine.curveTo(xPos, ofGetHeight()-(smoothBands.at(i)*gain));
		xPos+=offset;
	}

	ofSetHexColor(0xFFFFFF);
	smoothLine.draw();
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

void DancingBlob::setPointCount(unsigned count) {
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
void DancingBlob::mousePressed(int x, int y, int button) {
	ofVec2f m = ofVec2f(x, y);
	if(m.distance(origo) < 10) {
		beingDragged = true;
	}
}

void DancingBlob::mouseReleased(int x, int y, int button) {
	beingDragged = false;
}

void DancingBlob::mouseDragged(int x, int y, int button) {
	if(beingDragged) {
		origo =	ofVec2f(x, y);
	}
}

//--------------------------------------------------------------
void DancingBlob::updateDists() {
	int i = 0;
	float offset = (float)bands.size() / (float)(points.size()-1);
	float angleChangePerPt = TWO_PI / (float)points.size();
	float angle = 0;

	for(unsigned j=0; j<bands.size(); j++) {
		float dist = smoothBands.at(j)/offset;
		if(j > i*offset) {
			points.at(i).d = dist * gain;
			i++;
		}
	}

	for (auto &p : points) {
		p.x = origo->x + p.d * sin(angle);
		p.y = origo->y + p.d * cos(angle);

		angle += angleChangePerPt;
	}
}
//--------------------------------------------------------------
void DancingBlob::updateDirect() {
	for(unsigned j=0; j<bands.size(); j++) {
		if(smoothBands.at(j) > 0) {
			smoothBands.at(j) = bands.at(j);
		} else {
			smoothBands.at(j) = speed;
		}
	}
}

void DancingBlob::updateEase() {
	for(unsigned j=0; j<bands.size(); j++) {
		if(smoothBands.at(j) > 0) {
			if(smoothBands.at(j) < bands.at(j)) smoothBands.at(j) += speed;
			else if (smoothBands.at(j) > bands.at(j)) smoothBands.at(j) -= speed;
		} else {
			smoothBands.at(j) = speed;
		}
	}
}

void DancingBlob::updateEaseOut() {
	for(unsigned j=0; j<bands.size(); j++) {
		if(smoothBands.at(j) > 0) {
			if(smoothBands.at(j) < bands.at(j)) smoothBands.at(j) *= 1 + speed;
			else if (smoothBands.at(j) > bands.at(j)) smoothBands.at(j) = bands.at(j);
		} else {
			smoothBands.at(j) = speed;
		}
	}
}

void DancingBlob::updateEaseIn() {
	for(unsigned j=0; j<bands.size(); j++) {
		if(smoothBands.at(j) > 0) {
			if(smoothBands.at(j) < bands.at(j)) smoothBands.at(j) = bands.at(j);
			else if (smoothBands.at(j) > bands.at(j)) smoothBands.at(j) *= speed;
		} else {
			smoothBands.at(j) = speed;
		}
	}
}
