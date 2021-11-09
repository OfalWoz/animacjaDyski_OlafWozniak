#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    int maxBoxes;
    maxBoxes = 100;
    for (int i = 0; i < maxBoxes; i++) {
        box newBox;
        boxes.push_back(newBox);
    }
	point newPoint;
	cpoint.push_back(newPoint);
}

//--------------------------------------------------------------
void ofApp::update() {
    for (int i = 0; i < boxes.size(); i++) {
        boxes[i].wobble();
    }
}

//--------------------------------------------------------------
void ofApp::draw() {
    for (int i = 0; i < boxes.size(); i++) {
        boxes[i].draw();
    }
	cpoint[0].draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	switch (key)
	{
	case'p': //wlaczenie i zmiana polozenia punktu
		for (int i = 0; i < boxes.size(); i++) {
			POINT cursorPos;
			GetCursorPos(&cursorPos);
			boxes[i].cx = cursorPos.x;
			boxes[i].cy = cursorPos.y;
			cpoint[0].cx = cursorPos.x;
			cpoint[0].cy = cursorPos.y;
			boxes[i].cpoint();
			
		}
		break;
	case 'g': //wlaczenie grawitacji
		for (int i = 0; i < boxes.size(); i++) {
			boxes[i].gravity();
		}
		break;
	}
	

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
	switch (key)
	{
	case'p': //wlaczenie i zmiana polozenia punktu
		for (int i = 0; i < boxes.size(); i++) {
			cpoint[0].cx = -10;
			cpoint[0].cy = -10;
		}
		break;
	}
}
//--------------------------------------------------------------
box::box() {
    //constructor
    r = ofRandom(20);
	m = r * 2;
	x = ofRandom(ofGetWidth());
	y = ofRandom(ofGetHeight());
	vx = 1;
	vy = 1;
	cx = mx;
	cy = my;
    color.set(ofRandom(255), ofRandom(255), ofRandom(255));
}
//--------------------------------------------------------------
box::~box() {

}
//--------------------------------------------------------------
void box::gravity()
{
	if (y < 720) {//grawitacja
		vy = vy + (g * m);
	}
}
//--------------------------------------------------------------
void box::cpoint()
{
	if (y < cy) {
		vy = vy - c * (-5);
	}

	if (x < cx) {
		vx = vx - c * (-5);
	}

	if (y > cy) {
		vy = vy + c * (-5);
	}

	if (x > cx) {
		vx = vx + c * (-5);
	}
}
//--------------------------------------------------------------
void box::draw() {
    ofSetColor(color);
	ofDrawSphere(x, y, r);
}

//--------------------------------------------------------------
void box::wobble() {
		c = (G * m * M) / pow(r,2);
		//sprawdzanie pozycji i obijanie od scianek
		//D = -6 * 3.14 * (vx + vy) * r;
		//std::cout << c << "\n";
		x = x + vx * 0.5;
		y = y + vy * 0.5;

		if (vy < 0) {
			vy = vy + 0.1;
		}

		if (vy > 0) {
			vy = vy - 0.1;
		}

		if (vx < 0) {
			vx = vx + 0.1;
		}

		if (vx > 0) {
			vx = vx - 0.1;
		}

		if (vx == 0) {
			vx = 0;
		}

		if (vy == 0) {
			vy = 0;
		}

		if (x > 1280 - r) {
			vx = -vx;
			x = 1280 - r;
		}

		if (x <= 0) {
			vx = -vx;
			x = 0;
		}

		if (y >= 720 - r) {
			vy = -vy;
			y = 720 - r;
		}

		if (y < r) {
			vy = -vy;
			y = r;
		}
}
//--------------------------------------------------------------
point::point(){
	color.set(255, 255, 255);
}
//--------------------------------------------------------------
point::~point(){
}
//--------------------------------------------------------------
void point::draw(){
	ofSetColor(color);
	ofDrawSphere(cx, cy, r);
}