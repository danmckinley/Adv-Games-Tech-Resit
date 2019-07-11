#pragma once

#include ".\include\glew.h"								// Header File For the GLEW Library
#include ".\include\gl.h"								// Header File For the OpenGL32 Library
#include <.\windows.h>

class CSupportBeam {
public:
	CSupportBeam();
	~CSupportBeam();

	void Initialise();
	void preRender();
	void postRender();
	void Render(float r, float g, float b, float a);

private:
	//points 
	//Points for beam starting at the left
	GLfloat v0[3] = {-1, 0, -1 };
	GLfloat v1[3] = { 1, 3, -1 };
	GLfloat v2[3] = {-1, 6, -1 };

	//Points for beam starting at the right
	GLfloat v3[3] = { 1, 0, -1 };
	GLfloat v4[3] = { -1, 3, -1 };
	GLfloat v5[3] = { 1, 6, -1 };
	
};
