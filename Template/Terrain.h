#pragma once
#include <windows.h>									// Header File For The Windows Library

#include ".\include\gl.h"											// Header File For The OpenGL32 Library


class CTerrain
{
public:
	CTerrain();
	~CTerrain();
	bool Initialise();
	void Render();

	
private:
	UINT m_textureID;
	
};