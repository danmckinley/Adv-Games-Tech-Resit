#pragma once
#include <windows.h>

#include ".\include\gl.h"
#include "Texture.h"
#include "Vector3f.h"
#include <vector>

class CSplashScreen {
public:
	CSplashScreen();
	~CSplashScreen();

	void Initialise();

	void SetLoseScreen();

	void SetWinScreen();

	void preRender();

	void postRender();

	GLint m_viewport[4];
	void SetOrthographicProjection();
	void RestorePerspectiveProjection();

	void Render(float r, float g, float b, float a);
private:
	UINT m_textureID;
	CTexture introScreen;
	CTexture winScreen;
	CTexture loseScreen;

};

