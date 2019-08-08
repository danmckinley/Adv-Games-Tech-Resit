#pragma once
#include <windows.h>									// Header File For The Windows Library

#include ".\include\gl.h"											// Header File For The OpenGL32 Library
#include "Vector3f.h"


class CTerrain
{
public:
	CTerrain();
	~CTerrain();
	bool Initialise();
	void Render();
	CVector3f *m_polygons;				// array of polygons for the purpose of adding to the game data array in game.cpp
	CVector3f v0, v1, v2, v3;
	GLfloat length, width;

	
private:
	UINT m_textureID;
	
};