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
    requestName = "";
    processId = ofLoadURLAsync(url, requestName);
}

void AsyncLoader::loadAsSavingFile(string url, string fileName) {
    requestName = fileName;
    processId = ofSaveURLAsync(url, requestName);
}

void AsyncLoader::loadInstagramImage() {
    // initialize
    loadCnt = 0;
    urlList.clear();
    requestName = "list_instagram_image";
    ofLoadURLAsync("https://api.instagram.com/v1/tags/ずーしーほっきー/media/recent?access_token=&client_id=c8fc409e7c0d44539aa18f91f4208833&count=10", requestName);
}

void AsyncLoader::urlResponse(ofHttpResponse &response) {
    if (response.status == 200 && response.request.name == requestName) {
        if (requestName == "list_instagram_image") {
            
            // stock the list
            jsonData.parse(response.data.getText());
            
            std::size_t length = jsonData["data"].size();
            
            if (length > 0) {
                // change the request name to loading image
                requestName = "load_image";
                
                for (int i = 0; i < length; i++) {
                    std::string url = jsonData["data"][i]["images"]["standard_resolution"]["url"].asString();
                    url.erase(4, 1);
                    printf("\nimage %s", url.c_str());
                    urlList.push_back(url);
                    
                    // load image
                    // TODE: 既に保存してある画像はロードしないように修正する
                    ofLoadURLAsync(url, requestName);
                }
            }
        } else if (requestName == "load_image") {
            ofImage iii;
            iii.loadImage(response.data);
            
            ofFbo fff;
            fff.allocate(1280, 720, GL_RGB);
            
            // NOTE: urlからファイル名を取得する
            std::string fileName = response.request.url;
            fileName.erase(0, fileName.find_last_of("/", fileName.size()) + 1);
            
            // 保存用の画像をバッファー内に描画する
            fff.begin();
            ofClear(0, 0, 0, 0);
            ofBackground(0);
            iii.draw(0, 0);
            fff.end();
            
            // バッファー内にあるピクセルデータを画像ファイルとして保存
            ofPixels pixels;
            ofImage i;
            fff.readToPixels(pixels);
            i.setFromPixels(pixels);
            i.saveImage("instagram/" + fileName);
            
            loadCnt++;
            if (loadCnt == urlList.size()) {
                // complete load image from urlList
                ofNotifyEvent(LOAD_COMPLETE, response.data);
            }
        } else {
            // notificate response data to main
            // NOTE: response data is json
            //       @param file name
            //       @param effect type
            ofNotifyEvent(LOAD_COMPLETE, response.data);
        }
    } else {
        ofStopURLLoader();
        ofRemoveURLRequest(processId);
        ofNotifyEvent(LOAD_ERROR);
    }
//    ofStopURLLoader();
//    ofRemoveURLRequest(processId);
}
