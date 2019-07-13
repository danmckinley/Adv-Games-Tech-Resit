#include "BoundingBox.h"
#include <windows.h>									// Header File For The Windows Library
#include ".\include\gl.h"								// Header File For The OpenGL32 Library
#include <math.h>

 
CBoundingBox::CBoundingBox()
{
	m_width = 0;
	m_height = 0;
	m_depth = 0;
	scaled = false;
}

CBoundingBox::~CBoundingBox()
{}

void CBoundingBox::Get(CVector3f &bottom, float &width, float &height, float &depth)
{
	bottom = m_bottom;
	width = m_width;
	height = m_height;
	depth = m_depth;
}

CVector3f CBoundingBox::GetBottom() {
	return m_bottom;
}

CVector3f CBoundingBox::GetCenter() {	//returns the center of the bounding box
	//simply returns the m_bottom vector but with y component offset by the height of the box / 2
	return CVector3f(m_bottom.x, m_bottom.y + m_height/2, m_bottom.z);	
}


void CBoundingBox::SetSize(float width, float height, float depth)
{
	m_width = width;
	m_height = height;
	m_depth = depth;
}

void CBoundingBox::SetBottom(CVector3f bottom)
{
	m_bottom = bottom;
}

void CBoundingBox::ScaleAxis(float x, float y, float z)	// scales width, height and depth appropriately
{
	if (!scaled) {
		m_width = m_width * x;
		m_height = m_height * y;
		m_depth = m_depth * z;
		scaled = true;
	}
}

void CBoundingBox::Render(float r, float g, float b)
{

	float xmin = m_bottom.x - m_width / 2.0f;
	float xmax = m_bottom.x + m_width / 2.0f;
	float ymin = m_bottom.y;
	float ymax = m_bottom.y + m_height;
	float zmin = m_bottom.z - m_depth / 2.0f;
	float zmax = m_bottom.z + m_depth / 2.0f;


	glColor3f(r, g, b);
	glBegin(GL_LINE_LOOP);
	glVertex3f(xmin, ymin, zmin);
	glVertex3f(xmax, ymin, zmin);
	glVertex3f(xmax, ymax, zmin);
	glVertex3f(xmin, ymax, zmin);
	glEnd();
	glBegin(GL_LINE_LOOP);
	glVertex3f(xmin, ymin, zmax);
	glVertex3f(xmax, ymin, zmax);
	glVertex3f(xmax, ymax, zmax);
	glVertex3f(xmin, ymax, zmax);
	glEnd();
	glBegin(GL_LINES);
	glVertex3f(xmin, ymin, zmin);
	glVertex3f(xmin, ymin, zmax);
	glVertex3f(xmax, ymin, zmin);
	glVertex3f(xmax, ymin, zmax);
	glVertex3f(xmax, ymax, zmin);
	glVertex3f(xmax, ymax, zmax);
	glVertex3f(xmin, ymax, zmin);
	glVertex3f(xmin, ymax, zmax);
	glEnd();

}



bool CBoundingBox::Collision(CBoundingBox otherBox)
{

	float width1, height1, depth1, width2, height2, depth2;
	CVector3f bottom1, bottom2, centre1, centre2;

	Get(bottom1, width1, height1, depth1); // this box
	otherBox.Get(bottom2, width2, height2, depth2); // other box
	centre1 = bottom1 + CVector3f(0.0f, height1 / 2.0f, 0.0f);
	centre2 = bottom2 + CVector3f(0.0f, height2 / 2.0f, 0.0f);

	CVector3f v = centre2 - centre1;
	if (fabs(v.x) * 2 <= (width1 + width2) &&
		fabs(v.y) * 2 <= (height1 + height2) &&
		fabs(v.z) * 2 <= (depth1 + depth2))
		return true; // Collision detected
	else
		return false; // No collision detected
}

float CBoundingBox::GetWidth()
{
	return m_width;
}

float CBoundingBox::GetHeight()
{
	return m_height;
}

float CBoundingBox::GetDepth()
{
	return m_depth;
}




