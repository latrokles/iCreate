/*
 *  createController.h
 *  CreateRemote
 *
 *  Created by latrokles on 1/26/11.
 *  Copyright 2011 Samurai Hipppo Labs. All rights reserved.
 *
 */

#ifndef __CREATE_CONTROLLER__
#define __CREATE_CONTROLLER__

#define OFFSET        100
#define WHEEL_RADIUS   30
#define UPPER_LIMIT    20
#define LOWER_LIMIT   300

#include "ofMain.h"
#include "ofxNetwork.h"


class createController {
public:
    createController();
    ~createController();
    
    void setup();
    void setCreateAddress(string destination_addr);
    void handleInputData(int x, int y);
    void resetPosition(int x);
    void calculateVelocity();
    void sendControlInstruction(string instruction);
    void update();
    void draw();
private:
    //-- representation
    ofImage     createModel;
    
    //-- wheels
    int         centerX;
    int         centerY;
    ofPoint     rightWheel;
    ofPoint     leftWheel;
    
    //-- speed control
    // the create robot can take velocity values from -5000 to 5000,
    // the iphone screen is 320 pixels high (in landscape mode), which
    // translates in 160 positions for forward and backward directions.
    // this value will help with the mapping of the velocity values
    int speedFactor;        
    
    //-- network communications
    ofxUDPManager netSender;
};
#endif