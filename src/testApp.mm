#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){	
	// register touch events
	ofRegisterTouchEvents(this);
	
	// initialize the accelerometer
	ofxAccelerometer.setup();
	
	//iPhoneAlerts will be sent to this.
	ofxiPhoneAlerts.addListener(this);
	
	//If you want a landscape oreintation 
	iPhoneSetOrientation(OFXIPHONE_ORIENTATION_LANDSCAPE_RIGHT);
	ofBackground(0,0,0);
    
    
    //-- gui stuff
    network_button.loadImage("images/connection_button_v2.png");
    
    keyboard = new ofxiPhoneKeyboard(40, 32, 320, 32);
    keyboard->setVisible(false);
    keyboard->setBgColor(255, 255, 255, 255);
    keyboard->setFontColor(0, 0, 0, 255);
    keyboard->setFontSize(26);
    
    controller.setup();
}

//--------------------------------------------------------------
void testApp::update(){
}

//--------------------------------------------------------------
void testApp::draw(){
    ofEnableAlphaBlending();
    network_button.draw(0, NET_BUTTON_TOP, 40, 40);
    controller.draw();
    ofDisableAlphaBlending();
}

//--------------------------------------------------------------
void testApp::exit(){

}

//--------------------------------------------------------------
void testApp::touchDown(ofTouchEventArgs &touch){
    if (touch.x > GUI_X_BOUND) {
        controller.handleInputData(touch.x, touch.y);
    } else {
        //-- handle gui buttons
        //-- network button
        if (touch.y > NET_BUTTON_TOP) {
            if (!keyboard->isKeyboardShowing()) {
                keyboard->openKeyboard();
                keyboard->setVisible(true);
            } else {
                keyboard->closeKeyboard();
                keyboard->setVisible(false);
                controller.setCreateAddress(keyboard->getText());
            }
        }
    }
}

//--------------------------------------------------------------
void testApp::touchMoved(ofTouchEventArgs &touch){
    touchDown(touch);

}

//--------------------------------------------------------------
void testApp::touchUp(ofTouchEventArgs &touch){
    if (touch.x > GUI_X_BOUND) {
        controller.resetPosition(touch.x);
    }
}

//--------------------------------------------------------------
void testApp::touchDoubleTap(ofTouchEventArgs &touch){

}

//--------------------------------------------------------------
void testApp::lostFocus(){

}

//--------------------------------------------------------------
void testApp::gotFocus(){

}

//--------------------------------------------------------------
void testApp::gotMemoryWarning(){

}

//--------------------------------------------------------------
void testApp::deviceOrientationChanged(int newOrientation){

}

