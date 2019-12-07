#include "Sphere.h"

Sphere::Sphere(glm::vec3 p, float r, ofColor diffuse) { 
     position = p; 
     radius = r; 
     diffuseColor = diffuse; 
}

bool Sphere::intersect(const Ray & ray, glm::vec3 & point, glm::vec3 & normal) {
     return glm::intersectRaySphere(ray.p, ray.d, position, radius, point, normal);
}

void Sphere::draw() {
     
     ofSetColor(this->diffuseColor);
     ofDrawSphere(position, radius);
     ofSetColor(ofColor::white);
}