#include "dancingBlob.h"
// TODO Flatten FFT so bass doesn't have the extreme priority

void DancingBlob::setup(type_t _type, int bufferSize, int sampleRate) {
	type = _type;

	// Setup mouse events
	ofAddListener(ofEvents().mousePressed, this, &DancingBlob::mousePressed);
	ofAddListener(ofEvents().mouseReleased, this, &DancingBlob::mouseReleased);
	ofAddListener(ofEvents().mouseDragged, this, &DancingBlob::mouseDragged);
	
	// Set default values
	int nPoints = 10;

	speed.set("Speed", 0.0001, 0.00001, 0.01);
	gain.set("Gain", ofGetHeight(), 1, 1000);

	origo.set(ofGetWidth()/2, ofGetHeight()/2);
	points.resize(nPoints);
	points.pop_back();

	// Setup aubio-analyzers
	bands.setup("default", bufferSize * 2, bufferSize * 0.5, sampleRate);
	pitch.setup("yinfft", 8 * bufferSize, bufferSize, sampleRate);

	//
	smoothBands.resize(bands.nBands);

	cout << "Blob setup with type " << type << ", bs " << bufferSize << "and sr " << sampleRate << endl;
}

void DancingBlob::update() {
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

	ofDrawBitmapString(pitch.latestPitch, 10, 20);
	ofDrawBitmapString(pitch.pitchConfidence, 10, 30);

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

//--------------------------------------------------------------
void DancingBlob::audioIn(float *input, int bufferSize) {
	bands.audioIn(input, bufferSize, 1);
	pitch.audioIn(input, bufferSize, 1);
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
void DancingBlob::mousePressed(ofMouseEventArgs &mouseArgs) {
	ofVec2f m = ofVec2f(mouseArgs.x, mouseArgs.y);
	if(m.distance(origo) < 10) {
		beingDragged = true;
	}
}

void DancingBlob::mouseReleased(ofMouseEventArgs &mouseArgs) {
	beingDragged = false;
}

void DancingBlob::mouseDragged(ofMouseEventArgs &mouseArgs) {
	if(beingDragged) {
		origo =	ofVec2f(mouseArgs.x, mouseArgs.y);
	}
}

//--------------------------------------------------------------
void DancingBlob::updateDists() {
	int i = 0;
	float offset = (float)bands.nBands / (float)(points.size()-1);
	float angleChangePerPt = TWO_PI / (float)points.size();
	float angle = 0;

	for(int j=0; j<bands.nBands; j++) {
		float dist = smoothBands[j]/offset;
		if(j > i*offset) {
			points.at(i).d = dist * gain;
			i++;
		}
	}

	for (auto &p : points) {
		p.x = origo.x + p.d * sin(angle);
		p.y = origo.y + p.d * cos(angle);

		angle += angleChangePerPt;
	}
}
//--------------------------------------------------------------
void DancingBlob::updateDirect() {
	for(int j=0; j<bands.nBands; j++) {
		if(smoothBands[j] > 0) {
			smoothBands[j] = bands.energies[j];
		} else {
			smoothBands[j] = speed;
		}
	}
}

void DancingBlob::updateEase() {
	for(int j=0; j<bands.nBands; j++) {
		if(smoothBands[j] > 0) {
			if(smoothBands[j] < bands.energies[j]) smoothBands[j] += speed;
			else if (smoothBands[j] > bands.energies[j]) smoothBands[j] -= speed;
		} else {
			smoothBands[j] = speed;
		}
	}
}

void DancingBlob::updateEaseOut() {
	for(int j=0; j<bands.nBands; j++) {
		if(smoothBands[j] > 0) {
			if(smoothBands[j] < bands.energies[j]) smoothBands[j] *= 1 + speed;
			else if (smoothBands[j] > bands.energies[j]) smoothBands[j] = bands.energies[j];
		} else {
			smoothBands[j] = speed;
		}
	}
}

void DancingBlob::updateEaseIn() {
	for(int j=0; j<bands.nBands; j++) {
		if(smoothBands[j] > 0) {
			if(smoothBands[j] < bands.energies[j]) smoothBands[j] = bands.energies[j];
			else if (smoothBands[j] > bands.energies[j]) smoothBands[j] *= speed;
		} else {
			smoothBands[j] = speed;
		}
	}
}
