#pragma once
#include "ofMain.h"
#include "RayTracer.h"

class VideoTracer {
public:

     // Unchanging //
     RayTracer *tracer;
     //int framerate = 24;
     int maxCycles = 1;
     float thetaPerFrame = 5.0; // degrees
     float radius = 10.0;
     string outputDir = "video/";
     string filePrefix = "img";
     string fileType = ".png";
     float width = 600;
     float height = 400;

     // Incrementing //
     float currentAngle = 0;
     int currentCycles = 0;
     int currentFrame = 0;
     /*
          Constructs a video ray tracer from the given camera, Object vector, and Light vector.
     */
     VideoTracer() {};
     VideoTracer(RenderCam *cam, vector<SceneObject *> objects, vector<Light *> lights);
     void draw(int w, int h);
     void renderVideo();
     glm::vec3 getPosition();
};