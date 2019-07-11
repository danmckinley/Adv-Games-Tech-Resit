#pragma once

#include ".\include\glew.h"								// Header File For the GLEW Library
#include ".\include\gl.h"								// Header File For the OpenGL32 Library
#include <.\windows.h>

class CTetrahedron {
public:
	CTetrahedron();
	~CTetrahedron();
	void Initialise();
	void preRender();
	void postRender();
	void Render(float r, float g, float b, float a);
	
private:
	GLfloat v0[3] = { -10, 0, -10 };
	GLfloat v1[3] = { 10, 0, -10 };
	GLfloat v2[3] = { 0, 0, 10 };
	GLfloat v3[3] = { 0, 10, 0 };

	UINT m_textureID;
	
};