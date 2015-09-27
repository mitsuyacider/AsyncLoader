#include "ofApp.h"

void ofApp::setup(){
    ofAddListener(loader.LOAD_COMPLETE, this, &ofApp::loadComplete);
//    loader.load("http://www.openframeworks.cc/images/ofw-logo.png");
    loader.loadInstagramImage();
    isLoaded = false;
}
void ofApp::update(){
    
}
void ofApp::draw(){
    if (isLoaded) image.draw(0, 0);
}

void ofApp::loadComplete(ofBuffer &buffer) {
    cout << "load complete" << endl;
    image.loadImage(buffer);
    isLoaded = true;
    
    // command line sample
    std::stringstream cmd;
    string word = "load complete";
    cmd << "say -v kyoko " << word;
    system(cmd.str().c_str());
}