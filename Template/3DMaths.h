#pragma once
#define _USE_MATH_DEFINES
#include <.\windows.h>
#include <math.h>
#include <float.h>
#include ".\include\gl.h"
#include "Vector3f.h"
#define BEHIND		0
#define INTERSECTS	1
#define FRONT		2

// this class holds all of the methods used to calculate the polygon-based collision
// these methods start being called in CPrimitiveObject::CheckCollisions
// I got these methods from the 

int ClassifyBox(CVector3f & bottom, CVector3f & normal, CVector3f & point, float largerAxis, float & distance);
bool EdgeBoxCollision(CVector3f & vCenter, CVector3f vPolygon[], int vertexCount, float radius);
CVector3f ClosestPointOnLine(CVector3f vA, CVector3f vB, CVector3f vPoint);
GLfloat* Normal(GLfloat p[3], GLfloat q[3]);
GLfloat * Normal(CVector3f p, CVector3f q);
CVector3f Normal(CVector3f vPolygon[]);
CVector3f Normalize(CVector3f vNormal);
float Absolute(float num);
float PlaneDistance(CVector3f Normal, CVector3f Point);								
bool InsidePolygon(CVector3f intersection, CVector3f poly[], long verticeCount);	
float Dot(CVector3f vec1, CVector3f vec2);											
float Magnitude(CVector3f vNormal);													
double AngleBetweenVectors(CVector3f vec1, CVector3f vec2);							
float Distance(CVector3f vPoint1, CVector3f vPoint2);
CVector3f GetCollisionOffset(CVector3f &vNormal, float radius, float distance);




