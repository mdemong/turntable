#pragma once
#include "Ray.h"
#include "ofMain.h"

/*
     SceneObject Class

     Base object for every renderable object in the scene.

     I added ofImage texture and bHasTexture to each SceneObject. There's a
     function applyTexture which just initializes both of these values. I also
     added a new virtual function getColor which defaults to returning diffuse color.
     Subclasses can override this to return colors by whatever function makes sense
     for that shape.

     I'm interested in how these values might be converted into a Material class,
     since I can see how the number of properties involved with materials could
     very quickly explode once you start adding specular maps, normal maps, etc.
     However, I'm not sure how I'd effectively design that class at the moment.
*/
class SceneObject {
public: 
	virtual void draw() = 0;    // pure virtual funcs - must be overloaded

     // Micah Demong - just changed this to be a pure virtual function
     virtual bool intersect(const Ray &ray, glm::vec3 &point, glm::vec3 &normal) = 0;


     void applyTexture(const ofImage img) {
          // Ensuring that the image is valid before applying it
          if (img.isAllocated()) {
               this->texture = img;
               bHasTexture = true;
          }
     }
     
     virtual ofColor getColor(const glm::vec3 point) { return diffuseColor; }
	
	// any data common to all scene objects goes here
	glm::vec3 position = glm::vec3(0, 0, 0);

	// material properties (we will ultimately replace this with a Material class - TBD)
	//
	ofColor diffuseColor = ofColor::grey;    // default colors - can be changed.
	ofColor specularColor = ofColor::white;
     ofImage texture;
     bool bHasTexture = false;

     // Generate a rotation matrix that rotates v1 to v2
     // v1, v2 must be normalized
     //
     glm::mat4 rotateToVector(glm::vec3 v1, glm::vec3 v2) {
          glm::vec3 axis = glm::cross(v1, v2);
          if (axis == glm::vec3(0, 0, 0)) {
               return glm::mat4();
          }
          glm::quat q = glm::angleAxis(glm::angle(v1, v2), glm::normalize(axis));
          return glm::toMat4(q);
     }

     glm::mat4 SceneObject::lookAtMatrix(const glm::vec3 &pos, const glm::vec3 &aimPos, glm::vec3 upVector) {
          glm::mat4 m;

          glm::vec3 g = aimPos - pos;
          glm::vec3 w = glm::normalize(-g);
          glm::vec3 u = glm::normalize(glm::cross(upVector, w));
          glm::vec3 v = glm::normalize(glm::cross(w, u));

          m = { {u, 0}, {v, 0}, {w, 0}, {pos, 1} };

          return m;
     }
};