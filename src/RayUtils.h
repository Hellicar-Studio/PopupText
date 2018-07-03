//
//  RayUtils.h
//  textShadow
//
//  Created by cafe on 03/07/2018.
//

#ifndef RayUtils_h
#define RayUtils_h

// Define a pair of ray utilities

#include "ofMain.h"

struct Plane {
    ofVec3f p;
    ofVec3f n;
    
    void draw() {
        ofPushStyle();
        ofEnableDepthTest();
        ofSetRectMode(OF_RECTMODE_CENTER);
        ofSetColor(255, 0, 0);
        ofNoFill();
        ofDrawPlane(p.x, p.y, p.z, 1000, 1000);
        ofDrawLine(p, p + n*10);
        ofPopStyle();
    }
};

struct Line {
    ofVec3f p1;
    ofVec3f p2;
    void draw() {
        ofPushStyle();
        ofEnableDepthTest();
        ofSetColor(0, 255, 0);
        ofDrawLine(p1, p2);
        ofPopStyle();
    }
};


#endif /* RayUtils_h */
