#pragma once
#include "ofMain.h"
#include "RayTracer.h"

class VideoTracer {
     RayTracer tracer;
     int framerate = 24;
     float thetaPerFrame = 5.0; // degrees
     float radius = 3.0;

     string outputDir = "data/video";

public:
     void renderVideo();
};