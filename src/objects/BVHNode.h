#pragma once
#include "SceneObject.h"
#include "box.h"

// BVH tree
// Referenced from Fundamentals of Computer Graphics, 4th ed.


class BVHNode :
     public SceneObject
{
public:
     BVHNode();
     void draw() {}
     bool intersect(const Ray &ray, glm::vec3 &point, glm::vec3 &normal) = 0;
     // todo: pure virtual bbox()?
     SceneObject *left;
     SceneObject *right;
     Box bbox;
};

