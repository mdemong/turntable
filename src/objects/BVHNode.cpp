#include "BVHNode.h"

BVHNode::BVHNode()
{
}

bool BVHNode::intersect(const Ray & ray, glm::vec3 & point, glm::vec3 & normal)
{
     glm::vec3 leftPt, leftNormal, rightPt, rightNormal;
     bool bLeftHit = (left != NULL) && (left->intersect(ray, leftPt, leftNormal));
     bool bRightHit = (right != NULL) && (right->intersect(ray, rightPt, rightNormal));
     float leftDistSq = glm::distance2(leftPt, ray.p);     
     float rightDistSq = glm::distance2(rightPt, ray.p);


     if (bLeftHit && bRightHit) {
          if (leftDistSq < rightDistSq) {
               point = leftPt;
               normal = leftNormal;
          }
          else {
               point = rightPt;
               normal = leftNormal;
          }
          return true;
     }
     else if (bLeftHit) {
          point = leftPt;
          normal = leftNormal;
          return true;
     }
     else if (bRightHit) {
          point = rightPt;
          normal = rightNormal;
          return true;
     }
     else return false;
}
