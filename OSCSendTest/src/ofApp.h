#pragma once

#include "ofMain.h"

#include "ofxOsc.h"

//the host ip of my laptop
//#define HOST "192.168.1.7"


//degine a port for sender to use
#define PORT 8000

class ofApp : public ofBaseApp{
    
    
    
public:
    
    void setup();
    
    void update();
    
    void draw();
    
    void mouseMoved(int x, int y );
    
    void mouseDragged(int x, int y, int button);
    
    void mousePressed(int x, int y, int button);
    
    void mouseReleased(int x, int y, int button);
    
    
    //set up osc sender
    ofxOscSender sender;
    
};