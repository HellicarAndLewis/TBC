#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    stream.initGrabber(ofGetWidth(), ofGetHeight(), true);
    image.allocate(ofGetWidth(), ofGetHeight(), OF_IMAGE_COLOR);
    for(int i = 0; i < 100; i++)
    {
        pillars.push_back(Pillar(40*i + 1, ofGetHeight()/2, 20, ofRandom(200)));
    }
    //ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::update(){
    stream.update();
    if(stream.isFrameNew())
    {
        image.setFromPixels(stream.getPixels(), ofGetWidth(), ofGetHeight(), OF_IMAGE_COLOR);
        image.mirror(false, true);
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(255);
    image.draw(0, 0);
    for(int i = 0; i < pillars.size(); i++)
    {
        pillars[i].display();
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
