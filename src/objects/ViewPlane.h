#pragma once
#include "Plane.h"
#include "ofMain.h"

/*
     View Plane class
*/

class  ViewPlane: public Plane {
public:

	ViewPlane(glm::vec2 p0, glm::vec2 p1) { min = p0; max = p1; }
     ViewPlane();
	void setSize(glm::vec2 min, glm::vec2 max) { this->min = min; this->max = max; }
	float getAspect() { return width() / height(); }
	glm::vec3 toWorld(float u, float v);   //   (u, v) --> (x, y, z) [ world space ]
        	
	float width() { return (max.x - min.x); }
	float height() { return (max.y - min.y);}

	// some convenience methods for returning the corners
	//
	glm::vec2 topLeft() { return glm::vec2(min.x, max.y); }
	glm::vec2 topRight() { return max; }
	glm::vec2 bottomLeft() { return min;  }
	glm::vec2 bottomRight() { return glm::vec2(max.x, min.y); }

     /*
          Micah Demong

          Draws the outline of the ViewPlane.
     */
     void draw();

     /*
          Micah Demong

          Draws a wireframe with the given number of "pixels" in the horizontal
          and vertical directions.
     */
     void drawWireframe(int horizPixels, int vertPixels);


	//  To define an infinite plane, we just need a point and normal.
	//  The ViewPlane is a finite plane so we need to define the boundaries.
	//  We will define this in terms of min, max  in 2D.  
	//  (in local 2D space of the plane)
	//  ultimately, will want to locate the ViewPlane with RenderCam anywhere
	//  in the scene, so it is easier to define the View rectangle in a local'
	//  coordinate system.
	//
	glm::vec2 min, max;
};