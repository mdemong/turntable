#include "ofApp.h"

// caching random values for anti-aliasing?

void ofApp::setup() {
     
     ofSetBackgroundColor(0, 0, 0);
     setupCameras();
     setupObjects();

     lights.push_back(new PointLight(glm::vec3(-4, 0, 5), 5.0));
     lights.push_back(new PointLight(glm::vec3(3, 1, 5), 5.0));
     lights.push_back(new PointLight(glm::vec3(0, 3, 3), 7.0));

     rayTracer = RayTracer(renderCam, objects, lights);




}

void ofApp::setupCameras() {

     currentCam = &easyCam;

     easyCam.setDistance(10);
     easyCam.setPosition(10, 10, 10);
     easyCam.lookAt(glm::vec3(0, 0, 0));
     easyCam.setNearClip(0.01);

     sideCam.setPosition(glm::vec3(10, 0, 0));
     sideCam.lookAt(glm::vec3(0, 0, 0));
     sideCam.setNearClip(0.01);

     previewCam.setPosition(glm::vec3(0, 0, 9));
     previewCam.lookAt(glm::vec3(0, 0, 0));
     previewCam.setNearClip(0.01);
     previewCam.setFov(55);

}

void ofApp::setupObjects() {

     objects.push_back(new Sphere(glm::vec3(1, -.5, -2), 1.5, ofColor(255, 205, 150)));
     objects.push_back(new Sphere(glm::vec3(0, -1, 0), 1.0, ofColor(84, 68, 48)));
     objects.push_back(new Sphere(glm::vec3(-1, -1, 2), 1.0, ofColor(255, 230, 200)));

     Plane * ground = new Plane(glm::vec3(0, -2, -5), glm::vec3(0, 1, 0), ofColor::gray);
     ground->applyTexture(ofImage("textures/cardboard.jpg"));
     objects.push_back(ground);

     setupMesh();
}

void ofApp::setupMesh() {
     const float PRISM_HEIGHT = sqrtf(2.0 / 3.0) * 2;
     vector<glm::vec3> vertices = {
          {0, 0, 0},
          {2, 0, 0},
          {1, PRISM_HEIGHT, PRISM_HEIGHT / 3},
          {1, 0, PRISM_HEIGHT}
     };
     vector<Triangle *> triangles = {
          {new Triangle(0, 1, 2)},
          {new Triangle(0, 3, 2)},
          {new Triangle(0, 3, 1)},
          {new Triangle(3, 1, 2)}
     };

     objects.push_back(new Mesh(vertices, triangles));
}


void ofApp::update() {
     
}

void ofApp::draw() {

     currentCam->begin();

     for (auto object : this->objects) {
          object->draw();
     }

     for (auto light : this->lights) {
          light->draw();
     }

     drawAxes();
     viewPlane.drawWireframe(6, 4);
     renderCam.draw();
     rayTracer.draw(6, 4);
     
     currentCam->end();

     if (bShowImage) {
          ofSetColor(ofColor::white);
          
          image.draw(50, 50);
     }
}

void ofApp::drawAxes() {
     glm::vec3 origin = glm::vec3(0, 0, 0);
     glm::vec3 vecX = glm::vec3(1, 0, 0);
     glm::vec3 vecY = glm::vec3(0, 1, 0);
     glm::vec3 vecZ = glm::vec3(0, 0, 1);

     ofSetColor(ofColor::red);
     ofDrawLine(origin, vecX);
     ofSetColor(ofColor::green);
     ofDrawLine(origin, vecY);
     ofSetColor(ofColor::blue);
     ofDrawLine(origin, vecZ);
     ofSetColor(ofColor::white);
}

void ofApp::keyPressed(int key) {
     switch (key) {
     case 'F':
     case 'f':
          ofToggleFullscreen();
          break;
     case OF_KEY_F1:
          currentCam = &easyCam;
          break;
     case OF_KEY_F2:
          currentCam = &sideCam;
          break;
     case OF_KEY_F3:
          currentCam = &previewCam;
          break;
     case 'T':
     case 't':
          ofApp::trace();
          break;
     case 'V':
     case 'v':
          bShowImage = !bShowImage;
          break;
     }
}

void ofApp::trace() {
     image = rayTracer.rayTrace(this->imageWidth, this->imageHeight);
     image.save("images/myRender.png");

     // For some reason, it wouldn't display the image in the viewport properly 
     // unless I re-loaded it here...
     image.load("images/myRender.png");

     bShowImage = true;
}

void ofApp::keyReleased(int key) {
}

void ofApp::mouseMoved(int x, int y) {

}

void ofApp::mouseDragged(int x, int y, int button) {
}

void ofApp::mousePressed(int x, int y, int button) {
}

void ofApp::mouseReleased(int x, int y, int button) {
}

void ofApp::mouseEntered(int x, int y) {
}

void ofApp::mouseExited(int x, int y) {
}

void ofApp::windowResized(int w, int h) {
}

void ofApp::dragEvent(ofDragInfo dragInfo) {

}

void ofApp::gotMessage(ofMessage msg) {
}
