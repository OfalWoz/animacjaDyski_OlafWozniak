#pragma once
#include "iostream"
#include "ofMain.h"
#include <math.h>
class box {
public:
    int r;
    float x;// pozycja
    float y;
    float vx = 0;// predkosc
    float vy = 0;
    float m;//masa
    float cx;//punkt srodkowy
    float cy;
    float c;//sila punktu c
    const float g = 0.1;//grawitacja
    const float G = 6.673 * pow(10, 1);
    const float M = 2; //masa punktu c
    float my = 0;
    float mx = 0;
    float D; //sila opory
    float dt = (ofGetElapsedTimef()) * 0.9;
    float deltax, deltay;
    float R; //odleglosc miedzy pkt c a dyskiem
    float T; //czas w jakim dysk doleci do punktu
    float A; //przyspieszenie dysku
    float F; //sila dysku zmierzajac do c

    ofColor color;
    void draw();
    void wobble();
    void gravity();
    void cpoint(int i);
    void gpoint(int i);
    void stop();
    box(); //consturctor
    ~box(); //destructor
};

class point {
public:
    float cx = -10;//punkt srodkowy
    float cy = -10;
    float r = 5;
    ofColor color;
    void draw();
    point(); //consturctor
    ~point(); //destructor
};

class ofApp : public ofBaseApp {

public:
    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    void keyReleased(int key);
   
    vector<box> boxes;
    vector<point> cpoint;
};