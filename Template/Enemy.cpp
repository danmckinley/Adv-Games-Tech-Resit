#include "Enemy.h"



CEnemy::CEnemy()
{
	//m_position = CVector3f(10, 0, 10);
	m_health = 100;
	m_position = CVector3f((rand() % 50) - 25, 0, (rand() % 50)); // random spawn locations for enemies
}
CEnemy::~CEnemy()
{}
void CEnemy::Initialise()
{
	m_mesh.Load("Resources\\Meshes\\battroid\\tris.MD2", "Resources\\Meshes\\battroid\\VT_102.jpg",		// texture file formats were changed to JPEGs since .pcx, .bmp and .png weren't working
		"Resources\\Meshes\\battroid\\weapon.MD2", "Resources\\Meshes\\battroid\\myweapon.jpg");			// this method didn't work for the weapon texture
	m_bbox.SetSize(1.4f, 4.0f, 1.4f);
	m_bbox.SetBottom(m_position);
}

//TOOFAR,
//FIGHT,
//FLEE,
//INDIFFERENT

void CEnemy::Update(float dt) {
	switch (m_state) {
	case TOOFAR:	// aware of player
		TooFar();
		break;
	case FLEE:		// injured
		Flee();
		break;
	case INDIFFERENT:	// not aware of player
		Indifferent();
		break;
	case FIGHT:		// aware of player & in range
		Fight();
		break;
	case DEAD:		// dead
		Dead();
		break;
	}
	if (moving) {
		Move(dt);
	}
	m_bbox.SetBottom(m_position);
}

void CEnemy::Kill()
{
	m_state = DEAD;
}

void CEnemy::UpdatePlayerReference(CVector3f playerPosition) {
	playerReference = playerPosition;
	playerDirection = playerReference - m_position;
	playerDirection.y = 0;
	/*
	if (playerDirection.Length() < 5) {
		m_state = FLEE;
	}
	else if (playerDirection.Length() > 25) {
		m_state = TOOFAR;
	}
	*/
}

void CEnemy::Render()
{
	float thetaRadians = -atan2(m_direction.z, m_direction.x);		// gets the direction the enemy is moving as an angle in radians
	float thetaDegrees = thetaRadians * (180.0f / M_PI);			// converts it to degrees

	glPushMatrix(); {
		glTranslatef(m_position.x - 0.1, m_position.y + 2.3, m_position.z - 0.2);		// I offset the model to fit better inside of it's bounding box
		glRotatef(thetaDegrees+20, 0, 1, 0);
		glScalef(0.09, 0.09, 0.09);
		m_mesh.Render(true);
	}
	glPopMatrix();
	/*
	#if(_DEBUG)
		glDisable(GL_LIGHTING);
		glDisable(GL_TEXTURE_2D);
		m_bbox.Render(1, 0, 0);
		glEnable(GL_LIGHTING);
		glEnable(GL_TEXTURE_2D);
	#endif
	*/
}

void CEnemy::Face() {		//sets the m_direction variable towards the player reference
	CVector3f facing = playerDirection;
	facing.Normalise();
	m_direction = facing;

}

void CEnemy::Move(float dt) {				// moves the enemy in the direction of m_direction (to pursue the player)
	Face();
	float speed = dt * 2;
	if (m_state == FLEE) {
		m_position -= m_direction * speed;
	}
	else {
		m_position += m_direction * speed;
	}
}

void CEnemy::Indifferent()
{
	if (playerDirection.Length() <= 15) {
		m_state = TOOFAR;
	}
	moving = false;
}

void CEnemy::TooFar() {
	moving = true;
	if (playerDirection.Length() <= 10) {
		m_state = FIGHT;
	}
}

void CEnemy::Flee() {				// moves the enemy in the opposite direction of m_direction
	moving = true;
	if ((playerDirection.Length() >= 30)) {
		m_state = INDIFFERENT;
	}
}

void CEnemy::Fight()
{
	// implement enemy shooting code
	moving = false;
	if ((playerDirection.Length() >= 10)) {
		m_state = INDIFFERENT;
	}
}

void CEnemy::Dead() {
	moving = false;
	m_position = CVector3f(0, -10, 0);
}
