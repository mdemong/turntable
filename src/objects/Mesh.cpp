#pragma once

using namespace std;

#include "Mesh.h"
#include <vector>
#include <fstream>
#include <regex>

/*
	Mesh Class
	Micah Demong
*/

Mesh::Mesh()
{
	this->vertices = vector<glm::vec3>();
	this->triangles = vector<Triangle *>();
}

Mesh::Mesh(string filepath) 
{
	this->vertices = vector<glm::vec3>();
	this->triangles = vector<Triangle *>();

	// File read operations referenced from http://www.cplusplus.com/doc/tutorial/files/

	ifstream meshFile;
	meshFile.open(filepath);
	string line;

	while (getline(meshFile, line)) {

		// Regular expression operations are referenced from https://stackoverflow.com/a/35026140 
		// and the Strings/Regex section of "A Tour of C++" by Bjarne Stroustrup

		// Vertices
		if (regex_match(line, regex("v(-?[ .0-9])"))) {

			// cout << "VERTEX " << line << endl;

			auto coordinates = vector<float>();

			string::const_iterator searchStart(line.cbegin());
			smatch result;

			// Iterating through vertex float values on this line
			while (regex_search(searchStart, line.cend(), result, regex("(-?[0-9.])+"))) {
				coordinates.push_back(stof(result.str()));

				searchStart = result.suffix().first;
			}

			// A coordinate should have exactly 3 values; i.e. an X, Y, Z coordinate
			if (coordinates.size() == 3) {
				this->vertices.push_back(glm::vec3(coordinates[0], coordinates[1], coordinates[2]));
			}
			else {
				// If we don't have three coordinates, something is wrong with the file.
				throw "Vertex has unexpected number of arguments";
			}
		}

          // Faces
          else if (regex_match(line, regex("f[ 0-9//]+"))) {

               //cout << "FACE " << line << endl;

               auto shapeIndices = vector<int>();

               string::const_iterator searchStart(line.cbegin());
               smatch result;

               // Iterating through "slash strings" (e.g. 770/936/777)
               while (regex_search(searchStart, line.cend(), result, regex("[0-9/]+"))) {
                    smatch indexMatch;
                    string slashString = result[0];

                    // Just get the first match for an integer; 
                    // we don't care about normals or texture coordinates right now.
                    regex_search(slashString, indexMatch, regex("[0-9]+"));

                    // .OBJ files are 1-indexed, so we need to subtract 1 here
                    shapeIndices.push_back(stoi(indexMatch.str()) - 1);

                    searchStart = result.suffix().first;
               }

               if (shapeIndices.size() == 3) {
                    triangles.push_back(new Triangle(shapeIndices[0], shapeIndices[1], shapeIndices[2]));
               }
               else if (shapeIndices.size() == 4) {
                    // If we have a quad, split it into 2 triangles
                    triangles.push_back(new Triangle(shapeIndices[0], shapeIndices[1], shapeIndices[2])); 
                    triangles.push_back(new Triangle(shapeIndices[0], shapeIndices[2], shapeIndices[3]));
               }
               else {
                    // The monster-quad model has a few 5-vertex faces which trigger this section.
                    cout << "Face has " << shapeIndices.size() << " vertices; skipping" << endl;
               }
          }
     }
}

Mesh::Mesh(vector<glm::vec3> vertices, vector<Triangle *> triangles) {
	this->vertices = vertices;
	this->triangles = triangles;
}

void Mesh::draw() {
	for each (Triangle *tri in triangles) {
		auto indices = tri->getIndices();
		
		ofSetColor(255, 0, 255);
		ofDrawLine(vertices.at(indices[0]), vertices.at(indices[1]));
		ofDrawLine(vertices.at(indices[1]), vertices.at(indices[2]));
		ofDrawLine(vertices.at(indices[2]), vertices.at(indices[0]));
	}
}

bool Mesh::intersect(const Ray & ray, glm::vec3 & point, glm::vec3 & normal) {
     for (Triangle *t : this->triangles) {
          // TODO: somehow intersect with a mesh lol
     }
     return false;
}

int Mesh::polyCount() {
	return triangles.size();
}

int Mesh::vertCount() {
	return vertices.size();
}

int Mesh::size() {
	return vertices.size() * sizeof(glm::vec3) 
		+ triangles.size() * sizeof(Triangle) 
		+ sizeof(this);
}
