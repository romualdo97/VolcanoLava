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

	shader.setUniform2f("iResolution", ofVec2f(1024, 768));
	shader.setUniform1f("iTime", ofGetElapsedTimef());
	shader.setUniform2f("iMouse", ofVec2f(ofGetMouseX(), ofGetMouseY()));
	// iTemperature 1 for harm 0 for cold
#ifdef IS_FLASHLIGHT
	shader.setUniform1f("iTemperature", ofMap(photoValue, 0, 1023, 0, 1));
#else
	shader.setUniform1f("iTemperature", 1);
#endif // IS_FLASHLIGHT
	

	ofRect(0, 0, ofGetWidth(), ofGetHeight());

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
