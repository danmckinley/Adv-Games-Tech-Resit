#pragma once
#define _USE_MATH_DEFINES
#include <.\windows.h>
#include <math.h>
#include ".\include\gl.h"
#include ".\include\glut.h"
#include "BoundingBox.h"
#include "Vector3f.h"
#include "Texture.h"
#include "3DMaths.h"

////////////////////////////// PRIMITIVE CUBOID CLASS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\

class CPrimitiveObject {
public:
	CPrimitiveObject();
	//virtual void Render(float r, float g, float b, float a) = 0;
	virtual void Render() = 0;
	virtual void Initialise() = 0;
	virtual void SetPolygonsToWorldCoords() = 0;
	//virtual CVector3f GetCenter() = 0;
	void SetPosition(CVector3f newPos);
	void preRender();
	void postRender();
	void SetTexture(std::string path);
	// these two are used instead of direct calls to glScalef
	void SetScaling(GLfloat x, GLfloat y, GLfloat z);	// sets the scaleBy member variable
	void ApplyScaling();								// calls glScalef using the scaleBy member variable
	void SetRotation(GLfloat angle, GLfloat x, GLfloat y, GLfloat z);
	void ApplyRotation();
	void ApplyTranslation();
	void ApplySort();									// calls translation, rotation & scaling methods
	
	CVector3f ToWorldCoordinates(CVector3f vec);		// translates local coordinates to world coordinates
	bool CheckCollision(CBoundingBox bbox);				// used to check for collisions in Game.cpp
	CVector3f GetOffset();				// returns the collision offset vector
	CVector3f* GetPolygonData();
	int GetNumberOfVerts();
	
	
protected:		//protected so subclasses can access these variables
	UINT m_textureID;	
	CVector3f m_position;				// vector to track the object's position in the world
	CTexture texture;
	CVector3f *m_polygons = NULL;		// array of polygons for the primitive object
	int m_numOfVerts = 0;				// variable to store the number of vertices for a given shape
	bool polygonsSetToWorldCoords = false;	//bool to check if the polygons have been transformed to their world coordinates
private:
	CVector3f vOffset;					// vector to offset the colliding entity (such as the player) by
	GLfloat scaleBy[3];
	GLfloat rotateBy[4];
	
};

////////////////////////////// PRIMITIVE CUBOID CLASS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\

class CPrimitiveCuboid : public CPrimitiveObject {
public:
	/*CPrimitiveCuboid(GLfloat ve0[3], GLfloat ve1[3], GLfloat ve2[3], GLfloat ve3[3],
		GLfloat ve4[3], GLfloat ve5[3], GLfloat ve6[3], GLfloat ve7[3]);*/
	CPrimitiveCuboid();
	void SetPolygonsToWorldCoords();
protected:
	CVector3f v0;
	CVector3f v1;
	CVector3f v2;
	CVector3f v3;
	CVector3f v4;
	CVector3f v5;
	CVector3f v6;
	CVector3f v7;
};

////////////////////////////// PRIMITIVE OCTAHEDRON CLASS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\

class CPrimitiveOctahedron : public CPrimitiveObject {
public:
	CPrimitiveOctahedron();
	void SetPolygonsToWorldCoords();
protected:
	CVector3f v0;
	CVector3f v1;
	CVector3f v2;
	CVector3f v3;
	CVector3f v4;
	CVector3f v5;
};