#pragma once

#include "ofMain.h"
#include "AsyncLoader.h"

class ofApp : public ofBaseApp {

	public:
		void setup();
		void update();
		void draw();
    
        void loadComplete(ofBuffer &buffer);
        AsyncLoader loader;
    ofImage image;
    bool isLoaded;
};
