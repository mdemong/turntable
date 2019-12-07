#pragma once

#include <vector>
#include "ofMain.h"
#include "Triangle.h"

/*
	Mesh Class
	Micah Demong

	Represents a triangle mesh using an indexed triangle set data structure.
*/

class Mesh {
	vector<glm::vec3> vertices;
	vector<Triangle> triangles;
	

public:
	Mesh();

	/*
		Creates a Mesh from the specified filepath.
		If the file does not exist, an exception will be thrown.
	*/
	Mesh(string filepath);

	/*
		Constructs a triangle mesh with the given lists of vertices and triangles.
	*/
	Mesh(vector<glm::vec3> vertices, vector<Triangle> triangles);

	/*
		Draws the Mesh.
	*/
	void draw();

	/*
		Returns the number of faces in this Mesh.	
	*/
	int polyCount();

	/*
		Returns the number of vertices in this Mesh.
	*/
	int vertCount();

	/*
		Returns the size in bytes of this Mesh.
	*/
	int size();
};