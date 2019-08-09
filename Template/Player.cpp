#include "Player.h"
#include <math.h>
#include "gamewindow.h"
#include <string>
#include <iostream>

CPlayer::CPlayer() {
	m_position = CVector3f(27, 0, 20);
	m_direction = CVector3f(0,0,1);
	m_currentSpeed = 0.0f;
	m_defaultSpeed = 5.0f;
	m_rightHandedCamera = false;
	m_maxHealth = 100;
	m_health = m_maxHealth;
}

void CPlayer::Initialise() {
	m_mesh.Load("Resources\\Meshes\\Doom\\tris.md2", "Resources\\Meshes\\Doom\\doom.jpg", 
		"Resources\\Meshes\\Doom\\weapon.md2", "Resources\\Meshes\\Doom\\weapon.jpg");
	m_bbox.SetBottom(m_position);
	m_bbox.SetSize(1.0f, 2.4f, 1.0f);
}

void CPlayer::Update(float dt) {
	Movement(dt);
	HandlePhysics(dt);
	m_bbox.SetBottom(m_position);
}

void CPlayer::Render() {
	float thetaRadians = -atan2(m_direction.z, m_direction.x);		// gets the direction the player is moving as an angle in radians
	float thetaDegrees = thetaRadians * (180.0f / M_PI);			// converts it to degrees

	glPushMatrix(); {
		glTranslatef(m_position.x, m_position.y + m_bbox.GetHeight()/2, m_position.z);
		glRotatef(thetaDegrees, 0, 1, 0);							// rotate the player model to face the direction of the camera
		glScalef(0.05f, 0.05f, 0.05f);
		m_mesh.Render(true);
	}
	glPopMatrix();
	/*
	#if (_DEBUG)					// rendering the bounding box
		glDisable(GL_LIGHTING);
		glDisable(GL_TEXTURE_2D);
		m_bBox.Render(1, 0, 0);
		glEnable(GL_LIGHTING);
		glEnable(GL_TEXTURE_2D);
	#endif
	*/
}

void CPlayer::UpdateCamera(Camera &camera) {
	CVector3f camPos = CVector3f(m_position.x - (m_direction.x * 5), m_position.y + 3.0f, m_position.z - (m_direction.z * 5));
	CVector3f camFacing = CVector3f(m_position.x + (m_direction.x * 15), camera.GetViewPoint().y, m_position.z + (m_direction.z * 15));
	strafeVector = (camFacing - camPos) % CVector3f(0, 1, 0);		// sets the strafe vector in the same way as in Camera.cpp
	strafeVector.Normalise();
	if (m_rightHandedCamera == true) {								// based on the handedness of the camera, offset it either to the left or the right of the player
   		camPos += strafeVector*1.2;
	}
	else {
		camPos -= strafeVector * 1.2;
	}
	
	camera.Set(camPos, camFacing, CVector3f(0, 1, 0), m_currentSpeed);	// update the camera
	Turn(camera.SetCameraViewByPlayer());							// updates the rotation of the player model based on the x rotation component of the camera
	
}

void CPlayer::Advance(float speed){
	m_position += m_direction * speed;
	m_currentSpeed = speed;
}

void CPlayer::Strafe(float speed){
	m_position.x += strafeVector.x * speed;
	m_position.z += strafeVector.z * speed;
	m_currentSpeed = speed;
}

void CPlayer::Turn(float angle) {	// updates the direction vector of the player using the x component of the camera's rotation
	m_direction = m_direction.RotateAboutAxis(angle, CVector3f(0, 1, 0));
}

void CPlayer::Jump() {
	if (onGround) {
		onGround = false;
		m_acceleration = CVector3f(0.0f, -9.8f, 0.0f);
		CVector3f direction = CVector3f(0, 1, 0);
		direction.Normalise();
		CVector3f force = 27500.0f * direction;
		m_instantaneousAcceleration = force / 60;	// 60; for desktop // 5; for laptop
	}
}

void CPlayer::Attack() {
	//m_mesh.SetAnimation(YOHKO_ATTACK);
	m_currentSpeed = 0.0f;
}

void CPlayer::Movement(double dt)
{
	float speed = (float)dt * m_defaultSpeed;
	
	if (moveForward) {
		Advance(speed);		// Forward
		SetRunAnimation();
	}

	if (moveBackwards) {
		speed = speed / 1.5;
		Advance(-speed);	// Backward
	}

	if (strafeLeft) {
		Strafe(-speed);		// Left
		SetRunAnimation();
	}

	if (strafeRight) {
		Strafe(speed);		// Right
		SetRunAnimation();
	}

	if (!moveForward && !moveBackwards && !strafeLeft && !strafeRight) {
		SetStandAnimation();
	}
}

void CPlayer::FlipCamera() {
	//anim++;
	if (m_rightHandedCamera == true) {
		m_rightHandedCamera = false;
	}
	else {
		m_rightHandedCamera = true;
	}
}

void CPlayer::DecreaseShields(int damage) {
	m_shieldHealth -= damage;
}

int CPlayer::GetShields() {
	return m_shieldHealth;
}

void CPlayer::SetMoveForward(bool b) {
	moveForward = b;
}
void CPlayer::SetMoveBackwards(bool b) {
	moveBackwards = b;
}
void CPlayer::SetStrafeLeft(bool b) {
	strafeLeft = b;
}
void CPlayer::SetStrafeRight(bool b) {
	strafeRight = b;
}

void CPlayer::SetStandAnimation() {
	m_mesh.SetAnimation(0);
}

void CPlayer::SetRunAnimation() {
	m_mesh.SetAnimation(1);
}


