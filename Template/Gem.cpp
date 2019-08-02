#include "Gem.h"

CGem::CGem() {
	v0 = CVector3f(0, 0, 0);	// top

	v1 = CVector3f(-0.5f, 1.0f, -0.5f);	// sides
	v2 = CVector3f(0.5f, 1.0f, -0.5f);
	v3 = CVector3f(0.5f, 1.0f, 0.5f);
	v4 = CVector3f(-0.5f, 1.0f, 0.5f);

	v5 = CVector3f(0, 2, 0);	// bottom
	m_rotationAngle = 0;
}

void CGem::Initialise() {
	SetTexture("Resources\\Textures\\gem-texture.jpg");
}


void CGem::Render() {
	SetPolygonsToWorldCoords();
	preRender();
	glPushMatrix(); {
		ApplySort();
		glBlendFunc(GL_ONE, GL_ONE); // enables alpha blending on textured surface (https://www.opengl.org/archives/resources/faq/technical/transparency.htm @15.080)
		glColor4f(0.5, 0.5, 1.0, 0.5);
		glBegin(GL_TRIANGLE_FAN); { // Renders bottom half of octahedron
			glNormal3fv(Normal(v4, v2)); glTexCoord2f(0.5, 1);		glVertex3f(v0.x, v0.y, v0.z);
			glNormal3fv(Normal(v2, v4)); glTexCoord2f(0, 0.5);		glVertex3f(v1.x, v1.y, v1.z);
			glNormal3fv(Normal(v1, v3)); glTexCoord2f(1, 0.5);	glVertex3f(v2.x, v2.y, v2.z);
			glNormal3fv(Normal(v4, v2)); glTexCoord2f(0, 0.5);	glVertex3f(v3.x, v3.y, v3.z);
			glNormal3fv(Normal(v3, v1)); glTexCoord2f(1, 0.5);		glVertex3f(v4.x, v4.y, v4.z);
			glNormal3fv(Normal(v2, v4)); glTexCoord2f(0, 0.5);		glVertex3f(v1.x, v1.y, v1.z);
		}
		glEnd();
		glBegin(GL_TRIANGLE_FAN); {	//Renders top half of octahedron
			glNormal3fv(Normal(v2, v4)); glTexCoord2f(0.5, 0);		glVertex3f(v5.x, v5.y, v5.z);
			glNormal3fv(Normal(v1, v3)); glTexCoord2f(0, 0.5);		glVertex3f(v4.x, v4.y, v4.z);
			glNormal3fv(Normal(v2, v4)); glTexCoord2f(1, 0.5);		glVertex3f(v3.x, v3.y, v3.z);
			glNormal3fv(Normal(v1, v3)); glTexCoord2f(0, 0.5);		glVertex3f(v2.x, v2.y, v2.z);
			glNormal3fv(Normal(v2, v4)); glTexCoord2f(1, 0.5);		glVertex3f(v1.x, v1.y, v1.z);
			glNormal3fv(Normal(v1, v3)); glTexCoord2f(0, 0.5);		glVertex3f(v4.x, v4.y, v4.z);
		}
		glEnd();
		glPopMatrix();
	}
	postRender();
	Rotate();
}

void CGem::Rotate(){
	if (m_rotationAngle < 360) {
		m_rotationAngle += 2;
	}
	else {
		m_rotationAngle = 0;
	}
	SetRotation(m_rotationAngle, 0, 1, 0);
}
