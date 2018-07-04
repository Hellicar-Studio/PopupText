#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "Triangulator.h"
#include "ofxEasing.h"
#include "FlipText.hpp"
#include "RayUtils.h"

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
        void addLine(string text, ofVec3f offset);
    
        void addVerse(string text, ofVec3f offset);

    
        ofxPanel gui;
        ofParameter<ofVec3f> lightSource;
        ofParameter<ofVec3f> planeNormal;
        ofParameter<float> theta; //
        ofParameter<float> rotationYPos; //
    
        vector<FlipText> words;
    
        ofColor frontColor;

        float initTime; //
    
        ofMesh mesh; //
    
        ofTrueTypeFont font; //
        string text = "T"; //
        
        Plane p;
        Line l;
    
        ofEasyCam cam;
};
