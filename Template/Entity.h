#pragma once

#include <windows.h>
#include "3DMaths.h"
#include "Vector3f.h"
#include "Camera.h"
#include "MD2Animation.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "include\gl.h"
#include "BoundingBox.h"
#include "Grenade.h"
#include <memory>

class CEntity {
public:
	CEntity();
	void DecreaseHealth(int damage);
	virtual void Update(float dt) = 0;
	virtual void Initialise() = 0;
	virtual void Render() = 0;
	void HandlePhysics(float dt);
	bool onGround = true;
	bool GroundCollisionDetection(float yPlane);
	void GroundCollisionResponse();
	void CheckWorldCollision(CVector3f *pVertices, int numOfVerts);
	void Shoot(std::vector<std::shared_ptr<CGrenade>>& grenadelist, Camera & camera);
	//void Shoot(std::vector<std::shared_ptr<CGrenade>>& grenadelist);
	void SetPosition(CVector3f position);
	CVector3f GetPosition();
	CVector3f GetLastPosition();
	CVector3f GetGunPosition();
	CBoundingBox GetBBox();
	int GetHealth();
protected:
	int m_maxHealth;
	int m_health;

	CVector3f m_direction;
	CVector3f m_position;
	CVector3f m_velocity;
	CVector3f m_acceleration;
	CVector3f m_instantaneousAcceleration;
	CVector3f m_lastPosition;
	float m_coefficientOfRestitution;
	float m_contactTime;

	CMD2Model m_mesh;
	CBoundingBox m_bbox;
};