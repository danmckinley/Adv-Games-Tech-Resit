#pragma once
#include "PrimitiveObject.h"
class CMetalFloor: public CPrimitiveCuboid {
public:
	CMetalFloor();
	void Initialise() override;

	void Render() override;
}; 