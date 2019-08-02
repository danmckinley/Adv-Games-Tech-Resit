#pragma once
#include "PrimitiveObject.h"

class CGem : public CPrimitiveOctahedron {
public:
	CGem();
	void Initialise() override;

	void Render() override;
	void Rotate();

private:
	GLfloat m_rotationAngle; // variable for controlling rotation of gems
};