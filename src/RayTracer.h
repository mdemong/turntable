#pragma once
#include "ofMain.h"
#include "objects/RenderCam.h"
#include "objects/SceneObject.h"
#include "Light.h"

/*
     Micah Demong
     
     Ray Tracer class

     This class performs ray tracing with lambert + phong shading with shadows.
     The lambert and phong functions are now unused, but show how each individual calculation is performed.
     The phong_lambert() function performs both lambert and phong, including shadow calculation.
*/


class RayTracer {
     RenderCam cam;
     vector<SceneObject *> objects;
     vector<Light *> lights;
     float phongPower = 50;
     float phongLightIntensity = 0.5;
     ofColor ambientColor = ofColor(10, 8, 5);

     /*
          Gets the color for a given ray by performing intersections with this->objects.
     */
     ofColor getRayColor(Ray & r);     

     ofColor lambert(const glm::vec3 &p, const glm::vec3 &norm, const ofColor diffuse);

     ofColor phong(const glm::vec3 &p, const glm::vec3 &norm, const ofColor diffuse, const ofColor specular, float power);

     /*
          Calculates phong/lambert shading with shadows for a given point.
     */
     ofColor phong_lambert(const glm::vec3 & p, const glm::vec3 & norm, const ofColor diffuse, const ofColor specular, float power);

     /*
          Helper function to check if a point is in a shadow.
     */
     bool inShadow(const Ray & r);


public:
     RayTracer();

     /*
          Constructs a ray tracer from the given camera, Object vector, and Light vector.
     */
	RayTracer(RenderCam cam, vector<SceneObject *> objects, vector<Light *> lights);

     /*
          Creates a ray-traced image of the scene with the given width and height.
          The ray tracing will be performed using this object's SceneObject and Light lists,
          from the point of view of its RenderCam.
     */
     ofImage rayTrace(int imgWidth, int imgHeight);

     /*
          Draws simplified representation of this ray tracer using oF draw calls.
     */
     void draw(int imgWidth, int imgHeight);

};

/*
     Utility function to find the bisector of two vectors.
*/
glm::vec3 bisector(glm::vec3 vecA, glm::vec3 vecB);