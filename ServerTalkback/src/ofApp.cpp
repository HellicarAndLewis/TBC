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
    
    struct message {
        float normX;
        float normY;
        string name;
    };
    vector<message> messages;
    
  ofSetColor(255, 255, 255);
  for (map<ofxLibwebsockets::Connection*, client>::iterator mapIt = clientPositions->begin(); mapIt != clientPositions->end(); ++mapIt) {
    float radius = 10;
    string name = mapIt->second.name;
    ofVec2f position = mapIt->second.position * windowSize;

    ofDrawCircle(position, radius);
    ofDrawBitmapString(name, position - ofVec2f(-radius, -radius));
      message toSend = {position.x / windowSize.x, position.y / windowSize.y, name};
      messages.push_back(toSend);
//    ofVec2f normalized = ofVec2f(position.x / ofGetWidth(), position.y / ofGetHeight());
//    server.send(ofToString(normalized));
  }
    string toSend;
    for(int i = 0; i < messages.size(); i++)
    {
        toSend += ofToString(messages[i].normX) + " " + ofToString(messages[i].normY) + " " + ofToString(messages[i].name) + ",";
    }
    server.send(toSend);
    cout << toSend << endl;
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
