#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
    font.load("fonts/HeveticaBold.ttf", 100, true, true, true);
    
    ofColor frontColor = ofColor(255, 250, 240);
    
    ofSetBackgroundColor(frontColor);
    
    p.p = ofVec3f(0, 0, 0);
    p.n = ofVec3f(0, 0, 1);
    l.p1 = ofVec3f(100, 100, 100);
    l.p2 = ofVec3f(20, 20, 20);
    
    string settingsPath = "settings/settings.xml";
    
    gui.setup("Controls", settingsPath);
    gui.add(lightSource.set("Light Pos", ofVec3f(-300, -200, 140), ofVec3f(-1000, -1000, -1000), ofVec3f(1000, 1000, 1000)));
    gui.add(planeNormal.set("Plane Normal", ofVec3f(0, 0, 1), ofVec3f(-1, -1, -1), ofVec3f(1, 1, 1)));
    gui.add(theta.set("Angle", 0, 0, PI/2));
    gui.add(rotationYPos.set("Rotation Vec y", 0, -55, -50));

    gui.loadFromFile(settingsPath);
    
    cam.setPosition(-480, -402, 221);
    cam.lookAt(ofVec3f(0, 0, 0));
    
    initTime = 0;
    
    words.resize(14);
    
    for(int i = 0; i < words.size(); i++) {
        words[i].font = &font;
        words[i].color = frontColor;
    }
    
    int kerning = 100;
    int x = -500;
    
    int y = 200;
    
    words[0].init("H", ofVec3f(x, y, 0));
    x+=kerning;
    words[1].init("E", ofVec3f(x, y, 0));
    x+=kerning;
    words[2].init("L", ofVec3f(x, y, 0));
    x+=kerning;
    words[3].init("L", ofVec3f(x, y, 0));
    x+=kerning;
    words[4].init("I", ofVec3f(x, y, 0));
    x+=kerning;
    words[5].init("C", ofVec3f(x, y, 0));
    x+=kerning;
    words[6].init("A", ofVec3f(x, y, 0));
    x+=kerning;
    words[7].init("R", ofVec3f(x, y, 0));
    
    x = -200;
    y = 0;
    words[8].init("S", ofVec3f(x, y, 0));
    x+=kerning;
    words[9].init("T", ofVec3f(x, y, 0));
    x+=kerning;
    words[10].init("U", ofVec3f(x, y, 0));
    x+=kerning;
    words[11].init("D", ofVec3f(x, y, 0));
    x+=kerning;
    words[12].init("I", ofVec3f(x, y, 0));
    x+=kerning;
    words[13].init("O", ofVec3f(x, y, 0));

}

//--------------------------------------------------------------
void ofApp::update(){
    p.n = planeNormal;
    lightSource.set(ofVec3f(lightSource.get().x, lightSource.get().y, ofMap(sin(ofGetElapsedTimef()), -1.0, 1.0, 200, 250)));
    
    for(int i = 0; i < words.size(); i++) {
        words[i].update();
    }

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofEnableDepthTest();
    
    cam.begin();
    
    ofSetColor(255);
//    p.draw();
    
    ofSetColor(0);
    
    ofSetColor(255, 255, 0);
//    ofDrawSphere(lightSource, 10);
    
    for(int i = 0; i < words.size(); i++) {
        ofMesh m = words[i].draw();
        
        vector<ofVec3f> verts = m.getVertices();
        vector<ofVec3f> shadowPoints;
        
        ofMesh shadowMesh;
        for(int i = 0; i < verts.size(); i++) {
            Line newL;
            newL.p1 = verts[i] - lightSource;
            newL.p2 = verts[i];
            shadowPoints.push_back(planeLineIntersection(p, newL));
        }
        
        shadowMesh = m;
        for(int i = 0; i < m.getNumVertices(); i++) {
            shadowMesh.setVertex(i, shadowPoints[i]);
            shadowMesh.setColor(i, ofColor(0));
        }
        
        shadowMesh.draw();
        
    }
    
    ofSetColor(0, 0, 255);
    
    cam.end();
    
    ofDisableDepthTest();
    gui.draw();
}

//--------------------------------------------------------------
ofVec3f ofApp::planeLineIntersection(Plane p, Line l) {
    ofVec3f p3 = p.p;
    ofVec3f N = p.n;
    ofVec3f p1 = l.p1;
    ofVec3f p2 = l.p2;
    float denom = p.n.dot(p2 - p1);
    if(abs(denom) < 0.00001) {
//        cout<< "small dot!"<<endl;
        denom = (denom > 0) ? 0.00001 : -0.00001;
    }
    float u = p.n.dot(p3 - p1) / denom;
    
//    cout<<u<<endl;
    
//    if(abs(u) > 600) {
//        cout << "big u!" << endl;
//
//        u = (u > 0) ? 600 : -600;
//    }
    ofVec3f i = u*p2 + (1-u) * p1;
    return i;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == ' ') {
        for(int i = 0; i < words.size(); i++) {
            words[i].active = !words[i].active;
        }
        float now = ofGetElapsedTimef();
        float offset = 0.2f;
        float delay = 0.2f;
        for(int i = 0; i < words.size(); i++) {
            words[i].initTime = now+delay;
            delay += offset;
        }
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
