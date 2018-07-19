//
//  FlipText.cpp
//  textShadow
//
//  Created by cafe on 03/07/2018.
//

#include "FlipText.hpp"

void FlipText::init(string _text, ofVec3f _offset = ofVec3f(0, 0, 0), float _delay = 0) {
    offset = _offset;
    delay = _delay;
    text = _text;
    vector<ofTTFCharacter> characters = font->getStringAsPoints(text);
    ofRectangle rect = font->getStringBoundingBox(text, 0, 0);
    // Go through all the characters
    for (int j = 0; j < characters.size(); j++) {
        // Get the outline of each character
        ofMesh inputMesh = characters[j].getTessellation();
        
        for (int i = 0; i < inputMesh.getNumVertices(); i++) {
            ofPoint vertex = inputMesh.getVertex(i);
            inputMesh.setVertex(i, ofPoint(vertex.x, -vertex.y, 0));
            inputMesh.addColor(ofColor(255, 255 ,255));
        }
        
        Triangulator::generateTriangulation(&inputMesh, &mesh);
    }
        
    theta = 0;
    thetaMax = PI/2;
    thetaMin = 0;
    
    active = false;
}

void FlipText::update(float x, float y) {
    if(active) {
        auto duration = 3.f; // three seconds
        auto now = ofGetElapsedTimef();
        auto endTime = initTime + duration;
        
        theta = ofxeasing::map_clamp(now, initTime, endTime, thetaMin, thetaMax, ofxeasing::elastic::easeOut);
    } else {
        auto duration = 1.f; // three seconds
        auto now = ofGetElapsedTimef();
        auto endTime = initTime + duration;
        
        theta = ofxeasing::map_clamp(now, initTime, endTime, thetaMax, thetaMin, ofxeasing::linear::easeIn);
    }
    
    
    if(y + offset.y > FLIP_TOP) {
        if(active)
            initTime = ofGetElapsedTimef() + delay;
        active = false;
    }
    else if(y + offset.y > FLIP_BOTTOM) {
        if(!active)
            initTime = ofGetElapsedTimef() + delay;
        active = true;
    }
}

void FlipText::setActive(bool _a) {
    initTime = ofGetElapsedTimef() + delay;
    active = _a;
}

ofMatrix4x4 FlipText::draw(float x, float y) {
    
    ofPushMatrix();
    Line rotationLine;
    rotationLine.p1 = ofVec3f(-500, 0, 0);
    rotationLine.p2 = ofVec3f(500, 0 + 0.0001, 0);
    
    ofTranslate(x, y);
    ofTranslate(offset);
    ofRotate(theta * 180 / PI, 1, 0, 0);
    ofSetColor(0, 255, 0);
    mesh.draw();
    
    ofPopMatrix();
    
    return getRotationMatrix(theta, rotationLine.p1, rotationLine.p2);
}

ofMatrix4x4 FlipText::getRotationMatrix(float theta, ofVec3f p1, ofVec3f p2) {
    ofVec3f l = p2 - p1;
    ofVec3f u = l.normalize();
    float a = u.x;
    float b = u.y;
    float c = u.z;
    float d = sqrt(b*b + c*c);
    ofMatrix4x4 T = ofMatrix4x4(1, 0, 0, -p1.x, 0, 1, 0, -p1.y, 0, 0, 1, -p1.z, 0, 0, 0, 1);
    ofMatrix4x4 Rx = ofMatrix4x4(1, 0, 0, 0, 0, c/d, -b/d, 0, 0, b/d, c/d, 0, 0, 0, 0, 1);
    ofMatrix4x4 Ry = ofMatrix4x4(d, 0, -a, 0, 0, 1, 0, 0, a, 0, d, 0, 0, 0, 0, 1);
    ofMatrix4x4 Rz = ofMatrix4x4(cos(theta), -sin(theta), 0, 0, sin(theta), cos(theta), 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
    
    ofMatrix4x4 Pt = T.getInverse() * Rx.getInverse() * Ry.getInverse() * Rz * Ry * Rx * T;//* ofVec4f(p.x, p.y, p.z, 1);
    return Pt;
}

ofVec3f FlipText::rotatePointAboutVector(float theta, ofVec3f p, ofVec3f p1, ofVec3f p2) {
    ofVec3f l = p2 - p1;
    ofVec3f u = l.normalize();
    float a = u.x;
    float b = u.y;
    float c = u.z;
    float d = sqrt(b*b + c*c);
    ofMatrix4x4 T = ofMatrix4x4(1, 0, 0, -p1.x, 0, 1, 0, -p1.y, 0, 0, 1, -p1.z, 0, 0, 0, 1);
    ofMatrix4x4 Rx = ofMatrix4x4(1, 0, 0, 0, 0, c/d, -b/d, 0, 0, b/d, c/d, 0, 0, 0, 0, 1);
    ofMatrix4x4 Ry = ofMatrix4x4(d, 0, -a, 0, 0, 1, 0, 0, a, 0, d, 0, 0, 0, 0, 1);
    ofMatrix4x4 Rz = ofMatrix4x4(cos(theta), -sin(theta), 0, 0, sin(theta), cos(theta), 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
    
    ofVec4f Pt = T.getInverse() * Rx.getInverse() * Ry.getInverse() * Rz * Ry * Rx * T * ofVec4f(p.x, p.y, p.z, 1);

    return ofVec3f(Pt.x, Pt.y, Pt.z);
}
