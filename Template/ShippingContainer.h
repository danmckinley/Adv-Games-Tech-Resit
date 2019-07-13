#pragma once
#include "PrimitiveObject.h"
class CShippingContainer : public CPrimitiveCuboid {
public:
	CShippingContainer();
	void Initialise() override;
	
	void Render() override;
};