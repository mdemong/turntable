#include "PointLight.h"

PointLight::PointLight() {
}

PointLight::PointLight(glm::vec3 position, float intensity) {
     this->position = position;
     this->intensity = intensity;
}

float PointLight::getIllumination(glm::vec3 point) {
     float distSquare = glm::distance2(point, this->position);
     return (this->intensity / distSquare);
}

void PointLight::draw() {
     ofSetColor(ofColor::yellow);
     ofDrawSphere(position, .1);
     ofSetColor(ofColor::white);
}

