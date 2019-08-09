#pragma once
#include "Entity.h"



class CEnemy: public CEntity
{
public:
	CEnemy();
	~CEnemy();
	void Initialise() override;
	void Update(float dt) override;
	void Kill() override;
	void UpdatePlayerReference(CVector3f playerPosition);
	void Render() override;
	void Face();
	void Move(float dt);
	void TooFar();
	void Flee();
	void Indifferent();
	void Fight();
	void Dead();
	enum states {
		TOOFAR,
		FIGHT,
		FLEE,
		INDIFFERENT,
		DEAD
	};
	int m_state = INDIFFERENT;
	CVector3f playerReference;
	CVector3f playerDirection;
	bool moving = false;
};