//
//  AsyncMovieLoader.h
//  MovieGenerator
//
//  Created by Mitstuya.WATANABE on 2015/09/07.
//
//

#ifndef __MovieGenerator__AsyncMovieLoader__
#define __MovieGenerator__AsyncMovieLoader__

#include <stdio.h>

#endif /* defined(__MovieGenerator__AsyncMovieLoader__) */


#pragma once
#include "ofMain.h"
#include "ofxJSON.h"

class AsyncLoader : public ofBaseApp {
public:
    virtual ~AsyncLoader();
    AsyncLoader();
    
    void load(string url);
    void loadAsSavingFile(string url, string fileName);
    void loadInstagramImage();
    
    
    void urlResponse(ofHttpResponse &response);
    int processId;
    ofEvent<ofBuffer> LOAD_COMPLETE;
    ofEvent<void> LOAD_ERROR;
    ofImage bgImage;

protected:
    ofxJSONElement jsonData;
    vector <std::string> urlList;
    int loadCnt;
    std::string requestName;
    vector <std::string> captionList;
   // void notify(ofEvent<> event);
};

