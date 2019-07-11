#include "MetalFloor.h"
#include "Texture.h"
#include <windows.h>
#include ".\include\gl.h"

//metal texture from "http://www.photos-public-domain.com/2017/04/04/old-gray-tin-metal-texture/"

CMetalFloor::CMetalFloor() {}

CMetalFloor::~CMetalFloor() {}

void CMetalFloor::Initialise() {
	CTexture texture;
	texture.Load("Resources\\Textures\\MetalTexture.jpg", false);
	m_textureID = texture.m_textureID;

}

void CMetalFloor::preRender() {
	//glDisable(GL_TEXTURE_2D);					// enable for no texture
	glEnable(GL_TEXTURE_2D);					// disable for no texutre
	glBindTexture(GL_TEXTURE_2D, m_textureID);  // disable for no texture
	glEnable(GL_LIGHTING);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void CMetalFloor::postRender() {
	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
}

void CMetalFloor::Render(float r, float g, float b, float a) {
	preRender();
	glPushMatrix(); {
		glColor4f(r, g, b, a);
		glBegin(GL_QUAD_STRIP); {	//Renders two sides, and the top and bottom of a cuboid
			glTexCoord2f(1, 0); glVertex3fv(v1);
			glTexCoord2f(0, 0); glVertex3fv(v0);
			glTexCoord2f(1, 1); glVertex3fv(v5);
			glTexCoord2f(0, 1); glVertex3fv(v4);
			glTexCoord2f(1, 0); glVertex3fv(v6);
			glTexCoord2f(0, 0); glVertex3fv(v7);
			glTexCoord2f(1, 1); glVertex3fv(v2);
			glTexCoord2f(0, 1); glVertex3fv(v3);
			glTexCoord2f(1, 0); glVertex3fv(v1);
			glTexCoord2f(0, 0); glVertex3fv(v0);
		}
		glEnd();
		glBegin(GL_QUADS); {		//renders the "left" side
			glTexCoord2f(1, 1); glVertex3fv(v4);
			glTexCoord2f(1, 0); glVertex3fv(v0);
			glTexCoord2f(0, 0); glVertex3fv(v3);
			glTexCoord2f(0, 1); glVertex3fv(v7);
		}
		glEnd();
		glBegin(GL_QUADS); {		//renders the "right" side
			glTexCoord2f(1, 1); glVertex3fv(v6);
			glTexCoord2f(1, 0); glVertex3fv(v2);
			glTexCoord2f(0, 0); glVertex3fv(v1);
			glTexCoord2f(0, 1); glVertex3fv(v5);
		}
		glEnd();
	}
	glPopMatrix();
	postRender();
}

CVector3f CMetalFloor::Normal(CVector3f p, CVector3f q) {	// Method to calculate normals
	float a = p.y*q.z - p.z*q.y;
	float b = p.z*q.x - p.x*q.z;
	float c = p.x*q.y - p.y*q.x;
	
	return CVector3f(a, b, c);
}