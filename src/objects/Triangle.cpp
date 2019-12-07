#include "Triangle.h"
using namespace std;

/*
	Triangle Class
	Micah Demong
*/

Triangle::Triangle(int index1, int index2, int index3) {
	this->indices = { index1, index2, index3 };
}

Triangle::Triangle(array<int, 3> indices) {
	this->indices = indices;
}

array<int, 3> Triangle::getIndices() {
	return indices;
}

bool Triangle::intersect(const Ray & ray, glm::vec3 & point, glm::vec3 & normal) {
     return false;
}

void Triangle::draw() {
}
