#pragma once
#include <windows.h>									// Header File For The Windows Library
#include ".\include\gl.h"								// Header File For The OpenGL32 Library
#include "Vector3f.h"
#include "Texture.h"

class CExplosionSprite
{
public:
	CExplosionSprite();
	~CExplosionSprite();
	bool Initialise();
	void Update(float dt);
	void Render(CVector3f p, CVector3f lookAt, CVector3f upVector, float width, float height);
	void Activate();

private:

	bool m_active;

	unsigned int m_frame;
	unsigned int m_totalFrames;
	float m_elapsedTime;

	unsigned int m_frameWidth;
	unsigned int m_frameHeight;

	unsigned int m_framesX;
	unsigned int m_framesY;


	CTexture m_texture;

}; 
