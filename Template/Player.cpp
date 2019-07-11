#include "Player.h"
#include <math.h>
#include "gamewindow.h"

#include <string>
#include <iostream>

CPlayer::CPlayer() {
	m_position = CVector3f(20, 0, 0);
	m_direction = CVector3f(0,0,1);
	m_currentSpeed = 0.0f;
	m_defaultSpeed = 4.0f;
}

CPlayer::~CPlayer() {

}

void CPlayer::Initialise() {
	m_mesh.Load("Resources\\Meshes\\Yohko.md2", "Resources\\Meshes\\Yohko.bmp", 
		"Resources\\Meshes\\YohkoWeapon.md2", "Resources\\Meshes\\YohkoWeapon.bmp");
}

void CPlayer::Update(float dt) {
	Movement(dt);

	/* TEMPLATE VERSION
	m_position += m_direction * m_speed * dt;
	if (m_mesh.GetAnimation() == YOHKO_ATTACK && m_mesh.IsLastFrameRendered()) {
		m_mesh.SetAnimation(YOHKO_RUN);
		m_speed = 5.0f;
	}
	*/
}

void CPlayer::Render() {
	float thetaRadians = -atan2(m_direction.z, m_direction.x);
	float thetaDegrees = thetaRadians * (180.0f / M_PI);

	glPushMatrix(); {
		glTranslatef(m_position.x, 1.2f, m_position.z);
		glRotatef(thetaDegrees, 0, 1, 0);
		glScalef(0.05f, 0.05f, 0.05f);
		m_mesh.Render(true);
	}
	glPopMatrix();
}

void CPlayer::UpdateCamera(Camera &camera) {
	CVector3f camPos = CVector3f(m_position.x - (m_direction.x * 5), 3.0f, m_position.z - (m_direction.z * 5));
	CVector3f camFacing = CVector3f(m_position.x + (m_direction.x * 15), /*m_position.y + m_direction.y*/ camera.GetViewPoint().y, m_position.z + (m_direction.z * 15));
	m_strafeVector = (camFacing - camPos) % CVector3f(0, 1, 0);
	m_strafeVector.Normalise();
	camPos += m_strafeVector;
	camera.Set(camPos, camFacing, CVector3f(0, 1, 0), m_currentSpeed);
	Turn(camera.SetCameraViewByPlayer());
	
}

void CPlayer::Advance(float speed){
	m_position += m_direction * speed;
	m_currentSpeed = speed;
	SetRunAnimation();
}

void CPlayer::Strafe(float speed){
	m_position.x += m_strafeVector.x * speed;
	m_position.z += m_strafeVector.z * speed;
	m_currentSpeed = speed;
	SetRunAnimation();
}

void CPlayer::Turn(float angle) {
	m_direction = m_direction.RotateAboutAxis(angle, CVector3f(0, 1, 0));
}

void CPlayer::Attack() {
	m_mesh.SetAnimation(YOHKO_ATTACK);
	m_currentSpeed = 0.0f;
}

void CPlayer::Movement(double dt)
{
	float speed = (float)dt * m_defaultSpeed;
	
	if ((GetKeyState(VK_UP) & 0x80 || GetKeyState('W') & 0x80)) {
		Advance(speed);		// Forward
	}

	if ((GetKeyState(VK_DOWN) & 0x80 || GetKeyState('S') & 0x80)) {
		Advance(-speed);	// Backward
	}

	if ((GetKeyState(VK_LEFT) & 0x80 || GetKeyState('A') & 0x80)) {
		Strafe(-speed);		// Left
	}

	if ((GetKeyState(VK_RIGHT) & 0x80 || GetKeyState('D') & 0x80)) {
		Strafe(speed);		// Right
	}
}

void CPlayer::SetRunAnimation() {
		m_mesh.SetAnimation(YOHKO_RUN);
}

