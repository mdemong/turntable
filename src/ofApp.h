
/*
     ofApp: Final Project: Animated Ray Tracer
     Micah Demong


     Keybinds:
     F: Toggle Fullscreen
     F1: View EasyCam
     F2: View SideCam
     F3: View PreviewCam
     T: Ray-Trace scene
     V: Toggle image drawing to viewport
     X: Render and export ray-traced video
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
#include "objects/Mesh.h"
#include "objects/Triangle.h"
#include "videoTracer.h"


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

     void setupMesh();

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
     RenderCam *renderCam;
     ofImage image;
     RayTracer rayTracer;

     vector<SceneObject *> objects;
     vector<Light *> lights;
     //ViewPlane viewPlane;

     // Change these if you want a different image size output
     int imageWidth = 600;
     int imageHeight = 400;

     Mesh mesh;

     RenderCam *videoRenderCam;
     VideoTracer videoTracer;
};
