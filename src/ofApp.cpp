#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    int maxBoxes;
    maxBoxes = 1000;
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
	ofDrawBitmapString("hold 's' - stop movement", 0, 10);
	ofDrawBitmapString("hold 'p' - set up point position",0,20);
	ofDrawBitmapString("hold 'g' - turn on gravity", 0, 30);
	ofDrawBitmapString("hold 'k' - gravitional pull on point", 0, 40);
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
			boxes[i].cpoint(i);
		}
		break;
	case 'g': //wlaczenie grawitacji
		for (int i = 0; i < boxes.size(); i++) {
			boxes[i].gravity();
		}
		break;
	case'k': //wlaczenie i zmiana polozenia punktu
		for (int i = 0; i < boxes.size(); i++) {
			POINT cursorPos;
			GetCursorPos(&cursorPos);
			boxes[i].cx = cursorPos.x;
			boxes[i].cy = cursorPos.y;
			cpoint[0].cx = cursorPos.x;
			cpoint[0].cy = cursorPos.y;
			boxes[i].gpoint(i);
		}
		break;
	case's': //wlaczenie i zmiana polozenia punktu
		for (int i = 0; i < boxes.size(); i++) {
			boxes[i].stop();
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
	case'k': //wlaczenie i zmiana polozenia punktu
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
	if (y < ofGetHeight()) {
		//grawitacja
		vy = vy + (g * m) * dt;
	}
}
//--------------------------------------------------------------
void box::cpoint(int i)
{
	if (x > cx) {
		deltax = x - cx;
	}
	else {
		deltax = cx - x;
	}
	if (y > cy) {
		deltay = y - cy;
	}
	else {
		deltay = cy - y;
	}
	R = sqrt(pow(deltay, 2) + pow(deltax, 2));
	T = vy / R;
	A = vy / T;
	F = (A * m);
	c = 0.0001/pow(R,-2);
	//std::cout << F <<" "<<i<< "\n";
	if (y <= cy) {
		vy = vy + c * dt;
	}
	
	if (x <= cx) {
		vx = vx + c * dt;
	}

	if (y >= cy) {
		vy = vy - c * dt;
	}

	if (x >= cx) {
		vx = vx - c * dt;
	}
}

void box::stop()
{
	vy = 0;
	vx = 0;
}

void box::gpoint(int i)
{
	if (x > cx) {
		deltax = x - cx;
	}
	else {
		deltax = cx - x;
	}
	if (y > cy) {
		deltay = y - cy;
	}
	else {
		deltay = cy - y;
	}
	R = sqrt(pow(deltay, 2) + pow(deltax, 2));
	T = vy / R;
	A = vy / T;
	F = (A * m);
	c = (G * m * M) / pow(R, 2);
	//std::cout << F <<" "<<i<< "\n";
	if (y <= cy) {
		vy = vy + c * dt;
	}

	if (x <= cx) {
		vx = vx + c * dt;
	}

	if (y >= cy) {
		vy = vy - c * dt;
	}

	if (x >= cx) {
		vx = vx - c * dt;
	}
}
//--------------------------------------------------------------
void box::draw() {
    ofSetColor(color);
	ofDrawSphere(x, y, r);
}

//--------------------------------------------------------------
void box::wobble() {
		
		//sprawdzanie pozycji i obijanie od scianek
		D = -(6 * 3.14 * 0.00001554 * (vx + vy) * r);
		//std::cout << c << "\n";
		x = x + vx * dt;
		y = y + vy * dt;

		if (vy < 0) {
			vy = vy + D * dt;
		}

		if (vy > 0) {
			vy = vy + D * dt;
		}

		if (vx < 0) {
			vx = vx + D * dt;
		}

		if (vx > 0) {
			vx = vx + D * dt;
		}

		if (vx == 0) {
			vx = 0;
		}

		if (vy == 0) {
			vy = 0;
		}

		if (x > ofGetWidth() - r) {
			vx = -vx;
			x = ofGetWidth() - r;
		}

		if (x <= r) {
			vx = -vx;
			x = r;
		}

		if (y >= ofGetHeight() - r) {
			vy = -vy;
			y = ofGetHeight() - r;
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