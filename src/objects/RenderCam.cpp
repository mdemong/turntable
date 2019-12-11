#include "RenderCam.h"

RenderCam::RenderCam() {
     position = glm::vec3(0, 0, 10);
     aim = glm::vec3(0, 0, -1);
}

// Get a ray from the current camera position to the (u, v) position on
// the ViewPlane
//
Ray RenderCam::getRay(float u, float v) {
	glm::vec3 pointOnPlane = view.toWorld(u, v);
	return(Ray(position, glm::normalize(pointOnPlane - position)));
}

void RenderCam::draw() {
     ofPushMatrix();
     ofMultMatrix(createRotMatrix());
     ofDrawBox(1);
     ofPopMatrix();
     //cout << view.toWorld(.5, .5) << endl;
}

// Adapted from lookAt lab example
glm::mat4 RenderCam::createRotMatrix() {
     glm::mat4 m;

     glm::vec3 w = glm::normalize(-aim);
     glm::vec3 u = glm::normalize(glm::cross({0, 1, 0}, w));
     glm::vec3 v = glm::normalize(glm::cross(w, u));

     m = { {u, 0}, {v, 0}, {w, 0}, {this->position, 1} };

     return m;
}

void RenderCam::lookAt(glm::vec3 lookPosition)
{
}

void RenderCam::setPosition(glm::vec3 position)
{
     glm::vec3 viewDisplacement = view.position - this->position;
     this->position = position;
     view.position = position + viewDisplacement;
}
