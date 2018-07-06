//
//  FlipText.cpp
//  textShadow
//
//  Created by cafe on 03/07/2018.
//

#include "FlipText.hpp"

void FlipText::init(string text, ofVec3f offset = ofVec3f(0, 0, 0)) {
    vector<ofTTFCharacter> characters = font->getStringAsPoints(text);
    ofRectangle rect = font->getStringBoundingBox(text, 0, 0);
    rotationYPos = offset.y-rect.getHeight()/2;
    // Go through all the characters
    for (int j = 0; j < characters.size(); j++) {
        // Get the outline of each character
        ofMesh inputMesh = characters[j].getTessellation();
        
        for (int i = 0; i < inputMesh.getNumVertices(); i++) {
            ofPoint vertex = inputMesh.getVertex(i);
            inputMesh.setVertex(i, ofPoint(vertex.x - rect.width / 2 + offset.x, -vertex.y - rect.height / 2 + offset.y, offset.z));
            inputMesh.addColor(color);
        }
        
        Triangulator::generateTriangulation(&inputMesh, &mesh);
    }
    
    theta.set("Theta", 0, 0, PI/2);
    
    active = false;
}

void FlipText::update() {
    if(active) {
        auto duration = 3.f; // three seconds
        auto now = ofGetElapsedTimef();
        auto endTime = initTime + duration;
        
        theta = ofxeasing::map_clamp(now, initTime, endTime, theta.getMin(), theta.getMax(), ofxeasing::elastic::easeOut);
    } else {
        auto duration = 1.f; // three seconds
        auto now = ofGetElapsedTimef();
        auto endTime = initTime + duration;
        
        theta = ofxeasing::map_clamp(now, initTime, endTime, theta.getMax(), theta.getMin(), ofxeasing::linear::easeIn);
    }
}

ofMesh FlipText::draw() {
//    ofMesh drawMesh = mesh;
    
//    ofSetColor(0, 255, 0);
    Line rotationLine;
    rotationLine.p1 = ofVec3f(-500, rotationYPos, 0);
    rotationLine.p2 = ofVec3f(500, rotationYPos + 0.0001, 0);
    
//    ofTranslate(0, rotationYPos);
//    ofRotate(theta);
//    ofTranslate(0, -rotationYPos);
    
    ofMesh drawMesh = mesh;
    
    for(int i = 0; i < mesh.getNumVertices(); i++) {
        ofVec3f v = mesh.getVertex(i);
        v = rotatePointAboutVector(theta, v, rotationLine.p1, rotationLine.p2);
        drawMesh.setVertex(i, v);
    }
    
    drawMesh.draw();
    
    return mesh;
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
