#pragma once
#include "SceneObject.h"
#include "ViewPlane.h"

//  render camera  - currently must be z axis aligned (we will improve this in project 4)
//
class RenderCam: public SceneObject {
     glm::vec3 aim;
     // The camera viewplane, this is the view that we will render 

public:
     ViewPlane view;

     RenderCam();

	Ray getRay(float u, float v);

     void draw();

     glm::mat4 createRotMatrix();

     void lookAt(glm::vec3 lookPosition);

     void setPosition(glm::vec3 position);


     // For now, assuming we can't intersect the renderCam. - Micah
     bool intersect(const Ray &ray, glm::vec3 &point, glm::vec3 &normal) { return false; }

	void drawFrustum();
 
};