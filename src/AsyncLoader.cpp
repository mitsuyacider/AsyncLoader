//
//  AsyncLoader.cpp
//  MovieGenerator
//
//  Created by Mitstuya.WATANABE on 2015/09/07.
//
//

#include "AsyncLoader.h"

AsyncLoader::~AsyncLoader() {
    ofStopURLLoader();
    ofRemoveAllURLRequests();
    ofRemoveListener(ofURLResponseEvent(), this, &AsyncLoader::urlResponse);
}

AsyncLoader::AsyncLoader() {
    processId = 0;
    ofRegisterURLNotification(this);
    ofAddListener(ofURLResponseEvent(), this, &AsyncLoader::urlResponse);
}

void AsyncLoader::load(string url) {
    processId = ofLoadURLAsync(url);
}

void AsyncLoader::loadAsSavingFile(string url, string fileName) {
    processId = ofSaveURLAsync(url, fileName);
}

void AsyncLoader::urlResponse(ofHttpResponse &response) {
    if (response.status == 200) {
        // notificate response data to main
        // NOTE: response data is json
        //       @param file name
        //       @param effect type
        ofNotifyEvent(LOAD_COMPLETE, response.data);
    } else {
        ofStopURLLoader();
        ofRemoveURLRequest(processId);
        ofNotifyEvent(LOAD_ERROR);
    }
//    ofStopURLLoader();
//    ofRemoveURLRequest(processId);
}