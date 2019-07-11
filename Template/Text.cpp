#include "Text.h"


DWORD CText::m_listBaseCount = 1000;

CText::CText()
{}

CText::~CText()
{}



void CText::SetOrthographicProjection()
{
	// Get the viewport matrix to get the width and height of the window
	GLint m_viewport[4];
	glGetIntegerv(GL_VIEWPORT, m_viewport);

	// Switch to projection mode
	glMatrixMode(GL_PROJECTION);
	// save previous matrix which contains the settings for the perspective projection
	glPushMatrix();
	// reset matrix
	glLoadIdentity();
	// set a 2D orthographic projection based on the window size
	gluOrtho2D(0, m_viewport[2], 0, m_viewport[3]);

	glMatrixMode(GL_MODELVIEW);
}


void CText::ResetPerspectiveProjection() {
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}

void CText::Create(HDC hdc, char *fontName, int size)
{
	// Create a Windows font
	HFONT font = ::CreateFont(-size, 0, 0, 0, size, FALSE, FALSE, FALSE, 
							ANSI_CHARSET, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FF_DONTCARE|DEFAULT_PITCH, fontName);
 
	m_listBase = m_listBaseCount;
	// Select into device context and call wglUseFontBitmaps
	HFONT fontOld = (HFONT) SelectObject(hdc, font);
	wglUseFontBitmaps (hdc, 0, 255, m_listBase);
	m_listBaseCount += 255;
	SelectObject(hdc, fontOld);
}

void CText::RenderBitmapString(float x, float y, char *string)
{
	glRasterPos2f(x, y);
	glListBase (m_listBase);
	glCallLists (strlen(string), GL_UNSIGNED_BYTE, string);
}

void CText::Render(char *text, float x, float y, float r, float g, float b)
{
	glColor3f(r, g, b);
	glDisable(GL_TEXTURE_2D);
	glPushMatrix();
		SetOrthographicProjection();
		glLoadIdentity();
		RenderBitmapString(x, y, text);
		ResetPerspectiveProjection();
	glPopMatrix();
	glEnable(GL_TEXTURE_2D);
}