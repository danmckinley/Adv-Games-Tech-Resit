#include "Lighting.h"	



void CLighting::SetDefaultLighting()
{
	glEnable(GL_LIGHTING);

	GLfloat ambientLight0[] = {0.2f, 0.2f, 0.2f, 1.0f};
	GLfloat diffuseLight0[] = {1.0f, 1.0f, 1.0f, 1.0f};
	GLfloat specularLight0[] = {1.0f, 1.0f, 1.0f, 1.0f};
	GLfloat positionLight0[] = {0.0f, 1.0f, 1.0f, 0.0f};
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight0);
	glLightfv(GL_LIGHT0, GL_POSITION, positionLight0);

	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);

}

void CLighting::SetLight(CVector3f p0) {	//method for rendering a point light
	glEnable(GL_LIGHTING);
	//first light
	GLfloat ambientLight0[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	GLfloat diffuseLight0[] = { 1.0f, 1.0f, 0.0f, 1.0f };
	GLfloat specularLight0[] = { 1.0f, 1.0f, 0.0f, 1.0f };
	GLfloat positionLight0[] = { p0.x, p0.y, p0.z, 1.0f };
	glLightfv(GL_LIGHT1, GL_AMBIENT, ambientLight0);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuseLight0);
	glLightfv(GL_LIGHT1, GL_SPECULAR, specularLight0);
	glLightfv(GL_LIGHT1, GL_POSITION, positionLight0);
	glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 1.0);
	glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.1);
	glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.01);
	glEnable(GL_LIGHT1);	// enables corresponding light
	glEnable(GL_NORMALIZE);
}

void CLighting::SetTestLight(CVector3f p0) {	//method for rendering a point light
	glEnable(GL_LIGHTING);
	//first light
	GLfloat ambientLight0[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	GLfloat diffuseLight0[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat specularLight0[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat positionLight0[] = { p0.x, p0.y, p0.z, 1.0f };
	glLightfv(GL_LIGHT2, GL_AMBIENT, ambientLight0);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuseLight0);
	glLightfv(GL_LIGHT2, GL_SPECULAR, specularLight0);
	glLightfv(GL_LIGHT2, GL_POSITION, positionLight0);
	glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, 1.0);
	glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, 0.1);
	glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, 0.01);
	glEnable(GL_LIGHT2);	// enables corresponding light
	glEnable(GL_NORMALIZE);
}