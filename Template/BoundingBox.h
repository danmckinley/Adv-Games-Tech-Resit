#pragma once
#include "Vector3f.h"


class CBoundingBox
{
public:
	CBoundingBox();
	~CBoundingBox();
	void Get(CVector3f &bottom, float &width, float &height, float &depth);
	CVector3f GetBottom();
	CVector3f GetCenter();
	void SetSize(float width, float height, float depth);
	void SetBottom(CVector3f bottom);
	void ScaleAxis(float x, float y, float z);
	void Render(float r, float g, float b);
	bool Collision(CBoundingBox otherBox);
	float GetWidth();
	float GetHeight();
	float GetDepth();
private:
	CVector3f m_bottom;
	float m_width;
	float m_height;
	float m_depth;
	bool scaled;
};
