#pragma once

#include "ofMain.h"

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
	
	private:
		ofShader shader;
		ofPlanePrimitive plane;
		ofSpherePrimitive uvsphere;
		ofImage fireImage;
		ofImage rampImage;
		ofTexture fireTexture;
		ofTexture rampTexture;
		float flowMapOffset0;
		float flowMapOffset1;
		float const cycle = 0.08f;
		float const halfCycle = cycle * 0.5f;
		float const flowSpeed = 0.0005f;
		
};
