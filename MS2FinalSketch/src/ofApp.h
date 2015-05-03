#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"

class ofApp : public ofBaseApp{
    
    void setup();
    void update();
    void draw();
    
    
    void keyPressed  (int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mousePressed(int x, int y, int button);

    
    ofVideoGrabber movie;
    
    ofxCvColorImage rgb,hsb;
    ofxCvGrayscaleImage hue,sat,bri,filtered;
    ofxCvContourFinder contours;
    
    
    //this holds all of our points
    vector<ofVec3f> points;
    //this keeps track of the center of all the points
    ofVec3f center;
    
    //our camera objects for looking at the scene from multiple perspectives
    ofCamera camera;
    
    //if usecamera is true, we'll turn on the camera view
    bool usecamera;
    
    int w,h;
    int findHue;

};
