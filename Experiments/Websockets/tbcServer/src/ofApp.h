#pragma once

#include "ofMain.h"
#include "ofxLibwebsockets.h"

// how many past messages we want to keep
#define NUM_MESSAGES 30

class ofApp : public ofBaseApp {

struct client {
  std::string name;
  ofVec2f position;
    //added color field
    ofColor color;
    
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

  std::map<ofxLibwebsockets::Connection*, client> *clientPositions;
};
