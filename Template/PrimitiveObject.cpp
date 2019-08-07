#include "PrimitiveObject.h"
#include ".\include\gl.h"
#include <iostream>

// ONLY FOR CUBOIDS

CPrimitiveObject::CPrimitiveObject()
{
	rotateBy[0] = 0.0; rotateBy[1] = 0.0; rotateBy[2] = 0.0; rotateBy[3] = 0.0;
	scaleBy[0] = 1.0; scaleBy[1] = 1.0; scaleBy[2] = 1.0;
}

CVector3f CPrimitiveObject::ToWorldCoordinates(CVector3f vec1) {	
	// method that applies scaling, rotation, and transformations
	// to the local coordinate vectors of the primitive objects
	CVector3f vec2 = vec1;
	vec2.x = vec2.x * scaleBy[0];
	vec2.y = vec2.y * scaleBy[1];
	vec2.z = vec2.z * scaleBy[2];
	vec2 = vec2.RotateAboutAxis(rotateBy[0], CVector3f(rotateBy[1], rotateBy[2], rotateBy[3]));
	return CVector3f(vec2.x + m_position.x, vec2.y + m_position.y, vec2.z + m_position.z);
}

void CPrimitiveObject::SetPosition(CVector3f newPos)
{
	m_position = newPos;
}

void CPrimitiveObject::ApplyTranslation() {
	glTranslatef(m_position.x, m_position.y, m_position.z);
}

void CPrimitiveObject::SetScaling(GLfloat x, GLfloat y, GLfloat z) {
	scaleBy[0] = x;
	scaleBy[1] = y;
	scaleBy[2] = z;
}

void CPrimitiveObject::ApplyScaling() {
	glScalef(scaleBy[0], scaleBy[1], scaleBy[2]);
}

void CPrimitiveObject::SetRotation(GLfloat angle, GLfloat x, GLfloat y, GLfloat z) {
	rotateBy[0] = angle;
	rotateBy[1] = x;
	rotateBy[2] = y;
	rotateBy[3] = z;
}

void CPrimitiveObject::ApplyRotation() {
	glRotatef(rotateBy[0], rotateBy[1], rotateBy[2], rotateBy[3]);
}

void CPrimitiveObject::ApplySort() {
	ApplyTranslation();
	ApplyRotation();
	ApplyScaling();
}

void CPrimitiveObject::SetTexture(std::string path) {
	texture.Load(path, false);
	m_textureID = texture.m_textureID;
	//texture.Bind();
}

void CPrimitiveObject::preRender() {
	//glDisable(GL_TEXTURE_2D);					
	glEnable(GL_TEXTURE_2D);
	//texture.Bind();
	glBindTexture(GL_TEXTURE_2D, m_textureID);
	glEnable(GL_LIGHTING);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void CPrimitiveObject::postRender() {
	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
}

bool CPrimitiveObject::CheckCollision(CBoundingBox bbox) {
	for (int i = 0; i < m_numOfVerts; i += 3) {
		// Store the current triangle we're testing
		CVector3f vTriangle[3] = { m_polygons[i], m_polygons[i + 1], m_polygons[i + 2] };
		// ++ Finding the bbox's classification
		CVector3f vNormal = Normal(vTriangle);
		float distance = 0.0f;
		float largerAxis = bbox.GetWidth();
		if (vNormal.y > vNormal.x && vNormal.y > vNormal.z) {
			largerAxis = bbox.GetHeight();
		} else if (vNormal.x > vNormal.z) {
			largerAxis = bbox.GetWidth();
		} else if (vNormal.z > vNormal.x) {
			largerAxis = bbox.GetDepth();
		}
		
		int classification = ClassifyBox(bbox.GetCenter(), vNormal, vTriangle[0],
			largerAxis, distance);
		if (classification == INTERSECTS) {
			vOffset = vNormal * distance;
			CVector3f vIntersection = bbox.GetCenter() - vOffset;
			if (InsidePolygon(vIntersection, vTriangle, 3) || EdgeBoxCollision(bbox.GetCenter(), vTriangle, 3, bbox.GetWidth()/2)) {
				vOffset = GetCollisionOffset(vNormal, largerAxis, distance);
				return true;
			}
			return false;
		}
	}
	return false;
}

CVector3f CPrimitiveObject::GetOffset() {
	return vOffset;
}

CVector3f* CPrimitiveObject::GetPolygonData()
{
	return m_polygons;
}

int CPrimitiveObject::GetNumberOfVerts()
{
	return m_numOfVerts;
}

////////////////////////////// PRIMITIVE CUBOID METHODS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\

CPrimitiveCuboid::CPrimitiveCuboid() 
{
	m_numOfVerts = 12 * 3; // number of vertices for each triangle (3) multiplied by the number of triangles (6 QUADS so 12 TRIS)
	m_polygons = new CVector3f[m_numOfVerts];
}

void CPrimitiveCuboid::SetPolygonsToWorldCoords() {
	if (!polygonsSetToWorldCoords) {
		m_polygons[0] = ToWorldCoordinates(v0);//first triangle
		m_polygons[1] = ToWorldCoordinates(v1);
		m_polygons[2] = ToWorldCoordinates(v5);
		m_polygons[3] = ToWorldCoordinates(v0);//next triangle
		m_polygons[4] = ToWorldCoordinates(v5);
		m_polygons[5] = ToWorldCoordinates(v4);
		m_polygons[6] = ToWorldCoordinates(v2);//next triangle
		m_polygons[7] = ToWorldCoordinates(v3);
		m_polygons[8] = ToWorldCoordinates(v7);
		m_polygons[9] = ToWorldCoordinates(v2);//next triangle
		m_polygons[10] = ToWorldCoordinates(v7);
		m_polygons[11] = ToWorldCoordinates(v6);
		m_polygons[12] = ToWorldCoordinates(v3);//next triangle
		m_polygons[13] = ToWorldCoordinates(v0);
		m_polygons[14] = ToWorldCoordinates(v4);
		m_polygons[15] = ToWorldCoordinates(v3);//next triangle
		m_polygons[16] = ToWorldCoordinates(v4);
		m_polygons[17] = ToWorldCoordinates(v7);
		m_polygons[18] = ToWorldCoordinates(v1);//next triangle
		m_polygons[19] = ToWorldCoordinates(v2);
		m_polygons[20] = ToWorldCoordinates(v6);
		m_polygons[21] = ToWorldCoordinates(v1);//next triangle
		m_polygons[22] = ToWorldCoordinates(v6);
		m_polygons[23] = ToWorldCoordinates(v5);

		m_polygons[24] = ToWorldCoordinates(v4);//next triangle
		m_polygons[25] = ToWorldCoordinates(v5);
		m_polygons[26] = ToWorldCoordinates(v6);
		m_polygons[27] = ToWorldCoordinates(v4);//next triangle
		m_polygons[28] = ToWorldCoordinates(v6);
		m_polygons[29] = ToWorldCoordinates(v7);
		m_polygons[30] = ToWorldCoordinates(v3);//next triangle
		m_polygons[31] = ToWorldCoordinates(v2);
		m_polygons[32] = ToWorldCoordinates(v1);
		m_polygons[33] = ToWorldCoordinates(v3);//next triangle
		m_polygons[34] = ToWorldCoordinates(v1);
		m_polygons[35] = ToWorldCoordinates(v0);
		polygonsSetToWorldCoords = true;
	}
}

////////////////////////////// PRIMITIVE OCTAHEDRON METHODS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\

CPrimitiveOctahedron::CPrimitiveOctahedron()
{
	m_numOfVerts = 8 * 3; // number of vertices for each triangle (3) multiplied by the number of triangles (8)
	m_polygons = new CVector3f[m_numOfVerts];
}

void CPrimitiveOctahedron::SetPolygonsToWorldCoords()
{
	// creates a copy of the vertices at their appropriate world coordinates for the purposes of map data
	if (!polygonsSetToWorldCoords) {
		m_polygons[0] = ToWorldCoordinates(v0);//first triangle
		m_polygons[1] = ToWorldCoordinates(v2);
		m_polygons[2] = ToWorldCoordinates(v1);
		m_polygons[3] = ToWorldCoordinates(v0);//next triangle
		m_polygons[4] = ToWorldCoordinates(v1);
		m_polygons[5] = ToWorldCoordinates(v4);
		m_polygons[6] = ToWorldCoordinates(v0);//next triangle
		m_polygons[7] = ToWorldCoordinates(v4);
		m_polygons[8] = ToWorldCoordinates(v3);
		m_polygons[9] = ToWorldCoordinates(v0);//next triangle
		m_polygons[10] = ToWorldCoordinates(v3);
		m_polygons[11] = ToWorldCoordinates(v2);
		m_polygons[12] = ToWorldCoordinates(v5);//next triangle
		m_polygons[13] = ToWorldCoordinates(v1);
		m_polygons[14] = ToWorldCoordinates(v2);
		m_polygons[15] = ToWorldCoordinates(v5);//next triangle
		m_polygons[16] = ToWorldCoordinates(v4);
		m_polygons[17] = ToWorldCoordinates(v1);
		m_polygons[18] = ToWorldCoordinates(v5);//next triangle
		m_polygons[19] = ToWorldCoordinates(v3);
		m_polygons[20] = ToWorldCoordinates(v4);
		m_polygons[21] = ToWorldCoordinates(v5);//next triangle
		m_polygons[22] = ToWorldCoordinates(v2);
		m_polygons[23] = ToWorldCoordinates(v3);
		polygonsSetToWorldCoords = true;
	}
}
