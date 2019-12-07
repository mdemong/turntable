#include "ViewPlane.h"

ViewPlane::ViewPlane() {                         // create reasonable defaults (6x4 aspect)
     min = glm::vec2(-3, -2);
     max = glm::vec2(3, 2);
     position = glm::vec3(0, 0, 5);
     normal = glm::vec3(0, 0, 1);      // viewplane currently limited to Z axis orientation
}

// Convert (u, v) to (x, y, z) 
// We assume u,v is in [0, 1]
//
glm::vec3 ViewPlane::toWorld(float u, float v) {
	float w = width();
	float h = height();
	return (glm::vec3((u * w) + min.x, (v * h) + min.y, position.z));
}

void ViewPlane::draw() {
     //ofDrawRectangle(glm::vec3(min.x, min.y, position.z), width(), height());
     auto vert1 = toWorld(0, 0);
     auto vert2 = toWorld(1, 0);
     auto vert3 = toWorld(1, 1);
     auto vert4 = toWorld(0, 1);

     ofSetColor(ofColor::white);
     ofDrawLine(vert1, vert2);
     ofDrawLine(vert2, vert3);
     ofDrawLine(vert3, vert4);
     ofDrawLine(vert4, vert1);
}

void ViewPlane::drawWireframe(int horizPixels, int vertPixels) {
     // drawing border
     this->draw();
     
     float widthInterval = 1.0 / (float)horizPixels;
     for (float i = widthInterval; i < 1; i += widthInterval) 
          ofDrawLine(toWorld(i, 0), toWorld(i, 1));
     
     float heightInterval = 1.0 / (float)vertPixels;
     for (float i = heightInterval; i < 1; i += heightInterval)
          ofDrawLine(toWorld(0, i), toWorld(1, i));

}
