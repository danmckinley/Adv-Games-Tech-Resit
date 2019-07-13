#pragma once
#include "Entity.h"
#define DROID_RUN 1
#define DROID_ATTACK 2



class CEnemy: public CEntity
{
public:
	CEnemy();
	~CEnemy();
	void Initialise() override;
	void Update(float dt) override;
	void Render() override;
	void Face(CVector3f player);
	void Move(float dt);
	void Flee(float dt);
	enum states {
		TOOFAR,
		FIGHT,
		FLEE,
		INDIFFERENT
	};
	int m_state;
	
};