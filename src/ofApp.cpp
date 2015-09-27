#include "ofApp.h"

void ofApp::setup(){
    ofAddListener(loader.LOAD_COMPLETE, this, &ofApp::loadComplete);
    loader.load("http://www.openframeworks.cc/images/ofw-logo.png");
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
    string word = "画像のロードが完了しました。ロードした画像を表示します。";
    cmd << "say -v kyoko " << word;
    system(cmd.str().c_str());
}