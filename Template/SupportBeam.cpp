#include "SupportBeam.h"

CSupportBeam :: CSupportBeam(){
}
CSupportBeam :: ~CSupportBeam() {

}

void CSupportBeam::Initialise() {}

void CSupportBeam::preRender() {
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
	glEnable(GL_BLEND);
	//glEnable(GL_LINE_SMOOTH);		// Anti-Aliasing would be enabled, but it makes it so the lines don't connect cleanly (you can see through them where they join)
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void CSupportBeam::postRender() {
	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
}

void CSupportBeam::Render(float r, float g, float b, float a) {
	preRender();
	glPushMatrix(); {
		glLineWidth(3);
		glColor4f(0.75, 0.75, 0.75, a);
		glBegin(GL_LINE_STRIP);
		glVertex3fv(v0);
		glVertex3fv(v1);
		glVertex3fv(v2);
		glVertex3fv(v0);
		glEnd();
		glBegin(GL_LINE_STRIP);
		glVertex3fv(v3);
		glVertex3fv(v4);
		glVertex3fv(v5);
		glVertex3fv(v3);
		glEnd();
	}
	glPopMatrix();
	postRender();
}