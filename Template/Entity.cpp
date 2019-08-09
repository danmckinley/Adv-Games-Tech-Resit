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

	/*
	float yPlane = 0.0f;	// is set to same y value as the ground
	if (GroundCollisionDetection(yPlane)) {
		GroundCollisionResponse();
	}
	*/
}

bool CEntity::GroundCollisionDetection(float yPlane) {
	if (m_position.y /*- m_bbox.GetHeight()*/< yPlane && m_velocity.y < 0) {
		return true;
	}
	return false;
}

void CEntity::GroundCollisionResponse() {
	// float convergenceThreshold = 12.5f; // value to determine how hard must be falling to bounce
	onGround = true;
	m_velocity = m_velocity * m_coefficientOfRestitution;
	m_velocity = CVector3f(0.0f, 0.0f, 0.0f);
	m_acceleration = CVector3f(0.0f, -9.8f, 0.0f);
	m_position = CVector3f(m_position.x, m_position.y, m_position.z);
	/*	// turnt off bouncing 
	if (m_velocity.Length() > convergenceThreshold) {
		// The entity has bounced!  Implement a bounce by flipping the y velocity.
		m_velocity = CVector3f(m_velocity.x, -m_velocity.y, m_velocity.z);
		onGround = false; // if the player bounces, set onGround to false
	}
	else {
		// Velocity of the ball is below a threshold.  Stop the ball. 
		m_velocity = CVector3f(0.0f, 0.0f, 0.0f);
		m_acceleration = CVector3f(0.0f, 0.0f, 0.0f);
		m_position = CVector3f(m_position.x, m_position.y, m_position.z);
	}
	*/
}

void CEntity::CheckWorldCollision(CVector3f *pVertices, int numOfVerts)
{
	for (int i = 0; i < numOfVerts; i += 3) {
		// Store the current triangle we're testing
		CVector3f vTriangle[3] = { pVertices[i], pVertices[i + 1], pVertices[i + 2] };
		// ++ Finding the bbox's classification
		CVector3f vNormal = Normal(vTriangle);
		float distance = 0.0f;
		float boxWidth = m_bbox.GetWidth();
		float boxHeight = m_bbox.GetHeight();

		int classification = ClassifyBox(m_bbox.GetCenter(), vNormal, vTriangle[0],
			boxWidth, boxHeight, distance);
		if (classification == INTERSECTS) {
			CVector3f vOffset = vNormal * distance;
			CVector3f vIntersection = m_bbox.GetCenter() - vOffset;
			// this is what actually determines whether or not there is a collision
			if (InsidePolygon(vIntersection, vTriangle, 3) || EdgeBoxCollision(m_bbox.GetCenter(), vTriangle, 3, boxWidth/4, boxHeight/4)) {
				if (vNormal.y >= 0.75) {
					GroundCollisionResponse();
				}
				vOffset = GetCollisionOffset(vNormal, boxWidth, boxHeight, distance);
				m_position = m_position + vOffset;
			}
		}
		
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
