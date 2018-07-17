//
//  FlipText.hpp
//  textShadow
//
//  Created by cafe on 03/07/2018.
//

#ifndef FlipText_hpp
#define FlipText_hpp

#define FLIP_BOTTOM 0
#define FLIP_TOP 500

#include "ofMain.h"
#include "ofxEasing.h"
#include "Triangulator.h"
#include "RayUtils.h"

class FlipText {
public:
    void init(string _text, ofVec3f _offset, float _delay);
    void update();
    ofMatrix4x4 draw(float x, float y);
    ofVec3f rotatePointAboutVector(float theta, ofVec3f p, ofVec3f p1, ofVec3f p2);
    ofMatrix4x4 getRotationMatrix(float theta, ofVec3f p1, ofVec3f p2);
    
    float delay;
    
    ofVec3f offset;
    
    float initTime;
    
    ofMesh mesh;
    
    ofTrueTypeFont* font;
    string text;
        
    ofParameter<float> theta;
    float rotationYPos;
    
    ofColor color = ofColor(255);
        
    bool active;
};

#endif /* FlipText_hpp */
