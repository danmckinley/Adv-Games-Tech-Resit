#include "Grenade.h"
#include <cmath>

CGrenade::CGrenade(Camera camera)
{
	m_camera = camera;
	// Initialise static physical quantities
	m_radius = 0.1f; // in meters
	m_mass = 0.18f; // in kg
	m_rotationalInertia = (2.0f / 3.0f) * m_mass * m_radius * m_radius; // in kg m^2
	m_coefficientOfRestitution = 0.5f; // percentage
	m_contactTime = 0.05f; // in seconds
}

void CGrenade::Initialise() {
	/*m_explosionSprite.Initialise();*/
}

bool CGrenade::GroundCollisionDetection(float yPlane)
{
	// Check for collision with the ground by looking at the y value of the ball's position
	if (m_position.y - m_radius < yPlane && m_velocity.y < 0) {
		return true;
	}
	return false;
}

void CGrenade::GroundCollisionResponse()
{
	float convergenceThreshold = 0.5f;
	m_velocity = m_velocity * m_coefficientOfRestitution;
	m_angularVelocity = m_angularVelocity * m_coefficientOfRestitution;

	if (m_velocity.Length() > convergenceThreshold) {
		// The ball has bounced!  Implement a bounce by flipping the y velocity.
		m_velocity = CVector3f(m_velocity.x, -m_velocity.y, m_velocity.z);

	}
	else {
		// Velocity of the ball is below a threshold.  Stop the ball. 
		m_velocity = CVector3f(0.0f, 0.0f, 0.0f);
		m_acceleration = CVector3f(0.0f, 0.0f, 0.0f);
		m_position = CVector3f(m_position.x, m_radius, m_position.z);
		m_angularVelocity = CVector3f(0.0f, 0.0f, 0.0f);
	}
}

void CGrenade::Update(float dt)
{
	m_timeAlive += dt;
	if (m_timeAlive > 3) {
		exploded = true;
		Explode();
	}
	if (exploded == false) {
		// Update physical quanitities
		m_lastPosition = m_position;
		m_velocity += (m_acceleration + m_instantaneousAcceleration) * dt;
		m_position += m_velocity * dt;//+ (1/2 * m_acceleration)*(pow(dt,2));
		m_angle += m_angularVelocity * dt;
		m_angularVelocity += (m_angularAcceleration + m_instantaneousAngularAcceleration) * dt;

		// Turn off instantaneous forces if contact time is surpassed
		if (m_instantaneousAcceleration.Length() > 0 && m_contactTime > 0.05) {
			m_instantaneousAcceleration = CVector3f(0, 0, 0);
			m_instantaneousAngularAcceleration = CVector3f(0, 0, 0);
			m_contactTime = 0;
		}
		m_contactTime += dt;

		// Check for collision detection
		float yPlane = 0.0f;
		if (GroundCollisionDetection(yPlane)) {
			GroundCollisionResponse();
		}
	}/*
	else {
		m_explosionSprite.Update(dt);
	}
	*/
}

void CGrenade::Shoot(CVector3f pos){

	CVector3f direction = m_camera.GetViewPoint() - pos;			// Direction camera is facing relative to the player's position
	direction.Normalise();							// Normalised direction camera is facing

	// Initialise all physical variables
	m_position = CVector3f(0.0f, 0.0f, 0.0f);
	m_velocity = CVector3f(0.0f, 0.0f, 0.0f);
	m_acceleration = CVector3f(0.0f, -9.8f, 0.0f);
	m_instantaneousAcceleration = CVector3f(0.0f, 0.0f, 0.0f);
	m_angle = CVector3f(0.0f, 0.0f, 0.0f);
	m_angularVelocity = CVector3f(0.0f, 0.0f, 0.0f);
	m_angularAcceleration = CVector3f(0.0f, 0.0f, 0.0f);
	m_instantaneousAngularAcceleration = CVector3f(0.0f, 0.0f, 0.0f);
	m_contactTime = 0.0f;

	// Set the ball to the current camera position
	m_position = pos;
	//m_velocity = 25.0f * direction;
	CVector3f force = 50.0f * direction;
	CVector3f torque = CVector3f(1, 0, 0);
	torque = 25 * torque;
	m_instantaneousAcceleration = force / m_mass;
	m_instantaneousAngularAcceleration = torque / m_rotationalInertia;



	// Determine rotation angles of camera (from Lab 4)
	m_theta = 90.0f - (180.0f / 3.141529f) * acos(direction.y);
	m_phi = (180.0f / 3.1415290f) * atan2(direction.x, direction.z);
}

void CGrenade::Explode() {
	// Initialise all physical variables
	m_position = CVector3f(0.0f, 0.0f, 0.0f);
	m_velocity = CVector3f(0.0f, 0.0f, 0.0f);
	m_acceleration = CVector3f(0.0f, 0.0f, 0.0f);
	m_instantaneousAcceleration = CVector3f(0.0f, 0.0f, 0.0f);
	m_angle = CVector3f(0.0f, 0.0f, 0.0f);
	m_angularVelocity = CVector3f(0.0f, 0.0f, 0.0f);
	m_angularAcceleration = CVector3f(0.0f, 0.0f, 0.0f);
	m_instantaneousAngularAcceleration = CVector3f(0.0f, 0.0f, 0.0f);
	m_contactTime = 0.0f;
	m_radius = 5.0f;
}


void CGrenade::Render()
{
	if (exploded == false) {
		glPushMatrix();
		glColor3f(1, 0, 0);
		glTranslatef(m_position.x, m_position.y, m_position.z);
		glRotatef(m_phi, 0, 1, 0);
		glRotatef(-m_theta, 1, 0, 0);
		if (m_angle.Length() > 0) {
			glRotatef(m_angle.Length(), m_angle.x, m_angle.y, m_angle.z);	// Rotate the ball resulting from torque
		}
		glutSolidSphere(m_radius, 25, 25);
		glPopMatrix();
	}
	else {
		//m_explosionSprite.Activate();
		//m_explosionSprite.Render(m_position, m_camera.GetPosition(), m_camera.GetUpVector(), 10, 10);
	}
	
}

CVector3f CGrenade::GetPosition()
{
	return m_position;
}

CVector3f CGrenade::GetLastPosition()
{
	return m_lastPosition;
}