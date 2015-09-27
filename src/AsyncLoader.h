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

class AsyncLoader : public ofBaseApp {
public:
    virtual ~AsyncLoader();
    AsyncLoader();
    
    void load(string url);
    void loadAsSavingFile(string url, string fileName);
    void urlResponse(ofHttpResponse &response);
    int processId;
    ofEvent<ofBuffer> LOAD_COMPLETE;
    ofEvent<void> LOAD_ERROR;
};

