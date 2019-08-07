#include "MetalFloor.h"

//#include ".\include\gl.h"

//metal texture from "http://www.photos-public-domain.com/2017/04/04/old-gray-tin-metal-texture/"

CMetalFloor::CMetalFloor(){
	v0 = CVector3f(-1.5f, 0.0f, -1.5f);
	v1 = CVector3f(1.5f, 0.0f, -1.5f);
	v2 = CVector3f(1.5f, 0.0f, 1.5f);
	v3 = CVector3f(-1.5f, 0.0f, 1.5f);

	v4 = CVector3f(-1.5f, 0.33f, -1.5f);
	v5 = CVector3f(1.5f, 0.33f, -1.5f);
	v6 = CVector3f(1.5f, 0.33f, 1.5f);
	v7 = CVector3f(-1.5f, 0.33f, 1.5f);
	SetPolygonsToWorldCoords();
}

void CMetalFloor::Initialise() {
	SetTexture("Resources\\Textures\\MetalTexture.jpg");
}

void CMetalFloor::Render() {
	preRender();
	glPushMatrix(); {
		ApplySort();
		glBegin(GL_QUAD_STRIP); {	//Renders two sides, and the top and bottom of a cuboid
			glNormal3fv(Normal(v1, v0)); glTexCoord2f(1, 0); glVertex3f(v1.x, v1.y, v1.z);
			glNormal3fv(Normal(v0, v5)); glTexCoord2f(0, 0); glVertex3f(v0.x, v0.y, v0.z);
			glNormal3fv(Normal(v5, v4)); glTexCoord2f(1, 1); glVertex3f(v5.x, v5.y, v5.z);
			glNormal3fv(Normal(v4, v6)); glTexCoord2f(0, 1); glVertex3f(v4.x, v4.y, v4.z);
			glNormal3fv(Normal(v6, v7)); glTexCoord2f(1, 0); glVertex3f(v6.x, v6.y, v6.z);
			glNormal3fv(Normal(v7, v2)); glTexCoord2f(0, 0); glVertex3f(v7.x, v7.y, v7.z);
			glNormal3fv(Normal(v2, v3)); glTexCoord2f(1, 1); glVertex3f(v2.x, v2.y, v2.z);
			glNormal3fv(Normal(v3, v1)); glTexCoord2f(0, 1); glVertex3f(v3.x, v3.y, v3.z);
			glNormal3fv(Normal(v1, v0)); glTexCoord2f(1, 0); glVertex3f(v1.x, v1.y, v1.z);
			glNormal3fv(Normal(v0, v1)); glTexCoord2f(0, 0); glVertex3f(v0.x, v0.y, v0.z);
		}
		glEnd();
		glBegin(GL_QUADS); {		//renders the "left" side
			glNormal3fv(Normal(v4, v0)); glTexCoord2f(1, 1); glVertex3f(v4.x, v4.y, v4.z);
			glNormal3fv(Normal(v0, v3)); glTexCoord2f(1, 0); glVertex3f(v0.x, v0.y, v0.z);
			glNormal3fv(Normal(v3, v7)); glTexCoord2f(0, 0); glVertex3f(v3.x, v3.y, v3.z);
			glNormal3fv(Normal(v7, v4)); glTexCoord2f(0, 1); glVertex3f(v7.x, v7.y, v7.z);
		}
		glEnd();
		glBegin(GL_QUADS); {		//renders the "right" side
			glNormal3fv(Normal(v6, v2)); glTexCoord2f(1, 1); glVertex3f(v6.x, v6.y, v6.z);
			glNormal3fv(Normal(v2, v1)); glTexCoord2f(1, 0); glVertex3f(v2.x, v2.y, v2.z);
			glNormal3fv(Normal(v1, v5)); glTexCoord2f(0, 0); glVertex3f(v1.x, v1.y, v1.z);
			glNormal3fv(Normal(v5, v6)); glTexCoord2f(0, 1); glVertex3f(v5.x, v5.y, v5.z);
		}
		glEnd();
	}
	glPopMatrix();
	postRender();
}