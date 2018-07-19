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

const string HS = "Hellicar\n     Studio";

const string theRaven = "Once upon a midnight dreary, while I pondered, weak and weary,\nOver many a quaint and curious volume of forgotten lore-\nWhile I nodded, nearly napping, suddenly there came a tapping,\nAs of some one gently rapping, rapping at my chamber door.\n\"’Tis some visitor,\" I muttered, \"tapping at my chamber door—\nOnly this and nothing more.\"";

const string allMyPeople = "All My People\n\nJames Massiah\n\nAll these people\nAll their opinions\nAll their politics\nAll their shit\nAll the places that they live\nAll their palaces\nAll their pads\nAll their mansions and their parties\nAll their flats\nAll their hives\nAll their lows\nAll their highs\nAll their health\nAll their yoga and Pilates\nAll their preciousness\nAnd stretching\nAnd their aching\nAnd their pain\n\nAll their punches\nNeed more sugar\nAll their churches\nNeed more Satan\nAll their virgins\nNeed more laying\nAll their idols\nNeed more slaying\n\nTheir religions\nAnd their myths\nAll their children\nAll their kids\nAnd their choices\nAnd their choppers\nAll their roads\nNeed more lanes\n\nAll their babies need new names\nAnd their planet, a new sun\nAll their gangsters need new guns\nAnd I’ll be shot through every one\n\n";

//--------------------------------------------------------------
void ofApp::setup(){
    font.load("fonts/HeveticaBold.ttf", 100, true, true, true);
    
    frontColor = ofColor(255, 0, 0);
    
    ofSetBackgroundColor(frontColor);
    
    string settingsPath = "settings/settings.xml";
    
    gui.setup("Controls", settingsPath);
    gui.add(lightSource.set("Light Pos", ofVec3f(-300, -200, 140), ofVec3f(-1000, -1000, -1000), ofVec3f(1000, 1000, 1000)));
    gui.add(planeNormal.set("Plane Normal", ofVec3f(0, 0, 1), ofVec3f(-1, -1, -1), ofVec3f(1, 1, 1)));
    gui.add(c1.set("Color 1", ofColor(255)));
    gui.add(c2.set("Color 2", ofColor(127)));

    gui.loadFromFile(settingsPath);
    
    Slough.push_back("Come friendly bombs and fall on Slough!");
    Slough.push_back("It isn't fit for humans now,");
    Slough.push_back("There isn't grass to graze a cow.");
    Slough.push_back("Swarm over, Death!");
    
//    cam.setPosition(-480, -402, 221);
    
    shadow.load("shaders/shadow");
    
    gradient.load("shaders/gradient");
    
    slide = -1000;
    
    if(colorSettings.loadFile("settings/colorSettings.xml") ) {
        int numSavedColors = colorSettings.getNumTags("color");
        for(int i = 0; i < numSavedColors-1; i+=2) {
            ofColor c1;
            ofColor c2;
            colorSettings.pushTag("color", i);
            c1.r = colorSettings.getValue("R", 0.0);
            c1.g = colorSettings.getValue("G", 0.0);
            c1.b = colorSettings.getValue("B", 0.0);
            colorSettings.popTag();

            colorSettings.pushTag("color", i+1);
            c2.r = colorSettings.getValue("R", 0.0);
            c2.g = colorSettings.getValue("G", 0.0);
            c2.b = colorSettings.getValue("B", 0.0);
            colorSettings.popTag();

            pair<ofColor, ofColor> c = make_pair(c1, c2);
            
            colorPairs.push_back(c);
        }
    } else {
        colorPairs.push_back(make_pair(c1.get(), c2.get()));
    }
    
    if(cameraSettings.loadFile("settings/cameraSettings.xml") ) {
        int numSavedPositions = cameraSettings.getNumTags("position");
        for(int i = 0; i < numSavedPositions; i++) {
            ofVec3f pos;
            ofVec3f upDir;
            ofVec3f lookAt;
            cameraSettings.pushTag("position", i);
            pos.x = cameraSettings.getValue("X", 0.0);
            pos.y = cameraSettings.getValue("Y", 0.0);
            pos.z = cameraSettings.getValue("Z", 0.0);
            cameraSettings.popTag();
            cameraSettings.pushTag("upDir", i);
            upDir.x = cameraSettings.getValue("X", 0.0);
            upDir.y = cameraSettings.getValue("Y", 0.0);
            upDir.z = cameraSettings.getValue("Z", 0.0);
            cameraSettings.popTag();
            cameraSettings.pushTag("LookAt", i);
            lookAt.x = cameraSettings.getValue("X", 0.0);
            lookAt.y = cameraSettings.getValue("Y", 0.0);
            lookAt.z = cameraSettings.getValue("Z", 0.0);
            cameraSettings.popTag();
            
            cout<<lookAt<<endl;
            
            camPositions.push_back(pos);
            camUpVectors.push_back(upDir);
            camLookAts.push_back(lookAt);
        }
    } else {
        ofLogError("No Camera Settings File Found");
    }
    
    buffer.allocate(ofGetWidth(), ofGetHeight());
    buffer.getTexture().getTextureData().bFlipTexture = false;
    

    cam.setPosition(ofVec3f(0, 0, 1000));
    cam.lookAt(ofVec3f(0, 0, -1), ofVec3f(0, 1, 0));
    
    camPosition = cam.getPosition();
    camUpVector = cam.getUpDir();
    camLookAt = cam.getLookAtDir();
    
    showGui = false;
}

//--------------------------------------------------------------
void ofApp::update(){
    p.n = planeNormal;
    
    if(words.size() == 0) {
        float x = -2000;
        float y = 1000;
        ofVec3f offset = ofVec3f(x, y, 0.01);
        ofVec2f size = addVerse(toUpperCase(allMyPeople), offset);
        for(int i = 0; i < words.size(); i++) {
            cout<<words[i].text;
        }
    }
    
    lightSource.set(ofVec3f(lightSource.get().x, lightSource.get().y, ofMap(sin(ofGetElapsedTimef()), -1.0, 1.0, 200, 250)));

    slide += 3;
    
    if(slide > 8800) {
        slide = -1000;
    }
    
    for(int i = 0; i < words.size(); i++) {
        words[i].update(0, slide);
    }
    
    camPosition.interpolate(camPositions[camIndex], 0.1);
    camLookAt.interpolate(camLookAts[camIndex], 0.1);
    camUpVector.interpolate(camUpVectors[camIndex], 0.1);
    
    ofColor c1New = c1.get();
    ofColor c2New = c2.get();
    c1.set(c1New.lerp(colorPairs[colorIndex].first, 0.1));
    c2.set(c2New.lerp(colorPairs[colorIndex].second, 0.1));

    cam.setPosition(camPosition);
    cam.lookAt(camLookAt, camUpVector);

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofEnableDepthTest();
    buffer.begin();
    ofClear(0, 0, 0, 0);
    cam.begin();
    ofBackground(frontColor);
    
    ofPushMatrix();
    int num = 0;
    for(int i = 0; i < words.size(); i++) {
//        p.p.y = slide;
        ofMatrix4x4 m = words[i].draw(0, slide);
        if(words[i].theta > 0.1) {
            num++;
            shadow.begin();
            shadow.setUniform3f("planeCenter", p.p);
            shadow.setUniform3f("planeNormal", p.n);
            shadow.setUniform3f("lightPos", lightSource.get());
            shadow.setUniformMatrix4f("rotationMatrix", m);
            ofSetColor(0, 255, 0);
            ofPushMatrix();
            ofTranslate(0, slide);
            ofTranslate(words[i].offset);
            words[i].mesh.draw();
            ofPopMatrix();

            shadow.end();
        }
    }
    
    ofPopMatrix();
    
    cam.end();
    
    buffer.end();
    
    ofDisableDepthTest();
    gradient.begin();
    gradient.setUniformTexture("inputTexture", buffer.getTexture(), 0);
    gradient.setUniform2f("resolution", ofVec2f(ofGetWidth(), ofGetHeight()));
    gradient.setUniform3f("col1", ofVec3f(c1.get().r/255.0, c1.get().g/255.0, c1.get().b/255.0));
    gradient.setUniform3f("col2", ofVec3f(c2.get().r/255.0, c2.get().g/255.0, c2.get().b/255.0));
    ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
    gradient.end();

//    buffer.draw(0, 0);
    if(showGui) {
        gui.draw();
        
        ofDrawBitmapStringHighlight(ofToString(ofGetFrameRate()), ofGetWidth()-100, ofGetHeight()-10);
        
        stringstream ss;
        ss << "CamX: " << cam.getPosition().x << " CamY: " << cam.getPosition().y << " CamZ: " << cam.getPosition().z << endl;
        ss << "CamUpX: " << cam.getUpDir().x << " CamUpY: " << cam.getUpDir().y << " CamUpZ: " << cam.getUpDir().z << endl;
        ss << "CamTargetX: " << cam.getLookAtDir().x << " CamTargetY: " << cam.getLookAtDir().y << " CamTargetZ: " << cam.getLookAtDir().z <<endl;
        ss << "Slide: " << slide;
        ofDrawBitmapStringHighlight(ss.str(), ofGetWidth()-500, 20);
    }

}

//--------------------------------------------------------------
ofVec2f ofApp::addVerse(string text, ofVec3f offset) {
    vector<string> lines = ofSplitString(text, "\n");
    ofVec2f initialOffset = offset;
    float longestLineLength = 0;
    for(int i = 0; i < lines.size(); i++) {
        ofVec2f o = addLine(lines[i], offset);
        if(o.x > longestLineLength) {
            longestLineLength = o.x;
        }
        offset.y += -200;
    }
    cout<<"LongestLine: " <<longestLineLength<<endl;
    cout<<"TotalHeight: " << abs(offset.y - initialOffset.y)<<endl;

    return ofVec2f(longestLineLength, abs(offset.y - initialOffset.y));
}

//--------------------------------------------------------------
ofVec2f ofApp::addLine(string text, ofVec3f offset) {
    float kerning = 100;

    ofVec3f initialOffset = offset;
    for(int i = 0; i < text.size(); i++) {
        FlipText word;
        word.font = &font;
        word.color = frontColor;
        if(text[i] == 'I')
            kerning = 40;
        else
            kerning = 100;
        word.init(string(1, text[i]), offset, i * 0.05);
        offset.x += kerning;
        words.push_back(word);
    }
    
    return offset - initialOffset;
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
        pair<ofColor, ofColor> colPair = make_pair(c1, c2);
        colorPairs.push_back(colPair);
        camPositions.push_back(cam.getPosition());
        camUpVectors.push_back(cam.getUpDir());
        camLookAts.push_back(cam.getLookAtDir());
    }
    if(key == 'n') {
        camIndex = ofRandom(0, camPositions.size());
        colorIndex = ofRandom(0, colorPairs.size());
    }
    if(key == 'g') {
        showGui = !showGui;
    }
    if(key == 's') {
        colorSettings.clear();
        for(int i = 0; i < colorPairs.size(); i++) {
            colorSettings.addTag("color");
            colorSettings.pushTag("color", i);
            colorSettings.addValue("R", colorPairs[i].first.r);
            colorSettings.addValue("G", colorPairs[i].first.g);
            colorSettings.addValue("B", colorPairs[i].first.b);
            colorSettings.popTag();
            i++;
            colorSettings.addTag("color");
            colorSettings.pushTag("color", i);
            colorSettings.addValue("R", colorPairs[i].second.r);
            colorSettings.addValue("G", colorPairs[i].second.g);
            colorSettings.addValue("B", colorPairs[i].second.b);
            colorSettings.popTag();
        }
        colorSettings.saveFile("settings/colorSettings.xml");
        cameraSettings.clear();
        for(int i = 0; i < camPositions.size(); i++) {
            cameraSettings.addTag("position");
            cameraSettings.pushTag("position", i);
            cameraSettings.addValue("X", camPositions[i].x);
            cameraSettings.addValue("Y", camPositions[i].y);
            cameraSettings.addValue("Z", camPositions[i].z);
            cameraSettings.popTag();
            cameraSettings.addTag("upDir");
            cameraSettings.pushTag("upDir", i);
            cameraSettings.addValue("X", camUpVectors[i].x);
            cameraSettings.addValue("Y", camUpVectors[i].y);
            cameraSettings.addValue("Z", camUpVectors[i].z);
            cameraSettings.popTag();
            cameraSettings.addTag("LookAt");
            cameraSettings.pushTag("LookAt", i);
            cameraSettings.addValue("X", camLookAts[i].x);
            cameraSettings.addValue("Y", camLookAts[i].y);
            cameraSettings.addValue("Z", camLookAts[i].z);
            cameraSettings.popTag();
        }
        cameraSettings.saveFile("settings/cameraSettings.xml");
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
    buffer.allocate(w, h);
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
