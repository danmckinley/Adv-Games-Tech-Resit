#include "ExplosionSprite.h"

CExplosionSprite::CExplosionSprite()
{

	m_active = false;
}

CExplosionSprite::~CExplosionSprite()
{}


void CExplosionSprite::Activate()
{
	m_active = true;
	m_frame = 0;
	m_elapsedTime = 0;
}


void CExplosionSprite::Update(float dt)
{

	//if (m_active == false)
		//return;

	// Update the frame based on dt
	float frameTime = 1.0f / 30.0f;  // Sprite running at 30 frames per second

	m_elapsedTime += dt;

	if (m_elapsedTime > frameTime) {
		m_frame++;
		if (m_frame >= m_totalFrames) {
			m_frame = 0;
			m_active = false;
		}
		m_elapsedTime -= frameTime;
	}
}

// This assumes the images in the sprite are laid out in a 2D fashion in the sprite image
bool CExplosionSprite::Initialise()
{
	int numFramesX = 4;
	int numFramesY = 5;
	int totalFrames = 16;
	// Load the texture
	m_texture.Load("Resources\\Textures\\explosion.tga", true); // Loads an image.  Make sure the image has transparency

	m_framesX = numFramesX;
	m_framesY = numFramesY;

	m_frameWidth = m_texture.m_width / m_framesX;
	m_frameHeight = m_texture.m_height / m_framesY;

	m_frame = 0;
	m_totalFrames = totalFrames;

	m_active = false;


	return true;
}



void CExplosionSprite::Render(CVector3f p, CVector3f lookAt, CVector3f upVector, float width, float height)
{

	//if (m_active == false)
		//return;

	float fImageWidth = (float)m_texture.m_width;
	float fImageHeight = (float)m_texture.m_height;

	int xIndex = m_frame % m_framesX;
	int yIndex = (m_framesY - 1) - m_frame / m_framesX;


	// Form a quad at p in the plane orthogonal to the lookAt vector
	CVector3f xAxis = lookAt % upVector;
	xAxis.Normalise();
	CVector3f yAxis = upVector;
	yAxis.Normalise();

	// Determine the coordinates of the billboarded quad
	CVector3f p1 = p - width * xAxis - height * yAxis;
	CVector3f p2 = p + width * xAxis - height * yAxis;
	CVector3f p3 = p + width * xAxis + height * yAxis;
	CVector3f p4 = p - width * xAxis + height * yAxis;

	// Bind the texture	
	m_texture.Bind();				// Binds the bitmap for use

	glColor3f(1, 1, 1);

	glEnable(GL_BLEND);									// Enable Blending
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);					// Type Of Blending To Perform
	glEnable(GL_TEXTURE_2D);


	// Draw a textured quad with the current frame
	// Be sure to get the texture coordinates that match the current frame
	glBegin(GL_QUADS);
	glTexCoord2f(xIndex*(m_frameWidth / fImageWidth), yIndex*(m_frameHeight / fImageHeight));
	glVertex3f(p1.x, p1.y, p1.z);
	glTexCoord2f((xIndex + 1)*(m_frameWidth / fImageWidth), yIndex*(m_frameHeight / fImageHeight));
	glVertex3f(p2.x, p2.y, p2.z);
	glTexCoord2f((xIndex + 1)*(m_frameWidth / fImageWidth), (yIndex + 1)*(m_frameHeight / fImageHeight));
	glVertex3f(p3.x, p3.y, p3.z);
	glTexCoord2f(xIndex*(m_frameWidth / fImageWidth), (yIndex + 1)*(m_frameHeight / fImageHeight));
	glVertex3f(p4.x, p4.y, p4.z);
	glEnd();

	glDisable(GL_BLEND);
}