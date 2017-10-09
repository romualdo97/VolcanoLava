#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	ofSetFrameRate(60);

#ifdef TARGET_OPENGLES
	shader.load("shadersES2/shader");
#else
	if (ofIsGLProgrammableRenderer())
	{
		shader.load("shadersGL3/shader");
	}
	else
	{
		shader.load("shadersGL2/shader");
	}
#endif // TARGET_OPENGLES

	float planeScale = 0.75;
	int planeWidth = ofGetWidth() * planeScale;
	int planeHeight = ofGetHeight() * planeScale;
	int planeGridSize = 20;
	int planeColums = planeWidth / planeGridSize;
	int planeRows = planeHeight / planeGridSize;

	plane.set(planeWidth, planeHeight, planeColums, planeRows, ofPrimitiveMode::OF_PRIMITIVE_TRIANGLE_STRIP);

}

//--------------------------------------------------------------
void ofApp::update()
{

}

//--------------------------------------------------------------
void ofApp::draw()
{
	ofSetColor(255);

	shader.begin();

	// center plane in screen
	ofTranslate(ofGetWidth()/2, ofGetHeight()/2);

	float percentY = mouseY / (float)ofGetHeight();
	float rotation = ofMap(percentY, 0, 1, -60, 60, true) + 60;
	ofRotate(rotation, 1, 0, 0);

	shader.setUniform1f("time", ofGetElapsedTimef());
	plane.drawWireframe();

	shader.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y )
{

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button)
{

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y)
{

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y)
{

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h)
{

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg)
{

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo)
{ 

}
