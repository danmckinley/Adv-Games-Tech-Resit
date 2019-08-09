#include "Terrain.h"
#include "Texture.h"
#include <vector>

//ground texture from "https://jooinn.com/muddy-soil-texture.html"

CTerrain::CTerrain()
{
	float m_numOfVerts = 2 * 3; // number of vertices for each triangle (3) multiplied by the number of triangles (6 QUADS therefore 12 TRIS)
	m_polygons = new CVector3f[m_numOfVerts];
	float TERRAIN_SIZE = 500;

	length = TERRAIN_SIZE / 2.0f;
	width = TERRAIN_SIZE / 2.0f;

	// Centre terrain vertices around 0, 0, 0;
	float x = -width / 2.0f;
	float y = 0.0;
	float z = -length / 2.0f;
	v0 = CVector3f(x, y, z);
	v1 = CVector3f(x, y, z + length);
	v2 = CVector3f(x + width, y, z + length);
	v3 = CVector3f(x + width, y, z);
}

CTerrain::~CTerrain()
{}

bool CTerrain::Initialise()
{
	// Load the texture
	CTexture texture;
	texture.Load("Resources\\Textures\\MudTerrain.jpg", false); 
	m_textureID = texture.m_textureID;
	
	m_polygons[0] = v0;//first triangle
	m_polygons[1] = v2;
	m_polygons[2] = v1;
	m_polygons[3] = v0;//next triangle
	m_polygons[4] = v3;
	m_polygons[5] = v2;
	return true;
}

CVector3f CTerrain::GetVertexAtIndex(int index) {
	CVector3f vertex = m_polygons[index];
	return vertex;
}

void CTerrain::Render()
{

	// Bind the texture	
	glBindTexture(GL_TEXTURE_2D, m_textureID);

	glNormal3f(0.0f, 1.0f, 0.0f);

	// Draw a quad
	// I set the texture scaling to 30 instead of 1 to ensure the texture didn't look blurry and that the dirt in the image wasn't huge.
	glBegin(GL_QUADS);		
		glTexCoord2f(30.0f, 0.0f); glVertex3f(v0.x, v0.y, v0.z);
		glTexCoord2f(30.0f, 30.0f); glVertex3f(v1.x, v1.y, v1.z);
		glTexCoord2f(0.0f, 30.0f); glVertex3f(v2.x, v2.y, v2.z); 
		glTexCoord2f(0.0f, 0.0f); glVertex3f(v3.x, v3.y, v3.z);
	glEnd();
}
