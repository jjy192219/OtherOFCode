#include "ofApp.h"

void ofApp::setup(){
    
    ofBackground(0, 0, 0);
    
    //pass the port and host ip to sender
    sender.setup(HOST, PORT);
    
}

void ofApp::update(){ }

void ofApp::draw(){
    
    
    ofSetColor(255, 255, 255);
    
    ofCircle(mouseX, mouseY, 10);
    
}

void ofApp::mouseMoved(int x, int y){
    
    // define a osc message for mouse postions, pass it to sender
    
    ofxOscMessage m;
    
    
    m.setAddress("/mouse/position");
    
    
    m.addIntArg(x);
    
    m.addIntArg(y);
    
    
    sender.sendMessage(m);
    
}

// define a osc message for mouse draged, pass it to sender

void ofApp::mouseDragged(int x, int y, int button){
    
    
    ofxOscMessage m;
    
    m.setAddress("/mouse/position");
    
    m.addIntArg(x);
    
    m.addIntArg(y);
    
    sender.sendMessage(m);
    
}


// define a osc message for mouse pressing, pass it to sender
// degine a "up" messaage for mouse pressing
void ofApp::mousePressed(int x, int y, int button){
    
    
    ofxOscMessage m;
    
    m.setAddress("/mouse/button");
    
    m.addStringArg("down");
    
    
    sender.sendMessage(m);
    
}

// define a osc message for mouse releasing, pass it to sender
//define a "down"message for mouse releaseing
void ofApp::mouseReleased(int x, int y, int button){
    
    
    ofxOscMessage m;
    
    
    m.setAddress("/mouse/button");
    
    m.addStringArg("up");
    
    sender.sendMessage( m );
    
}