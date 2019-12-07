
/*
     ofApp: Ray Tracer, Part 3
     Micah Demong

     This project performs a phong-lambert ray trace of a 3D scene with textures.
     Instead of being handled in the ofApp class, the actual ray tracing in 
     the RayTracer class (RayTracer::rayTrace()). ofApp::trace() simply calls
     this function and stores its result in an image.

     SceneObject has been modified to handle textures. See SceneObject.h for more info.
     
     Texture lookups are performed by the Plane class. We load our texture to the plane
     in ofApp::setupObjects().
     
     Keybinds:
     F: Toggle Fullscreen
     F1: View EasyCam
     F2: View SideCam
     F3: View PreviewCam
     T: Ray-Trace scene
     V: Toggle image drawing to viewport
*/

#pragma once

#include "ofMain.h"
#include "RayTracer.h"
#include "objects/RenderCam.h"
#include "objects/SceneObject.h"
#include "Light.h"
#include "PointLight.h"
#include "objects/Sphere.h"
#include "objects/ViewPlane.h"


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

          /*
               Helper function for ofApp::setup() which performs camera setup operations.
          */
          void setupCameras();

          /*
               Helper function of ofApp::setup() which initializes objects.
          */
          void setupObjects();

          /*
               Draws X, Y, and Z axes at the origin.
          */
          void drawAxes();

          /*
               Runs this class's RayTracer, saves it to an image on disk, and
               displays this image to the viewport.
          */
          void trace();


          // --- VARIABLES ---

		bool bHide = true;
		bool bShowImage = false;

		ofEasyCam easyCam;
		ofCamera sideCam;
		ofCamera previewCam;
		ofCamera *currentCam;    // set to current camera either easyCam or sideCam

		// set up one render camera to render image through
		RenderCam renderCam;
		ofImage image;
          RayTracer rayTracer;

		vector<SceneObject *> objects;
		vector<Light *> lights;
          ViewPlane viewPlane;

          // Change these if you want a different image size output
		int imageWidth = 1800;
		int imageHeight = 1200;
         
};
 