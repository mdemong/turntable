#pragma once
using namespace std;

#include <array>

/*
	Triangle Class
	Micah Demong

	A simple container class for a Triangle index list.
*/

class Triangle {
	array<int, 3> indices;

public:
	Triangle(int index1, int index2, int index3);
	Triangle(array<int, 3> indices);
	array<int, 3> getIndices();
};