#pragma once
#include "PrimitiveObject.h"

class CLampPost : public CPrimitiveCuboid {
public:
	CLampPost();
	void Initialise() override;
	void Render() override;
	CVector3f GetLightPosition();
};