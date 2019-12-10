#pragma once
#include "SceneObject.h"

// Axis-aligned Binary Space Partition (BSP) tree
// Structure and algorithm from Fundamentals of Computer Graphics, 4th ed., p. 307-308


class BSPNode :
     public SceneObject
{
public:
     BSPNode();
     void draw() {}
     bool intersect(const Ray &ray, glm::vec3 &point, glm::vec3 &normal) = 0;
     SceneObject *left;
     SceneObject *right;
     float D;
};

