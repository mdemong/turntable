#pragma once
#include "ofMain.h"

/*
     Micah Demong

     Light Class

     I chose not to make Light a SceneObject, since a light is not going to have intersection,
     a diffuse color, or specular color. Rather than setting each of those values to some sort of
     unusable/placeholder value, I made this a separate abstract class. This can later be extended
     to support different types of lights (e.g. cone lights, plane lights, etc).
*/

class Light {
protected:
     float intensity;
public:
     virtual float getIllumination(glm::vec3 point) = 0;
     virtual void draw() = 0;
     glm::vec3 position;

     // todo: should light have color?
};

