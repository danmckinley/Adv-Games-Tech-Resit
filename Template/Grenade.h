#pragma once
#include <windows.h>
#include "Vector3f.h"
#include "include\gl.h"
#include "./include/glut.h"
#include "ExplosionSprite.h"
#include "Camera.h"

class CGrenade {
public: 
	CGrenade(Camera camera);
	void Initialise();
	void Update(float dt);
	void Shoot(CVector3f pos);
	void Explode();
	void Render();
	CVector3f GetPosition();
	CVector3f GetLastPosition();
public:
	float m_timeAlive = 0;
	bool exploded = false;
	Camera m_camera;
	CExplosionSprite m_explosionSprite;
	// Linear physical quantities
	CVector3f m_position;
	CVector3f m_velocity;
	CVector3f m_acceleration;
	CVector3f m_instantaneousAcceleration;
	CVector3f m_lastPosition;

	// Rotational physical quantities
	CVector3f m_angle;
	CVector3f m_angularVelocity;
	CVector3f m_angularAcceleration;
	CVector3f m_instantaneousAngularAcceleration;


	// Other physical quantities
	float m_mass; // in kg
	float m_rotationalInertia; // in kg m^2
	float m_contactTime; // in seconds
	float m_coefficientOfRestitution; // as a percentage
	float m_radius; // radius of ball in meters

	// Angles used for rendering (see Lab 4)
	float m_theta;
	float m_phi;

	// Methods to handle collisions with the ground
	bool GroundCollisionDetection(float yPlane);
	void GroundCollisionResponse();
};
