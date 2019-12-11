#include "videoTracer.h"


VideoTracer::VideoTracer(RenderCam * cam, vector<SceneObject*> objects, vector<Light*> lights) {
     this->tracer = new RayTracer(cam, objects, lights);

}

void VideoTracer::draw(int w, int h) {
     this->tracer->draw(w, h);
}



void VideoTracer::renderVideo() {

}
