#include "ofApp.h"

void ofApp::setup() {
  ofxLibwebsockets::ServerOptions options = ofxLibwebsockets::defaultServerOptions();

  options.port = 9090;
  options.bUseSSL = false;
  serverSetup = server.setup(options);
  
  // this adds your app as a listener for the server
  server.addListener(this);
  
  ofBackground(0);
  ofSetFrameRate(60);

  clientPositions = new map<ofxLibwebsockets::Connection*, client>();
}

void ofApp::update() {
    
}

void ofApp::draw() {
  ofVec2f windowSize = ofGetWindowSize();

  ofSetColor(255, 255, 255);
  for (map<ofxLibwebsockets::Connection*, client>::iterator mapIt = clientPositions->begin(); mapIt != clientPositions->end(); ++mapIt) {
    float radius = 10;
    string name = mapIt->second.name;
      ofVec2f position = mapIt->second.position * windowSize;

    ofCircle(position, radius);
    ofDrawBitmapString(name, position - ofVec2f(-radius, -radius));
  }
}

void ofApp::onConnect(ofxLibwebsockets::Event &args) {
  ofLogNotice() << "onConnect";
}

void ofApp::onOpen(ofxLibwebsockets::Event &args) {
  ofLogNotice() << "onOpen";
}

void ofApp::onClose(ofxLibwebsockets::Event &args) {
  ofLogNotice() << "onClose";

  clientPositions->erase(&args.conn);
}

void ofApp::onIdle(ofxLibwebsockets::Event &args) {
  ofLogNotice() << "onIdle";
}

void ofApp::onMessage(ofxLibwebsockets::Event &args) {
  ofLogNotice() << "onMessage: " << args.message;

  vector<string> splitted = ofSplitString(args.message, ",");

  client tmpClient;
  tmpClient.name = splitted[0];
  tmpClient.position = ofVec2f(ofToFloat(splitted[1]), ofToFloat(splitted[2]));

  (*clientPositions)[&args.conn] = tmpClient;
}

void ofApp::onBroadcast(ofxLibwebsockets::Event &args) {
  ofLogNotice() << "onBroadcast: " << args.message;
}
