#pragma once

#include "ofMain.h"
#include "ofxiPhone.h"
#include "ofxiPhoneExtras.h"
#include "createController.h"

#define GUI_X_BOUND        40
#define NET_BUTTON_TOP      0
#define NET_BUTTON_BOTTOM  40

class testApp : public ofxiPhoneApp {
	
public:
	void setup();
	void update();
	void draw();
	void exit();
	
	void touchDown(ofTouchEventArgs &touch);
	void touchMoved(ofTouchEventArgs &touch);
	void touchUp(ofTouchEventArgs &touch);
	void touchDoubleTap(ofTouchEventArgs &touch);

	void lostFocus();
	void gotFocus();
	void gotMemoryWarning();
	void deviceOrientationChanged(int newOrientation);
    
    createController    controller;
    ofxiPhoneKeyboard*  keyboard;
    
    //-- gui buttons
    ofImage network_button;
    ofImage spin_button;
    ofImage sing_button;
};


