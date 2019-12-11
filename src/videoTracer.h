#pragma once
#include "ofMain.h"
#include "RayTracer.h"

class VideoTracer {
public:
     RayTracer *tracer;
     //int framerate = 24;
     int maxCycles = 1;
     int currentCycles = 0;
     float thetaPerFrame = 5.0; // degrees
     float radius = 10.0;
     float startAngle = 0;
     float currentAngle = 0;
     string outputDir = "data/video";
     string filePrefix = "img";

     /*
          Constructs a video ray tracer from the given camera, Object vector, and Light vector.
     */
     VideoTracer() {};
     VideoTracer(RenderCam *cam, vector<SceneObject *> objects, vector<Light *> lights);
     void draw(int w, int h);
     void renderVideo();
};