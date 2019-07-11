#include "Tetrahedron.h"
#include "Texture.h"
#include <windows.h>
#include ".\include\gl.h"

CTetrahedron::CTetrahedron() {
}

CTetrahedron::~CTetrahedron()
{
}

void CTetrahedron::Initialise()
{
	CTexture texture;
	texture.Load("Resources\\Textures\\croppedRockTexture.bmp", false);
	m_textureID = texture.m_textureID;
}

void CTetrahedron::Render(float r, float g, float b, float a) {
	preRender();
	glPushMatrix(); {
		glColor4f(r, g, b, a);
		glBegin(GL_TRIANGLES);
		glTexCoord2f(0, 0);
		glVertex3fv(v2);
		glTexCoord2f(0.5, 1);
		glVertex3fv(v3);
		glTexCoord2f(1, 0);
		glVertex3fv(v0);
		glEnd();
		glBegin(GL_TRIANGLES);
		glTexCoord2f(0, 0);
		glVertex3fv(v0);
		glTexCoord2f(0.5, 1);
		glVertex3fv(v3);
		glTexCoord2f(1, 0);
		glVertex3fv(v1);
		glEnd();
		glBegin(GL_TRIANGLES);
		glTexCoord2f(0, 0);
		glVertex3fv(v3);
		glTexCoord2f(0.5, 1);
		glVertex3fv(v2);
		glTexCoord2f(1, 0);
		glVertex3fv(v1);
		glEnd();
		glBegin(GL_TRIANGLES);
		glTexCoord2f(0, 0);
		glVertex3fv(v1);
		glTexCoord2f(0.5, 1);
		glVertex3fv(v2);
		glTexCoord2f(1, 0);
		glVertex3fv(v0 );
		glEnd();
	}
	glPopMatrix();
	postRender();
}


void CTetrahedron::preRender() {
	glEnable(GL_TEXTURE_2D);					// disable for no texutre
	glBindTexture(GL_TEXTURE_2D, m_textureID);  // disable for no texture
	//glDisable(GL_TEXTURE_2D);		//for rendering without a texture
	glDisable(GL_LIGHTING);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void CTetrahedron::postRender() {
	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
}