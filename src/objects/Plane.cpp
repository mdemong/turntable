#include "Plane.h"


Plane::Plane(glm::vec3 p, glm::vec3 n, ofColor diffuse, float w, float h) {
     position = p; 
     normal = n;
     width = w;
     height = h;
     diffuseColor = diffuse;
     plane.rotateDeg(90, 1, 0, 0);
}

// Intersect Ray with Plane  (wrapper on glm::intersect*)
//
bool Plane::intersect(const Ray &ray, glm::vec3 & point, glm::vec3 & normalAtIntersect) {
     float dist;
     bool insidePlane = false;

     bool hit = glm::intersectRayPlane(ray.p, ray.d, position, this->normal, dist);

     if (hit) {

          Ray r = ray;
          point = r.evalPoint(dist);
          normalAtIntersect = this->normal;

          glm::vec2 xrange = glm::vec2(position.x - width / 2, position.x + width / 2);
          glm::vec2 zrange = glm::vec2(position.z - height / 2, position.z + height / 2);

          if (point.x < xrange[1] && point.x > xrange[0] && point.z < zrange[1] && point.z > zrange[0]) {
               insidePlane = true;
          }
     }
     return insidePlane;
}

void Plane::draw() {
     plane.setPosition(position);
     plane.setWidth(width);
     plane.setHeight(height);
     plane.setResolution(4, 4);
     plane.drawWireframe();
}

ofColor Plane::getColor(glm::vec3 point) {
     if (this->bHasTexture) {
          /*
               This only really works for a plane parallel to the ground.
               What this section does:
                  * takes the point and moves it toward the origin
                  * divides it by width (or height) to normalize it
                  * we're now in range (-0.5, 0.5) so we add 0.5 s.t. we're in range (0, 1)
                  * multiply by the number of texture loops
                  * perform fmod w/ 1, so that we keep the decimal part. This is our u (or v) coordinate
          */
          float u = fmod((((point.x - position.x) / this->width) + 0.5) * texWidthLoops, 1);
          float v = fmod((((point.z - position.z) / this->height) + 0.5) * texHeightLoops, 1);
          return getTextureColor(u, v);

     }
     else return this->diffuseColor;
     // convert from worldspace to plane space
          // possibly do this with a naive z-plane-only approach?
     // find u,v coordinate from plane space
     // return getTextureColor(u, v)
}

ofColor Plane::getTextureColor(float u, float v) {
     int i = u * texture.getWidth() - 1;
     int j = v * texture.getHeight() - 1;
     return texture.getColor(i, j);
}

