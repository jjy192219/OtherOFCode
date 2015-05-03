#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0,0,0);
    
    w = ofGetWidth();
    h = ofGetHeight();
    
    ofSetLogLevel(OF_LOG_VERBOSE);
    movie.listDevices();
    movie.setDeviceID(0);
    movie.initGrabber(w, h, true);
    
    //reserve memory for cv images
    rgb.allocate(w, h);
    hsb.allocate(w, h);
    hue.allocate(w, h);
    sat.allocate(w, h);
    bri.allocate(w, h);
    filtered.allocate(w, h);
    
    ofSetFrameRate(60);
    ofSetVerticalSync(true);
    ofBackground(255);
    
    //initialize the variable so it's off at the beginning
    usecamera = false;
    
//    findHue = 130;



}

//--------------------------------------------------------------
void ofApp::update(){
    
    
    
    movie.update();
    
    if (movie.isFrameNew()) {
        
        //copy webcam pixels to rgb image
        rgb.setFromPixels(movie.getPixels(), w, h);
        
        //mirror horizontal
        rgb.mirror(false, true);
        
        //duplicate rgb
        hsb = rgb;
        
        //convert to hsb
        hsb.convertRgbToHsv();
        
        //store the three channels as grayscale images
        hsb.convertToGrayscalePlanarImages(hue, sat, bri);
        
        //filter image based on the hue value were looking for
        for (int i=0; i<w*h; i++) {
            filtered.getPixels()[i] = ofInRange(hue.getPixels()[i],findHue-5,findHue+5) ? 255 : 0;
        }
        filtered.flagImageChanged();
        
        //run the contour finder on the filtered image to find blobs with a certain hue
        contours.findContours(filtered, 50, w*h/2, 1, false);
    }
    
    
    //don't move the points if we are using the camera
    if(!usecamera){
        ofVec3f sumOfAllPoints(0,0,0);
        for(unsigned int i = 0; i < points.size(); i++){
            points[i].z -= 4;
            sumOfAllPoints += points[i];
        }
        center = sumOfAllPoints / points.size();
    }
    
    
   
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofSetColor(255,255,255);
    
    //draw all cv images
//    rgb.draw(0,0);
//    hsb.draw(0,0);
//    hue.draw(0,240);
//    sat.draw(320,240);
//    bri.draw(640,240);
//    filtered.draw(0,480);
//    contours.draw(0,0);
    
    ofSetColor(255, 0, 0);
    ofFill();
    
    //draw red circles for found blobs
    for (int i=0; i<contours.nBlobs; i++) {
        ofCircle(contours.blobs[i].centroid.x, contours.blobs[i].centroid.y, 10);
        
        if(usecamera){
            float rotateAmount = ofMap(contours.blobs[i].centroid.x, 0, ofGetWidth(), 0, 360);
            ofVec3f furthestPoint;
            if (points.size() > 0) {
                furthestPoint = points[0];
            }
            else
            {
                furthestPoint = ofVec3f(contours.blobs[i].centroid.x, contours.blobs[i].centroid.y, 0);
            }
            
            ofVec3f directionToFurthestPoint = (furthestPoint - center);
            ofVec3f directionToFurthestPointRotated = directionToFurthestPoint.rotated(rotateAmount, ofVec3f(0,1,0));
            camera.setPosition(center + directionToFurthestPointRotated);
            camera.lookAt(center);
        }
        //otherwise add points like before
        else{
            ofVec3f mousePoint(contours.blobs[i].centroid.x,contours.blobs[i].centroid.y,0);
            points.push_back(mousePoint);
        }

    }
    
    
    if(usecamera){
        camera.begin();
    }
    
    ofSetColor(0);
    //do the same thing from the first example...
    ofMesh mesh;
    mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
    for(unsigned int i = 1; i < points.size(); i++){
        
        //find this point and the next point
        ofVec3f thisPoint = points[i-1];
        ofVec3f nextPoint = points[i];
        
        //get the direction from one to the next.
        //the ribbon should fan out from this direction
        ofVec3f direction = (nextPoint - thisPoint);
        
        //get the distance from one point to the next
        float distance = direction.length();
        
        //get the normalized direction. normalized vectors always have a length of one
        //and are really useful for representing directions as opposed to something with length
        ofVec3f unitDirection = direction.normalized();
        
        //find both directions to the left and to the right
        ofVec3f toTheLeft = unitDirection.getRotated(-90, ofVec3f(0,0,1));
        ofVec3f toTheRight = unitDirection.getRotated(90, ofVec3f(0,0,1));
        
        //use the map function to determine the distance.
        //the longer the distance, the narrower the line.
        //this makes it look a bit like brush strokes
        float thickness = ofMap(distance, 0, 60, 20, 2, true);
        
        //calculate the points to the left and to the right
        //by extending the current point in the direction of left/right by the length
        ofVec3f leftPoint = thisPoint+toTheLeft*thickness;
        ofVec3f rightPoint = thisPoint+toTheRight*thickness;
        
        //add these points to the triangle strip
        mesh.addVertex(ofVec3f(leftPoint.x, leftPoint.y, leftPoint.z));
        mesh.addVertex(ofVec3f(rightPoint.x, rightPoint.y, rightPoint.z));
    }
    
    //end the shape
    mesh.draw();
    
    
    //if we're using the camera, take it away
    if(usecamera){
        camera.end();
    }


}

void ofApp::keyPressed(int key){
    //hitting any key swaps the camera view
    usecamera = !usecamera;
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    //if we are using the camera, the mouse moving should rotate it around the whole sculpture
//    if(usecamera){
//        float rotateAmount = ofMap(ofGetMouseX(), 0, ofGetWidth(), 0, 360);
//        ofVec3f furthestPoint;
//        if (points.size() > 0) {
//            furthestPoint = points[0];
//        }
//        else
//        {
//            furthestPoint = ofVec3f(x, y, 0);
//        }
//        
//        ofVec3f directionToFurthestPoint = (furthestPoint - center);
//        ofVec3f directionToFurthestPointRotated = directionToFurthestPoint.rotated(rotateAmount, ofVec3f(0,1,0));
//        camera.setPosition(center + directionToFurthestPointRotated);
//        camera.lookAt(center);
//    }
//    //otherwise add points like before
//    else{
//        ofVec3f mousePoint(x,y,0);
//        points.push_back(mousePoint);
//    }
}


void ofApp::mousePressed(int x, int y, int button) {
    
    //calculate local mouse x,y in image
    int mx = x % w;
    int my = y % h;
    
//    get hue value on mouse position
    findHue = hue.getPixels()[my*w+mx];
    cout<< findHue <<endl;
    
}

//--------------------------------------------------------------
