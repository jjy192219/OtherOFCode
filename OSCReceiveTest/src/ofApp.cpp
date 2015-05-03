#include "ofApp.h"

void ofApp::setup(){
    
    ofBackground(255);
    
    //set up the initial values for receiver
    
    receiver.setup( PORT );
    
    mouseX = 0;
    
    mouseY = 0;
    
    mouseButtonState = "";
    
    
    
    for (int i=0; i<5; i++) {
        Ball stevieNicks;
        stevieNicks.setup(ofRandomWidth(), ofRandomHeight());
        ballVector.push_back(stevieNicks);
    }


}

void ofApp::update(){
    
    
    
    //if the recevier is working, get the messages
    
    while(receiver.hasWaitingMessages()){
        
        
        
        ofxOscMessage m;
        
        receiver.getNextMessage(&m);
        
        
        //mousemove
        // getting mouse positions message and assign the values to OSC variables getArgInt32
        
        if (m.getAddress() == "/mouse/position"){
            
            remoteMouse.x = m.getArgAsInt32(0);
            
            remoteMouse.y = m.getArgAsInt32(1);
            
            
            
        }
        //mousepressed
        
        
        else if (m.getAddress() == "/mouse/button"){
            
            mouseButtonState = m.getArgAsString(0) ;
            
        }
        
        //pass osc messages
        dumpOSC(m);
        
    }
    
    
    
    //update each item in the ball vector
    for (int i=0; i<ballVector.size(); i++) {
        ballVector[i].update();
    };
    
    
    
}

        
void ofApp::draw(){
    
    int radius;
    
    //read mousebutton states and draw balls if it is pressed
    if (mouseButtonState == "down") {
        
        radius = 60;
        
        ofSetColor(255, 127, 0);
       
        for(int i =0; i<5; i++){
            Ball barryGibbs;
            barryGibbs.setup(remoteMouse.x, remoteMouse.y);
            ballVector.push_back(barryGibbs);
        }
        
    } else {
        
        radius = 50;
        
        ofSetColor(0, 127, 255);
    }
        
        ofCircle(remoteMouse.x, remoteMouse.y, radius);
    
    
    for (int i =0; i<ballVector.size(); i++) {
        ballVector[i].draw();
    };
    


}




void ofApp::dumpOSC(ofxOscMessage m) {
    
    string msg_string;
    
    msg_string = m.getAddress();
    
    for (int i=0; i<m.getNumArgs(); i++ ) {
        
        msg_string += " ";
        
        if(m.getArgType(i) == OFXOSC_TYPE_INT32)
            
            msg_string += ofToString( m.getArgAsInt32(i));
        
        else if(m.getArgType(i) == OFXOSC_TYPE_FLOAT)
            
            msg_string += ofToString( m.getArgAsFloat(i));
        
        else if(m.getArgType(i) == OFXOSC_TYPE_STRING)
            
            msg_string += m.getArgAsString(i);
        
    }
    
    cout << msg_string << endl;
    
}

void ofApp::keyPressed(int key){
    
    //erase balls when mouse is pressed
    
    switch (key) {
        case OF_KEY_DOWN:
            if(ballVector.size()>0){
                ballVector.erase(ballVector.begin());
            }
            break;
            
        default:
            break;
    }
    
}



