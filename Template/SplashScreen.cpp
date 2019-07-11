#include "SplashScreen.h"

CSplashScreen::CSplashScreen() {}
CSplashScreen::~CSplashScreen() {}

void CSplashScreen::Initialise() {
	CTexture texture;
	texture.Load("Resources\\Textures\\splashscreen.jpg", false);
	m_textureID = texture.m_textureID;
}

void CSplashScreen::preRender() {
	// Set the OpenGL state and go to 2D mode
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);					
	glBindTexture(GL_TEXTURE_2D, m_textureID);  
	glDisable(GL_LIGHTING);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	SetOrthographicProjection();
	glLoadIdentity();
}

void CSplashScreen::postRender() {
	// Go back to 3D mode (perspective projection)
	RestorePerspectiveProjection();
	glPopMatrix();
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
}

void CSplashScreen::SetOrthographicProjection() {
	// Switches to orthographic (2D) rendering
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();

	glGetIntegerv(GL_VIEWPORT, m_viewport);
	int w = m_viewport[2];	//width of game window
	int h = m_viewport[3];	//height of game window

	gluOrtho2D(0, w, 0, h);
	glMatrixMode(GL_MODELVIEW);
}

void CSplashScreen::RestorePerspectiveProjection() {
	// Returns to 3D rendering mode
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}

void CSplashScreen::Render(float r, float g, float b, float a) {
	
	preRender();
	// Render full screen quad
	float w = (float)m_viewport[2];
	float h = (float)m_viewport[3];
	glColor4f(r, g, b, a);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(0, 0, 0);
	glTexCoord2f(1, 0); glVertex3f(w, 0, 0);
	glTexCoord2f(1, 1); glVertex3f(w, h, 0);
	glTexCoord2f(0, 1); glVertex3f(0, h, 0);
	glEnd();
	postRender();
}