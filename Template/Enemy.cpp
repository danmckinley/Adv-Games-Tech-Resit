#include "Enemy.h"



CEnemy::CEnemy()
{
	//m_position = CVector3f(10, 0, 10);
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
	case TOOFAR:
		Move(dt);
		break;
	case FLEE:
		Flee(dt);
		break;
	case INDIFFERENT:
		break;
	case FIGHT:
		break;
	}
	m_bbox.SetBottom(m_position);
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
	#if(_DEBUG)
		glDisable(GL_LIGHTING);
		glDisable(GL_TEXTURE_2D);
		m_bbox.Render(1, 0, 0);
		glEnable(GL_LIGHTING);
		glEnable(GL_TEXTURE_2D);
	#endif
}

void CEnemy::Face(CVector3f player) {		//sets the m_direction variable towards the vector (which will be the player)
	CVector3f facing = player - m_position;
	facing.Normalise();
	facing.y = 0;
	if (facing.Length() < 5) {
		m_state = FLEE;
	}
	else if (facing.Length() > 25) {
		m_state = TOOFAR;
	}
	facing.Normalise();
	m_direction = facing;

}

void CEnemy::Move(float dt) {				// moves the enemy in the direction of m_direction (to pursue the player)
	float speed = dt * 2;
	m_position += m_direction * speed;
}

void CEnemy::Flee(float dt) {				// moves the enemy in the opposite direction of m_direction
	float speed = dt * 2;
	m_position -= m_direction * speed;
}