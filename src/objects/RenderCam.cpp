#include "RenderCam.h"

RenderCam::RenderCam() {
     position = glm::vec3(0, 0, 10);
     aim = glm::vec3(0, 0, -1);
}

// Get a ray from the current camera position to the (u, v) position on
// the ViewPlane
//
Ray RenderCam::getRay(float u, float v) {
	glm::vec3 pointOnPlane = view.toWorld(u, v);
	return(Ray(position, glm::normalize(pointOnPlane - position)));
}
