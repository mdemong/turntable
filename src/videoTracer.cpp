#include "videoTracer.h"


VideoTracer::VideoTracer(RenderCam * cam, vector<SceneObject*> objects, vector<Light*> lights) {
     this->tracer = new RayTracer(cam, objects, lights);

}

void VideoTracer::draw(int w, int h) {
     this->tracer->draw(w, h);
}

void VideoTracer::renderVideo() {
     while (currentCycles < maxCycles) {

          // position
          tracer->setPosition(this->getPosition());
          tracer->lookAt({ 0, 0, 0 });

          // render
          cout << "Rendering frame " << currentFrame << endl;
          ofImage frameOut = tracer->rayTrace(this->width, this->height);
          stringstream ss;
          ss << this->outputDir << this->filePrefix
               << std::setfill('0') << std::setw(4)
               << currentFrame << fileType;
          frameOut.save(ss.str());

          // increment things
          currentAngle += thetaPerFrame;
          currentFrame++;
          if (currentAngle >= 360.0) {
               currentAngle = fmod(currentAngle, 360.0);
               currentCycles++;
          }

     }
}
glm::vec3 VideoTracer::getPosition() {
     auto startVector = glm::vec3(0, 0, radius);
     return glm::rotateY(startVector, glm::radians(currentAngle));
}


