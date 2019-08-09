#pragma once
#include "PrimitiveObject.h"

class CGem : public CPrimitiveOctahedron {
public:
	CGem();
	void Initialise() override;

	void Render() override;
	bool CheckPlayerCollision(CBoundingBox otherBox);
	void SetCollected();
	bool GetCollected();
	void Rotate();
	CBoundingBox GetBBox();
	CVector3f GetPosition();

private:
	bool collected = false;
	CBoundingBox m_bbox;
	GLfloat m_rotationAngle; // variable for controlling rotation of gems
};