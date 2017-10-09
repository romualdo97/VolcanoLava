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

	plane.set(planeWidth, planeHeight, planeColums, planeRows, ofPrimitiveMode::OF_PRIMITIVE_TRIANGLE_STRIP); // plane
	plane.mapTexCoords(0, 0, planeWidth, planeHeight);
	uvsphere.setRadius(100); // uv sphere

	texture.loadImage("fire1.jpg");
}

//--------------------------------------------------------------
void ofApp::update()
{

}

//--------------------------------------------------------------
void ofApp::draw()
{
	// bind our texture. in our shader this will now be tex0 by default
	// so we can just go ahead and access it there.
	texture.getTextureReference().bind();

	// start our shader, in our OpenGL3 shader this will automagically set
	// up a lot of matrices that we want for figuring out the texture matrix
	// and the modelView matrix
	shader.begin();

	// get mouse position relative to center of screen
	float mousePosition = ofMap(mouseX, 0, ofGetWidth(), 1.0, -1.0, true);
#ifndef TARGET_OPENGLES
	// when texture coordinates are normalised, they are always between 0 and 1.
	// in GL2 and GL3 the texture coordinates are not normalised,
	// so we have to multiply the normalised mouse position by the plane width.
	mousePosition *= plane.getWidth();
#endif

	shader.setUniform1f("mouseX", mousePosition);
	//shader.setUniform1f("time", ofGetElapsedTimef());



	/*
	float percentY = mouseY / (float)ofGetHeight();
	float rotation = ofMap(percentY, 0, 1, -60, 60, true) + 60;
	ofRotate(rotation, 1, 0, 0);*/

	ofPushMatrix();
	ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2); // center plane in screen
	plane.draw();
	plane.drawAxes(100);
	ofPopMatrix();

	//uvsphere.drawWireframe();

	shader.end();

	texture.getTextureReference().unbind();
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
