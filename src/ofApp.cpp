#include "ofApp.h"

string toUpperCase ( string str )
{
    string strUpper = "";
    
    for( int i=0; i<str.length(); i++ )
    {
        strUpper += toupper( str[ i ] );
    }
    
    return strUpper;
}

const string Xanadu = "In Xanadu did Kubla Khan\nA stately pleasure dome decree:\nWhere Alph, the sacred river, ran\nThrough caverns measureless to man\nDown to a sunless sea.\nSo twice five miles of fertile ground\nWith walls and towers were girdled round:\nAnd there were gardens bright with sinuous rills,\nWhere blossomed many an incense-bearing tree;\nAnd here were forests ancient as the hills,\nEnfolding sunny spots of greenery.";

const string Slough = "Come friendly bombs and fall on Slough!\nIt isn't fit for humans now,\nThere isn't grass to graze a cow.\nSwarm over, Death!";

const string HS = "Hellicar\n     Studio";

const string theRaven = "Once upon a midnight dreary, while I pondered, weak and weary,\nOver many a quaint and curious volume of forgotten lore-\nWhile I nodded, nearly napping, suddenly there came a tapping,\nAs of some one gently rapping, rapping at my chamber door.\n\"’Tis some visitor,\" I muttered, \"tapping at my chamber door—\nOnly this and nothing more.\"";

//--------------------------------------------------------------
void ofApp::setup(){
    font.load("fonts/HeveticaBold.ttf", 100, true, true, true);
    
    frontColor = ofColor(255, 250, 240);
    
    ofSetBackgroundColor(frontColor);
    
    p.p = ofVec3f(0, 0, 0);
    p.n = ofVec3f(0, 0, 1);
    l.p1 = ofVec3f(100, 100, 100);
    l.p2 = ofVec3f(20, 20, 20);
    
    string settingsPath = "settings/settings.xml";
    
    gui.setup("Controls", settingsPath);
    gui.add(lightSource.set("Light Pos", ofVec3f(-300, -200, 140), ofVec3f(-1000, -1000, -1000), ofVec3f(1000, 1000, 1000)));
    gui.add(planeNormal.set("Plane Normal", ofVec3f(0, 0, 1), ofVec3f(-1, -1, -1), ofVec3f(1, 1, 1)));

    gui.loadFromFile(settingsPath);
    
    cam.setPosition(-480, -402, 221);
    cam.lookAt(ofVec3f(0, 0, 0));
            
    for(int i = 0; i < words.size(); i++) {
        words[i].font = &font;
        words[i].color = ofColor(127);
    }
    
    shadow.load("shaders/shadow");
    
    float x = -500;
    float y = 200;
    float yGap = -200;
    addVerse(toUpperCase(theRaven), ofVec3f(x, y, 0));
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
    
    for(int i = 0; i < words.size(); i++) {
        words[i].draw();
        
//        shadow.begin();
//        shadow.setUniform3f("planeCenter", p.p);
//        shadow.setUniform3f("planeNormal", p.n);
//        shadow.setUniform3f("lightPos", lightSource.get());
//        ofSetColor(255);
//        words[i].draw();
//        shadow.end();
    }
        
    cam.end();
    
    ofDisableDepthTest();
    gui.draw();
    
    ofDrawBitmapStringHighlight(ofToString(ofGetFrameRate()), ofGetWidth()-100, ofGetHeight()-10);
}

//--------------------------------------------------------------
void ofApp::addVerse(string text, ofVec3f offset) {
    vector<string> lines = ofSplitString(text, "\n");
    for(int i = 0; i < lines.size(); i++) {
        addLine(lines[i], offset);
        offset.y += -200;
    }
//    float kerning = 100;
//    for(int i = 0; i < text.size(); i++) {
//        FlipText word;
//        word.font = &font;
//        word.color = frontColor;
//        word.init(string(1, text[i]), offset);
//        offset.x += kerning;
//        words.push_back(word);
//    }
}

//--------------------------------------------------------------
void ofApp::addLine(string text, ofVec3f offset) {
    float kerning = 100;
    for(int i = 0; i < text.size(); i++) {
        FlipText word;
        word.font = &font;
        word.color = frontColor;
        word.init(string(1, text[i]), offset);
        offset.x += kerning;
        words.push_back(word);
    }
}

//--------------------------------------------------------------
ofVec3f ofApp::planeLineIntersection(Plane p, Line l) {
    ofVec3f p3 = p.p;
    ofVec3f N = p.n;
    ofVec3f p1 = l.p1;
    ofVec3f p2 = l.p2;
    float denom = p.n.dot(p2 - p1);
    if(abs(denom) < 0.00001) {
        denom = (denom > 0) ? 0.00001 : -0.00001;
    }
    float u = p.n.dot(p3 - p1) / denom;
    
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
