#pragma once

#include "ofMain.h"

class confetto { //class used to simulate confetti 
public:
	//properties that the confetti can have
	//dimensions, location and colour of confetti
	int width;
	int height;
	int x;
	int y;
	ofColor color;
	void draw();
	confetto();
	~confetto();
};

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);



	//face 
	//face properties to determin which one will be shown 
	bool regularFace;
	bool happyFace;
	bool sadFace;
	int faceMood;
	int faceInteract;

	//box and circle  
	vector<ofBoxPrimitive> squares; //allows 3d boxes to be drawn
	vector<ofSpherePrimitive> circles; //allows 3d spheres to be drawn
	ofEasyCam camera; //allows to see the project in 3d
	ofLight light; 
	int spaceRange;
	ofImage dylan; //image will be refered to using this name
	ofImage both;

	//confetti
	vector<confetto> confetti;

	//music
	ofSoundPlayer happySound; //music will be refered to using this name 
	ofSoundPlayer sadSound;

	//text
	ofTrueTypeFont font; //font system
};
