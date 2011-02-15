/*
 *  createController.cpp
 *  CreateRemote
 *
 *  Created by latrokles on 1/26/11.
 *  Copyright 2011 Samurai Hipppo Labs. All rights reserved.
 *
 */

#include "createController.h"

createController::createController(){
    
}

createController::~createController(){
}

void createController::setup(){
    centerX = ofGetWidth()/2;
    centerY = ofGetHeight()/2;
    speedFactor = 5000/160;         // will get rid of magical numbers later
    createModel.loadImage("images/2d_model_v3.png");
    leftWheel.set(centerX - OFFSET, centerY, 0);
    rightWheel.set(centerX + OFFSET, centerY, 0);
}

void createController::setCreateAddress(string destination_addr){
    netSender.Create();
    netSender.Connect(destination_addr.c_str(), 1337);
    netSender.SetNonBlocking(false);
    netSender.SetTimeoutSend(30);
    //printf("Connecting to: %s", destination_addr.c_str());
}

void createController::handleInputData(int x, int y){
    if (x < centerX) {
        leftWheel.y = y;
    }
    
    if (x > centerX) {
        rightWheel.y = y;
    }
    calculateVelocity();
}

void createController::resetPosition(int x){
    handleInputData(x, centerY);
}

void createController::calculateVelocity(){
    int leftDifference  = (centerY - leftWheel.y) * speedFactor;
    int rightDifference = (centerY - rightWheel.y) * speedFactor;
    
    string controlStr = "Left:" + ofToString(leftDifference, 0) + ":Right:" + ofToString(rightDifference, 0);
    sendControlInstruction(controlStr);
}

void createController::sendControlInstruction(string instruction){
    int sent = netSender.Send(instruction.c_str(), instruction.length());
    //printf("Instruction -- %s\nSize -- %d\n\n", instruction.c_str(), sent);
}

void createController::update(){    
}

void createController::draw(){
    ofPushMatrix();
    ofTranslate(centerX, centerY, 0);
    createModel.draw(-100, - 100, 200, 200);
    ofPopMatrix();
    ofSetColor(255, 255, 255, 150);
    ofEnableSmoothing();
    ofCircle(leftWheel.x, leftWheel.y , WHEEL_RADIUS);
    ofCircle(rightWheel.x, rightWheel.y, WHEEL_RADIUS);
    ofDisableSmoothing();
}