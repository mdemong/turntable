#pragma once
#include "SceneObject.h"
#include "ViewPlane.h"

//  render camera  - currently must be z axis aligned (we will improve this in project 4)
//
class RenderCam: public SceneObject {
     glm::vec3 aim;
     // The camera viewplane, this is the view that we will render 
     ViewPlane view;

public:

     RenderCam();

	Ray getRay(float u, float v);

     void draw();

     glm::mat4 createRotMatrix();


     // For now, assuming we can't intersect the renderCam. - Micah
     bool intersect(const Ray &ray, glm::vec3 &point, glm::vec3 &normal) { return false; }

	void drawFrustum();

 
};