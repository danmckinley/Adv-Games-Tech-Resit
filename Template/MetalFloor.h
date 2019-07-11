#pragma once

#include ".\include\glew.h"								// Header File For the GLEW Library
#include ".\include\gl.h"								// Header File For the OpenGL32 Library
#include <.\windows.h>

#include "Vector3f.h"

class CMetalFloor {
public:
	CMetalFloor();
	~CMetalFloor();
	void Initialise();
	void preRender();
	void postRender();
	void Render(float r, float g, float b, float a);

	CVector3f Normal(CVector3f a, CVector3f b);

private:
	GLfloat v0[3] = { 0, 0, 0 };
	GLfloat v1[3] = { 4, 0, 0 };
	GLfloat v2[3] = { 4, 0, 4 };
	GLfloat v3[3] = { 0, 0, 4 };

	GLfloat v4[3] = { 0, 0.5, 0 };
	GLfloat v5[3] = { 4, 0.5, 0 };
	GLfloat v6[3] = { 4, 0.5, 4 };
	GLfloat v7[3] = { 0, 0.5, 4 };

	UINT m_textureID;
};