#include "Entity.h"

CEntity::CEntity() {
	m_acceleration = CVector3f(0.0f, -9.8f, 0.0f);
	m_coefficientOfRestitution = 0.75f;				// reduced coefficient of restitution so that more velocity is lost per bounce
}

void CEntity::DecreaseHealth(int damage) {
	m_health -= damage;
}

void CEntity::HandlePhysics(float dt){
	m_lastPosition = m_position;
	m_velocity += (m_acceleration + m_instantaneousAcceleration) * dt;
	m_position += m_velocity * dt;

	if (m_instantaneousAcceleration.Length() > 0 && m_contactTime > 0.05) {
		m_instantaneousAcceleration = CVector3f(0, 0, 0);
		m_contactTime = 0;
	}
	m_contactTime += dt;

	float yPlane = 0.0f;
	if (GroundCollisionDetection(yPlane)) {
		GroundCollisionResponse();
		onGround = true;
	}
}

bool CEntity::GroundCollisionDetection(float yPlane) {
	if (m_position.y /*- m_bbox.GetHeight()*/< yPlane && m_velocity.y < 0) {
		return true;
	}
	return false;
}

void CEntity::GroundCollisionResponse() {
	float convergenceThreshold = 12.5f;
	m_velocity = m_velocity * m_coefficientOfRestitution;
	if (m_velocity.Length() > convergenceThreshold) {
		// The ball has bounced!  Implement a bounce by flipping the y velocity.
		m_velocity = CVector3f(m_velocity.x, -m_velocity.y, m_velocity.z);
	}
	else {
		// Velocity of the ball is below a threshold.  Stop the ball. 
		m_velocity = CVector3f(0.0f, 0.0f, 0.0f);
		m_acceleration = CVector3f(0.0f, 0.0f, 0.0f);
		m_position = CVector3f(m_position.x, m_position.y, m_position.z);
	}
}

void CEntity::Shoot(std::vector<std::shared_ptr<CGrenade>> &grenadelist, Camera &camera) {
		std::shared_ptr<CGrenade> grenade = std::make_shared<CGrenade>(camera);
		//grenade->Initialise();
		grenadelist.push_back(grenade);
		grenade->Initialise();
		grenade->Shoot(GetGunPosition());
}

void CEntity::SetPosition(CVector3f position) {
	m_position = position;
}

CVector3f CEntity::GetPosition() {
	return m_position;
}

CVector3f CEntity::GetLastPosition()
{
	return m_lastPosition;
}

CVector3f CEntity::GetGunPosition()
{
	CVector3f gunPos = CVector3f(m_position.x, m_position.y + m_bbox.GetHeight()/2, m_position.z);
	CVector3f horizontalDirection = CVector3f(m_direction.x, 0.0f, m_direction.z);
	gunPos = gunPos + horizontalDirection;
	return gunPos;
}

CBoundingBox CEntity::GetBBox() {
	return m_bbox;
}

int CEntity::GetHealth() {
	return m_health;
}
