#include "Gem.h"

CGem::CGem() {
	// vertices
	v0 = CVector3f(0.0f, 0.0f, 0.0f);	// top

	v1 = CVector3f(-0.25f, 0.75f, -0.25f);	// sides
	v2 = CVector3f(0.25f, 0.75f, -0.25f);
	v3 = CVector3f(0.25f, 0.75f, 0.25f);
	v4 = CVector3f(-0.25f, 0.75f, 0.25f);

	v5 = CVector3f(0.0f, 1.5f, 0.0f);	// bottom
}

void CGem::Initialise() {
	//SetTexture("Resources\\Textures\\ShippingContainer.jpg");
}


/*
CVector3f Normal(CVector3f vPolygon[]) {	//method to calculate normals from an array of 3 CVectors, returning a CVector
	CVector3f vVector1 = vPolygon[2] - vPolygon[0];
	CVector3f vVector2 = vPolygon[1] - vPolygon[0];
	CVector3f vNormal = vVector1 % vVector2;
	vNormal.Normalise();
	return vNormal;
}
*/

void CGem::Render() {
	SetPolygonsToWorldCoords();
	preRender();
	glPushMatrix(); {
		ApplySort();
		glColor3f(0.0, 1.0, 0.0);
		glBegin(GL_TRIANGLE_FAN); {	//Renders bottom half of octahedron
			glNormal3fv(VertexNormal(v0, v1, v3)); glTexCoord2f(0, 0);		glVertex3f(v0.x, v0.y, v0.z);
			glNormal3fv(VertexNormal(v1, v0, v2)); glTexCoord2f(0, 1);		glVertex3f(v1.x, v1.y, v1.z);
			glNormal3fv(VertexNormal(v2, v0, v3)); glTexCoord2f(0.285, 0);	glVertex3f(v2.x, v2.y, v2.z);
			glNormal3fv(VertexNormal(v3, v0, v4)); glTexCoord2f(0.285, 1);	glVertex3f(v3.x, v3.y, v3.z);
			glNormal3fv(VertexNormal(v4, v0, v1)); glTexCoord2f(1, 0);		glVertex3f(v4.x, v4.y, v4.z);
			glNormal3fv(VertexNormal(v1, v0, v2)); glTexCoord2f(1, 1);		glVertex3f(v1.x, v1.y, v1.z);
		}
		glEnd();
		glBegin(GL_TRIANGLE_FAN); {	//Renders top half of octahedron
			glNormal3fv(VertexNormal(v5, v1, v3)); glTexCoord2f(0, 0);		glVertex3f(v5.x, v5.y, v5.z);
			glNormal3fv(VertexNormal(v4, v5, v1)); glTexCoord2f(1, 0);		glVertex3f(v4.x, v4.y, v4.z);
			glNormal3fv(VertexNormal(v3, v5, v4)); glTexCoord2f(0.285, 1);	glVertex3f(v3.x, v3.y, v3.z);
			glNormal3fv(VertexNormal(v2, v5, v3)); glTexCoord2f(0.285, 0);	glVertex3f(v2.x, v2.y, v2.z);
			glNormal3fv(VertexNormal(v1, v5, v2)); glTexCoord2f(0, 1);		glVertex3f(v1.x, v1.y, v1.z);
			glNormal3fv(VertexNormal(v4, v5, v1)); glTexCoord2f(1, 0);		glVertex3f(v4.x, v4.y, v4.z);
		}
		glEnd();
		glPopMatrix();
		postRender();

	}
}
