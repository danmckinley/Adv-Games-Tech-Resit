#pragma once
#include "PrimitiveObject.h"

class CGem : public CPrimitiveOctahedron {
public:
	CGem();
	void Initialise() override;

	void Render() override;
};