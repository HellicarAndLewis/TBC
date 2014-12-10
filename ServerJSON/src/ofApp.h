#pragma once

#include "ofMain.h"
#include "ofxJSON.h"
#include "ofxLibwebsockets.h"

class ofApp : public ofBaseApp{
    
struct client {
    std::string name;
    ofVec2f position;
};
    
public:
    void setup();
    void update();
    void draw();
    
    void onConnect(ofxLibwebsockets::Event& args);
    void onOpen(ofxLibwebsockets::Event& args);
    void onClose(ofxLibwebsockets::Event& args);
    void onIdle(ofxLibwebsockets::Event& args);
    void onMessage(ofxLibwebsockets::Event& args);
    void onBroadcast(ofxLibwebsockets::Event& args);
    
    ofxLibwebsockets::Server server;
    bool serverSetup;
    
    std::map<ofxLibwebsockets::Connection*, client> * clientPositions;
};
