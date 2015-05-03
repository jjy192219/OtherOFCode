#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetVerticalSync(true);
    ofSetFrameRate(60);
    
    ofBackground(255,0,130);
    
    ofSetBackgroundAuto(false);
    
    ofBackground(255, 255, 255);
    
    brainWave.setup();
    brainWave.start();
    
//    ard.connect("/dev/tty.usbserial-DA00VGFP", 57600);
    
    ard.connect("/dev/tty.usbmodem1411", 57600);

    
    // listen for EInitialized notification. this indicates that
    // the arduino is ready to receive commands and it is safe to
    // call setupArduino()
    
    
    ofAddListener(ard.EInitialized, this, &ofApp::setupArduino);
    bSetupArduino	= false;	// flag so we setup arduino when its ready, you don't need to touch this :)
    

}

//--------------------------------------------------------------
void ofApp::update(){
    
    updateArduino();
    updateBrain();

}




//---------Setup arduino----------------

void ofApp::setupArduino(const int & version) {

    // remove listener because we don't need it anymore
    ofRemoveListener(ard.EInitialized, this, &ofApp::setupArduino);
    
    // it is now safe to send commands to the Arduino
    bSetupArduino = true;
    
    // print firmware name and version to the console
    ofLogNotice() << ard.getFirmwareName();
    ofLogNotice() << "firmata v" << ard.getMajorFirmwareVersion() << "." << ard.getMinorFirmwareVersion();
    
    // Note: pins A0 - A5 can be used as digital input and output.
    // Refer to them as pins 14 - 19 if using StandardFirmata from Arduino 1.0.
    // If using Arduino 0022 or older, then use 16 - 21.
    // Firmata pin numbering changed in version 2.3 (which is included in Arduino 1.0)
    
    // set pin D13 as digital output
    ard.sendDigitalPinMode(13, ARD_OUTPUT);
    
}


void ofApp::updateArduino(){
    
    // update the arduino, get any data or messages.
    // the call to ard.update() is required
    ard.update();
    
    
}


void ofApp::updateBrain(){
    
    EegData data = brainWave.getEegData();
    cout << data.delta <<  endl;
    cout << "attention:" << data.attention << endl;
    cout << "meditation"<< data.meditation << endl;
    
//    int meditation = data.meditation;
//
//    if(meditation >= 65){
//    
//        ard.sendDigital(13, ARD_HIGH);
//    
//    }
//    else{
//    
//        ard.sendDigital(13, ARD_LOW);
//        
//    }
    
    
    ard.sendDigital(13, ARD_HIGH);
}




//--------------------------------------------------------------
void ofApp::draw(){
    

}


//--------------

void ofApp::keyPressed  (int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    

    
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
