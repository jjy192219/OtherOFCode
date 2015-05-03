#pragma once

#include "ofMain.h"

#include "ofxOsc.h"

#include "ball.h"

//set the same port used for sender
#define PORT 8000

class ofApp : public ofBaseApp{
    
    
    
public:
    
    
    
    void setup();
    
    void update();
    
    void draw();
    
    
    //function for passing the osc messages
    void dumpOSC(ofxOscMessage m);
    
    
    
    //osc reveiver
    ofxOscReceiver receiver;
    
    // mouse position
    
    ofPoint remoteMouse;
    
    // mousebutton state
    
    string mouseButtonState;
    
    //ball vectors
    vector<Ball> ballVector;
    
    void keyPressed(int key);
    
    
};