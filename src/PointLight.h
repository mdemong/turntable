#pragma once
#include "Light.h"
/*
     Micah Demong
     Point Light Class

     This class represents a point light which emanates light in all directions.
*/

class PointLight : public Light {

public:
	PointLight();
     PointLight(glm::vec3 position, float intensity);
     float getIllumination(glm::vec3 point);
     void draw();
};

