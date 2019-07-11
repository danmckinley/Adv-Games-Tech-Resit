#pragma once

#include <windows.h>
#include "Vector3f.h"
#include "Camera.h"
#include "MD2Animation.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "include\gl.h"
#define YOHKO_RUN 1
#define YOHKO_ATTACK 2

class CPlayer {
public:
	CPlayer();
	~CPlayer();
	void Update(float dt);
	void Initialise();
	void Render();

	void UpdateCamera(Camera &camera); //TODO
	void Advance(float speed);
	void Strafe(float speed);
	void Turn(float angle);
	void Attack();

	void Movement(double dt);

	void SetModelRotationByMouse();

	void SetRunAnimation();

private:
	CVector3f m_position;
	CVector3f m_direction;
	CVector3f m_strafeVector; //
	float m_currentSpeed;
	float m_defaultSpeed;

	CMD2Model m_mesh;

};