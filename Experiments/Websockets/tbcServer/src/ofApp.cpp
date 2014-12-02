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
    //struct for sending relevant data back to the client (not really necessary as it turned out)
    struct message {
        float normX;
        float normY;
        string name;
    };
    //Vector of messages to be populated and sent to the client
    vector<message> messages;
    
  ofSetColor(255, 255, 255);
  for (map<ofxLibwebsockets::Connection*, client>::iterator mapIt = clientPositions->begin(); mapIt != clientPositions->end(); ++mapIt) {
    float radius = 10;
    string name = mapIt->second.name;
    ofVec2f position = mapIt->second.position * windowSize;
      //set color to client color value
      ofColor color = mapIt->second.color;
      ofSetColor(color);
    ofDrawCircle(position, radius);
      ofSetColor(255, 255, 255);

    ofDrawBitmapString(name, position - ofVec2f(-radius, -radius));
      //populate messages vector with location information about each client
      message relLoc = {position.x / windowSize.x, position.y / windowSize.y, name};
      messages.push_back(relLoc);
  }
    //generate string to be sent to the client (comma separated messages with " " separated fields
    string toSend;
    for(int i = 0; i < messages.size(); i++)
    {
        toSend += ofToString(messages[i].normX) + " " + ofToString(messages[i].normY) + " " + ofToString(messages[i].name) + ",";
    }
    //send strings to the server
    server.send(toSend);
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
    //check if we've moved or clicked
    if(splitted[0] == "moved")
    {
        client tmpClient;
        tmpClient.name = splitted[1];
        tmpClient.position = ofVec2f(ofToFloat(splitted[2]), ofToFloat(splitted[3]));

        (*clientPositions)[&args.conn] = tmpClient;
    }
    else if(splitted[0] == "clicked")
    {
        //if we've clicked change the color toa  random color
        (*clientPositions)[&args.conn].color = ofColor(ofRandom(0, 255), ofRandom(0, 255), ofRandom(0, 255));
    }
}

void ofApp::onBroadcast(ofxLibwebsockets::Event &args) {
  ofLogNotice() << "onBroadcast: " << args.message;
}
