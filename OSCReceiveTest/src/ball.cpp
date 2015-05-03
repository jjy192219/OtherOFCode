
#include "ball.h"

void Ball::setup(float mX, float mY){
    
    //define x and y coordinates
    x = mX;
    y = mY;
    
    //set color to random
    color = ofColor(ofRandom(255), ofRandom(255), ofRandom(255));
    
    //set velocity to random
    xVel = ofRandom(-5, 5);
    yVel = ofRandom(-5, 5);
    
    
};

void Ball::update(){
    
    
    //move ball
    x += xVel;
    y += yVel;
    
    //add ball bounce
    
    if(x >= ofGetWidth()){
        xVel *= -1;
        //cout <<"bounce off the right side"<< endl;
        
    }
    
    if(x <= 0){
        x = 0;
        xVel *= -1;
        //cout <<"bounce off the left side"<< endl;
        
    }
    
    if(y >= ofGetHeight()){
        y = ofGetHeight();
        yVel *= -1;
        //cout <<"bounce off the bottom"<< endl;
        
    }
    
    if(y <= 0){
        y = 0;
        yVel *= -1;
        //cout <<"bounce off the bottom"<< endl;
        
    }
    
    
};

void Ball::draw(){
    
    //set colors and draw balls
    
    ofSetColor(color);
    ofCircle(x, y, 5);
    
    
};
