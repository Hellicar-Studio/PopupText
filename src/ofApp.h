#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "Triangulator.h"
#include "ofxEasing.h"
#include "FlipText.hpp"
#include "RayUtils.h"
#include "ofxXmlSettings.h"

class ofApp : public ofBaseApp{

	public:
    
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
        ofVec3f rotatePointAboutVector(float theta, ofVec3f p, ofVec3f p1, ofVec3f p2);
        ofVec3f planeLineIntersection(Plane p, Line l);
        ofVec2f addLine(string text, ofVec3f offset);
    
        ofVec2f addVerse(string text, ofVec3f offset);

        ofxPanel gui;
        ofParameter<ofVec3f> lightSource;
        ofParameter<ofVec3f> planeNormal;
        ofParameter<ofColor> c1, c2;
    
        vector<ofVec3f> camPositions;
        vector<ofVec3f> camUpVectors;
        vector<ofVec3f> camLookAts;
        vector<pair<ofColor, ofColor>> colorPairs;
    
        ofVec3f camPosition, camUpVector, camLookAt;
        
        ofxXmlSettings cameraSettings, colorSettings;
    
        ofMesh shadowMesh;

        ofShader shadow, rotate, gradient;
    
        ofFbo buffer;
    
        vector<string> Slough;
    
        int lineIndex = 0;
        int camIndex = 0;
        int colorIndex = 0;
    
        bool showGui;
        bool autoPlayOn;
    
        int slide;
    
        vector<FlipText> words;
    
        ofColor frontColor;
    
        ofTrueTypeFont font; //
        
        Plane p;
        Line l1, l2;
    
        ofEasyCam cam;
};
