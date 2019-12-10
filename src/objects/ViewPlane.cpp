#include "ViewPlane.h"

ViewPlane::ViewPlane() {                         // create reasonable defaults (6x4 aspect)
     min = glm::vec2(-3, -2);
     max = glm::vec2(3, 2);
     position = glm::vec3(0, 0, 5);

     // Viewplane modified to allow arbitrary rotation  -Micah
     normal = glm::vec3(0, 0, 1);
}

// Convert (u, v) to (x, y, z) 
// We assume u,v is in [0, 1]
//
glm::vec3 ViewPlane::toWorld(float u, float v) {
	float w = width();
	float h = height();

     //float angle = glm::angle(normal, { 0, 0, -1 });

     //glm::mat4 m = glm::toMat4(glm::rotation({ 0, 0, 1 }, normal));
     glm::vec3 zAlignedPoint = {(u * w) + min.x, (v * h) + min.y, position.z};
     glm::mat4 m = rotateToVector({0, 0, 1}, glm::normalize(normal));
     glm::mat4 translateMtx = glm::translate(position);
     glm::vec4 result = translateMtx * m * glm::inverse(translateMtx) * glm::vec4(zAlignedPoint, 1);
     
     //cout << m << endl;
     // cout << translateMtx << endl;
     //cout << "normal:" << normal << endl;
     //cout << zAlignedPoint << " -> " << result << endl;
     return {result.x, result.y, result.z};
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
