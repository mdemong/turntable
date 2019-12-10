#pragma once
#include "SceneObject.h"

// BVH tree
// Algorithms and class design from Fundamentals of Computer Graphics, 4th ed.


class BVHNode :
     public SceneObject
{
public:
     BVHNode();
     void draw() {}
     bool intersect(const Ray &ray, glm::vec3 &point, glm::vec3 &normal) = 0;
     SceneObject *left;
     SceneObject *right;
     // todo: pure virtual bbox()?
};

