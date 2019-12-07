#pragma once
#include "SceneObject.h"

/*
     Plane Class

     This class has been modified to handle texture lookups. It overrides the getColor function 
     proivded by SceneObject 
*/
class Plane: public SceneObject {

public:
     Plane(glm::vec3 p, glm::vec3 n, ofColor diffuse = ofColor::darkOliveGreen, float w = 20, float h = 20);
	Plane() { }
	bool intersect(const Ray &ray, glm::vec3 & point, glm::vec3 & normal);
     void draw();
     /*
          Gets the diffuse color at a point based on:
             * whether the plane is textured or not
             * the position of the point along the plane
             * texWidthLoops and texHeightLoops
     */
     ofColor getColor(glm::vec3 point);

     ofPlanePrimitive plane;
     glm::vec3 normal = glm::vec3(0, 1, 0);
	float width = 20;
	float height = 20;

     /*
          These correspond to the number of vertical and horizontal copies of a texture along the plane.
          For example, a texture will loop 10 times vertically and 10 times horizontally in this case,
          meaning the texture is repeated a total of 100 times on the plane.
     */
     float texWidthLoops = 10;
     float texHeightLoops = 10;
private:
     /*
          This gives the color at a given u, v value.
     */
     ofColor getTextureColor(float u, float v);
};