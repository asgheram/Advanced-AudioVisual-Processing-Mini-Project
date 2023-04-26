#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	font.load("OpenSans-ExtraBold.ttf", 15); //loads in the font required at sets the font size

	//faces setup 
	regularFace = true; //allows the regular face to appear first on the screen 
	faceMood = 2; // set the inital value of the faces 

	//floating cirlces and squares setup
	int maxSquares = 100; //sets the maximum amount of squares that can appear
	int maxCircles = 100; //sets the maximum amount of squares that can appear

	spaceRange = 500; //determins how condensed the shapes are
	ofEnableDepthTest(); 
	ofSetBackgroundColor(0); //sets background to black 
	light.setPosition(-900, 900, 900); //determinds where in space the light will be coming from
	light.enable(); //turns light on
	dylan.load("dylan image.jpg"); //loads in selected image
	both.load("both image.jpg"); //loads in selected image

	//squares placement, colours and texture
	for (int i = 0; i < maxSquares; i++) {
		ofBoxPrimitive newSquare;
		newSquare.set(ofRandom(10, 180)); //randomise the size between 10 - 180
		newSquare.mapTexCoordsFromTexture(both.getTexture()); //attaches image to the shape using texture mapping

		newSquare.setPosition(ofRandom(-spaceRange, spaceRange), //placing the sqaures randomly in space using x axis
			ofRandom(-spaceRange, spaceRange), //y axis
			ofRandom(-spaceRange, spaceRange)); //and z axis
		for (int side = 0; side < 2; side++) { //selecting 2 sides of the square to be coloured
			newSquare.setSideColor(side, ofColor::fromHsb(ofRandom(255), 255, 255)); //randomly choose the colour for the square sides
		}
		squares.push_back(newSquare);
	}

	//circle placement, colours and textures
	for (int i = 0; i < maxCircles; i++) {
		ofSpherePrimitive newCircle;
		newCircle.set(ofRandom(10, 160), 10);  //randomise the size between 10 - 180
		newCircle.mapTexCoordsFromTexture(dylan.getTexture()); //attaches image onto the shape using texture mapping

		newCircle.setPosition(ofRandom(-spaceRange, spaceRange), //placing the sqaures randomly in space using x axis
				ofRandom(-spaceRange, spaceRange), //y axis
				ofRandom(-spaceRange, spaceRange)); //and z axis
		circles.push_back(newCircle);
	}

	//confetti setup
	int maxConfetti;
	maxConfetti = 100; //maximum amount of sqaures placed on screen

	for (int i = 0; i < maxConfetti; i++) {
		confetto maxConfetto; 
		confetti.push_back(maxConfetto);
	}

	//music setup 
	happySound.load("music/happy-soundtrack.mp3"); //loads in selected audio
	sadSound.load("music/sad-soundtrack.mp3"); //loads in selected audio
}

//--------------------------------------------------------------
void ofApp::update() {

	squares[ofRandom(squares.size())].setPosition(ofRandom(-spaceRange, spaceRange), //change the positon and size of square everytime it reloads
		ofRandom(-spaceRange, spaceRange), // with the x, y and z axis
		ofRandom(-spaceRange, spaceRange));
	glm::vec3 bothOrientation(ofRandom(360), ofRandom(360), ofRandom(360)); //allows the sqaures to change orintation so they are not all facing the same way
	squares[ofRandom(squares.size())].setOrientation(bothOrientation); //changes the size of squares every reload

	circles[ofRandom(circles.size())].setPosition(ofRandom(-spaceRange, spaceRange), //change the positon and size of circles everytime it reloads
		ofRandom(-spaceRange, spaceRange),
		ofRandom(-spaceRange, spaceRange));//with the x, y and z axis
	glm::vec3 dylanOrientation(ofRandom(360), ofRandom(360), ofRandom(360)); //allows the cirlces to change orintation so they are not all facing the same way
	circles[ofRandom(circles.size())].setOrientation(dylanOrientation); //changes the size of circles every reload

}

//--------------------------------------------------------------
void ofApp::draw() {

	//instruction on how to use the project
	ofSetColor(255);
	font.drawString("Click 'h' if happy or 's' if sad.", 0, 120); //writes text using chosen font in selected location
	font.drawString("Drag mouse around and press the up and down arrows.", 0, 140);
	font.drawString("Enjoy the music :)", 0, 160);
	

	//face 

	//regular face
	if (regularFace == true) { //displays this version of the face is condition is met
		//eyes
		ofSetColor(255);
		ofDrawEllipse(410, 300, 100, 100);
		ofDrawEllipse(580, 300, 100, 100);
		//mouth
		ofSetLineWidth(8);
		ofDrawLine(410, 470, 580, 470);
		//face
		ofSetColor(241, 194, 125);
		ofDrawEllipse(500, 370, 500, 500);

	}

	//happy face
	if (faceMood >= 3) { //if condition is met draw this face
		//eyes
		ofSetColor(0);
		ofDrawEllipse(45, 45, 20, 20);
		ofDrawEllipse(75, 45, 20, 20);
		//mouth
		ofSetLineWidth(4);
		ofDrawLine(40, 65, 40, 80);
		ofDrawLine(80, 65, 80, 80);
		ofDrawLine(40, 80, 80, 80);
		//face
		ofSetColor(0,255, 0);
		ofDrawEllipse(60, 60, 100, 100);
		ofSetColor(255);
	}

	//face sad
	if (faceMood <= 1) { //if condition is met draw this face
		//eyes 
		ofSetColor(0);
		ofDrawEllipse(45, 45, 20, 20);
		ofDrawEllipse(75, 45, 20, 20);
		//mouth
		ofSetLineWidth(4);
		ofDrawLine(40, 80, 40, 95);
		ofDrawLine(80, 80, 80, 95);
		ofDrawLine(40, 80, 80, 80);
		//face
		ofSetColor(255, 0, 0);
		ofDrawEllipse(60, 60, 100, 100);
	}

	//cloud
	if (faceMood <= 1) { //if condition is met the following happens
		float time = ofGetSystemTimeMillis() / 250.0; //spped at which the screen rotates
		camera.begin(); //everything inside camera will be seen in 3d 

		both.getTexture().bind();

		ofPushMatrix(); 
		ofRotateDeg(time);

		for (int i = 0; i < squares.size(); i++) {
			both.getTexture().bind(); //wraps all following shapes within image
			squares[i].draw(); //all sqaure will be shown as image 'both'
			both.getTexture().unbind(); //stops wraping using image
		}

		ofPopMatrix();
		camera.end(); //end of 3d viewing
	}

	if (faceMood >= 3) { //if condtion is met the following happens
		float time = ofGetSystemTimeMillis() / 250.0; //speed at which the screen roates
		camera.begin(); //everything inside camera will be seen in 3d 

		dylan.getTexture().bind();

		ofPushMatrix();
		ofRotateDeg(time);

		for (int i = 0; i < circles.size(); i++) {
			dylan.getTexture().bind(); //wraps all following shapes within image
			circles[i].draw(); //all circles will be shown as image 'dylan'
			dylan.getTexture().unbind(); //stops wraping using image
		}

		ofPopMatrix();
		camera.end(); //end of 3d viewing

		//draw confetti using infor from confetto::draw
		for (int i = 0; i < confetti.size(); i++) { 
			confetti[i].draw();
		}
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	
	//face
	if (key == 'h') { //when the 'h' key is pressed the following happens
		cout << key << endl; //displays what key is pressed
		faceMood += 1; //increases counter by 1
		happySound.play(); //triggers 1 sound to start
		sadSound.stop(); //forces another sound to stop or stay silent
	}
	else {
		regularFace = false; //defult condition
	}

	if (key == 's') { //when 's' key is pressed the following happnes
		cout << key << endl; //displays what key is pressed
		faceMood -= 1; //decreases counter by 1
		sadSound.play(); //triggers 1 sound to start
		happySound.stop(); //forces another sound to stop or stay silent
	}
	else {
		regularFace = false; //defult condition
	}

	//cloud
	switch (key) {
	case OF_KEY_UP: //when the up arrow is triggered
		spaceRange += 15; //the space between the circles and squares increase
		break;

	case OF_KEY_DOWN: //when the down arrow is triggered
		spaceRange -= 15; //the space between the circles and sqaures decrease
		break;

	default:
		break;
	}

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
confetto::confetto() {
	//constructor 
	width = 20; //sets width of confetti
	height = 20; //sets height of confetti
	x = ofRandom(ofGetWidth()); //only fills width of screen	
	y = ofRandom(ofGetHeight()); // only fills height of the screen 
	color.set(ofRandom(255), ofRandom(255), ofRandom(255)); //determins all confetti colours randomly
}

//--------------------------------------------------------------
confetto::~confetto() {
	//deconstructor 
}

//--------------------------------------------------------------
void confetto::draw() {
	ofSetColor(color); //sets each confetti square to a predetermind colour
	ofDrawRectangle(x, y, width, height); //sets postion and dimensions of each conetti square

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}