#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofxLibwebsockets::ServerOptions options = ofxLibwebsockets::defaultServerOptions();
    options.port = 9090;
    options.bUseSSL = false;
    serverSetup = server.setup(options);
    server.addListener(this);
    
    ofBackground(0);
    ofSetFrameRate(60);
    
   clientPositions = new map<ofxLibwebsockets::Connection*, client>();

}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofVec2f windowSize = ofGetWindowSize();
    ofSetColor(255, 255, 255);
    for(map<ofxLibwebsockets::Connection*, client>::iterator mapIt = clientPositions->begin(); mapIt != clientPositions->end(); ++mapIt)
    {
        float radius = 10;
        std::string name = mapIt->second.name;
        ofVec2f position = mapIt->second.position * windowSize;
        ofSetColor(mapIt->second.color);
        ofDrawCircle(position, radius);
        ofDrawBitmapString(name, position - ofVec2f(-radius, -radius));
    }

}

void ofApp::onConnect(ofxLibwebsockets::Event &args) {
    ofLogNotice() << "onConnect";
}

//--------------------------------------------------------------
void ofApp::onOpen(ofxLibwebsockets::Event &args) {
    ofLogNotice() << "onOpen";
}

//--------------------------------------------------------------
void ofApp::onClose(ofxLibwebsockets::Event &args) {
    ofLogNotice() << "onClose";
    
    clientPositions->erase(&args.conn);
}

//--------------------------------------------------------------
void ofApp::onIdle(ofxLibwebsockets::Event &args) {
    ofLogNotice() << "onIdle";
}

//--------------------------------------------------------------
void ofApp::onMessage(ofxLibwebsockets::Event &args) {
    ofLogNotice() << "onMessage: " << args.message;
    
    ofxJSONElement tmpJSON;
    bool parsingSuccessful = tmpJSON.parse(args.message);
    
    if(parsingSuccessful)
    {
        client tmpClient;
        tmpClient.name = tmpJSON["name"].asString();
        tmpClient.position.x = tmpJSON["x"].asFloat();
        tmpClient.position.y = tmpJSON["y"].asFloat();
        tmpClient.color.setHex(tmpJSON["color"].asInt());
        tmpClient.idNum = tmpJSON["id"].asInt();
        cout << tmpJSON["color"].asInt() << endl;
        if(tmpJSON["clicked"].asBool())
        {
            tmpClient.color = ofColor(ofRandom(255), ofRandom(255), ofRandom(255));
        }
        
        (*clientPositions)[&args.conn] = tmpClient;
    }
    
    ofxJSONElement message;
    int i = 0;
    for(map<ofxLibwebsockets::Connection*, client>::iterator mapIt = clientPositions->begin(); mapIt != clientPositions->end(); ++mapIt)
    {
        message[i]["name"] = mapIt->second.name;
        message[i]["id"] = mapIt->second.idNum;
        message[i]["x"] = mapIt->second.position.x;
        message[i]["y"] = mapIt->second.position.y;
        message[i]["color"] = mapIt->second.color.getHex();
        i++;
    }
    server.send(message.getRawString());
}

//--------------------------------------------------------------
void ofApp::onBroadcast(ofxLibwebsockets::Event &args) {
    ofLogNotice() << "onBroadcast: " << args.message;
}
