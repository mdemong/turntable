#pragma once
#include "SceneObject.h"

//  General purpose sphere  (assume parametric)
//
class Sphere: public SceneObject {
public:
     Sphere(glm::vec3 p, float r, ofColor diffuse = ofColor::lightGray);
	Sphere() {}
     bool intersect(const Ray &ray, glm::vec3 &point, glm::vec3 &normal);
     void draw();

	float radius = 1.0;
};