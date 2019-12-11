#include "RayTracer.h"

const int SUBPIXEL_COUNT = 2;

RayTracer::RayTracer() {

}


RayTracer::RayTracer(RenderCam *cam, vector<SceneObject *> objects, vector<Light *> lights) {
     this->cam = cam;
     this->objects = objects;
     this->lights = lights;
}


void RayTracer::draw(int imgWidth, int imgHeight) {
     float widthIncrement = 1.0 / (float)imgWidth;
     float heightIncrement = 1.0 / (float)imgHeight;

     // Initial values are increments divided by 2, so that we're
     // sending rays exactly in the center of each pixel.
     float initWidth = widthIncrement / 2.0;
     float initHeight = heightIncrement / 2.0;

     ofSetColor(ofColor::cyan);

     for (float i = initWidth; i < 1; i += widthIncrement) {
          for (float j = initHeight; j < 1; j += heightIncrement) {
               Ray r = this->cam->getRay(i, j);
               r.draw(10);
          }
     }

     ofSetColor(ofColor::white);
}

ofImage RayTracer::rayTrace(int imgWidth, int imgHeight) {

     std::clock_t start;
     double duration;

     start = std::clock();

     ofImage outputImage = ofImage();
     outputImage.allocate(imgWidth, imgHeight, ofImageType::OF_IMAGE_COLOR);

     outputImage.setColor(ofColor::black);
     
     for (int i = 0; i < imgWidth; i ++) {

          for (int j = 0; j < imgHeight; j ++) {

               // Algorithm referenced from Fundamentals of Computer Graphics, page 330
               ofColor pixelColor = ofColor::black;
               int red = 0, green = 0, blue = 0;

               for (int p = 0; p < SUBPIXEL_COUNT; p++) {
                    for (int q = 0; q < SUBPIXEL_COUNT; q++) {
                         float rayX = (i + ((p + 0.5) / SUBPIXEL_COUNT)) / imgWidth;
                         float rayY = 1 - ((j + ((q + 0.5) / SUBPIXEL_COUNT)) / imgHeight);
                         Ray ray = this->cam->getRay(rayX, rayY);
                         ofColor rayColor = getRayColor(ray);
                         red += rayColor.r;
                         green += rayColor.g;
                         blue += rayColor.b;
                    }
               }

               //cout << red << " " << green << " " << blue << endl;

               ofColor finalColor;
               finalColor.r = red / (SUBPIXEL_COUNT * SUBPIXEL_COUNT);
               finalColor.g = green / (SUBPIXEL_COUNT * SUBPIXEL_COUNT);
               finalColor.b = blue / (SUBPIXEL_COUNT * SUBPIXEL_COUNT);

               //cout << finalColor << endl;

               outputImage.setColor(i, j, finalColor);

               //// These offsets are used so we send the rays from the center of the pixel.
               //float xOffset = (1.0 / (float)imgWidth) / 2.0;
               //float yOffset = (1.0 / (float)imgHeight) / 2.0;

               //float pixelX = ((float) i / imgWidth) + xOffset;
               //float pixelY = 1 - (((float) j / imgHeight) + yOffset);

               //Ray ray = this->cam.getRay(pixelX, pixelY);

               //outputImage.setColor(i, j, getRayColor(ray));
          }
     }

     duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;
     std::cout << "raytrace took " << duration << " seconds" << endl;

     return outputImage;
}


ofColor RayTracer::getRayColor(Ray &r)
{
     float minDist2 = std::numeric_limits<float>::infinity();
     ofColor color = ofColor::black;

     for (auto obj : this->objects) {

          glm::vec3 point;
          glm::vec3 normal;

          auto intersected = obj->intersect(r, point, normal);

          if (intersected) {

               float dist2 = glm::distance2(point, cam->position);

               if (dist2 < minDist2) {

                    minDist2 = dist2;

                    // TODO: this section could be optimized

                    // For now, we're just setting this pixel color to diffuseColor.
                    ofColor diffuse = obj->getColor(point);
                    color = this->ambientColor;
                    color += phong_lambert(point, normal, diffuse, obj->specularColor, this->phongPower);
                    //color += lambert(point, normal, diffuse);
                    //color += phong(point, normal, diffuse, obj->specularColor, this->phongPower);
               }
          }
     }
     return color;
}



ofColor RayTracer::lambert(const glm::vec3 & p, const glm::vec3 & norm, const ofColor diffuse) {
     ofColor lambertColor = ofColor::black;
     for (auto light : this->lights) {
          glm::vec3 light_dir = glm::normalize(light->position - p);

          // This returns illumination: i.e. I/(r^2)
          float illumination = light->getIllumination(p);
          
          lambertColor += diffuse * illumination * max(0.0f, glm::dot(norm, light_dir));
          
     }
     return lambertColor;
}

ofColor RayTracer::phong(const glm::vec3 & p, const glm::vec3 & norm, const ofColor diffuse, const ofColor specular, float power) {
     ofColor phongColor = ofColor::black;
     for (auto light : this->lights) {
          glm::vec3 v = glm::normalize(cam->position - p);
          glm::vec3 l = glm::normalize(light->position - p);
          glm::vec3 h = bisector(v, l);
          float illumination = light->getIllumination(p);
          phongColor += specular * illumination * this->phongLightIntensity * glm::pow(max(0.0f, glm::dot(norm, h)), power);
     }
     return phongColor;
}

ofColor RayTracer::phong_lambert(const glm::vec3 & p, const glm::vec3 & norm, const ofColor diffuse, const ofColor specular, float power) {
     ofColor lambertColor = ofColor::black;
     ofColor phongColor = ofColor::black;
     for (auto light : this->lights) {
          glm::vec3 v = glm::normalize(cam->position - p);
          glm::vec3 l = glm::normalize(light->position - p);
          glm::vec3 h = bisector(v, l);
          float illumination = light->getIllumination(p);

          if(!inShadow(Ray(p + .0001 * l, l))) {
               phongColor += specular * illumination * this->phongLightIntensity * glm::pow(max(0.0f, glm::dot(norm, h)), power);
               lambertColor += diffuse * illumination * max(0.0f, glm::dot(norm, l));
          }
     }
     return phongColor + lambertColor;
}

bool RayTracer::inShadow(const Ray &r) {

     for (auto object : objects) {
          glm::vec3 point;
          glm::vec3 normal;
          if (object->intersect(r, point, normal)) {
               return true;
          }
     }
     // If we reach here, no hits.
     return false;
}

glm::vec3 bisector(glm::vec3 vecA, glm::vec3 vecB) {
     return glm::normalize((vecA + vecB) / (vecA + vecB).length());
}




