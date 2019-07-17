#include "3DMaths.h"

int ClassifyBox(CVector3f &center, CVector3f &normal, CVector3f &point,
	float largerAxis, float &distance) {
	// determines if the box is infront, behind, or intersecting the polygon
	float d = (float)PlaneDistance(normal, point);
	distance = (normal.x * center.x + normal.y * center.y + normal.z * center.z + d);

	if (Absolute(distance) < largerAxis / 2) {
		return INTERSECTS;
	}
	else if (distance >= largerAxis / 2) {
		return FRONT;
	}
	return BEHIND;
}

bool EdgeBoxCollision(CVector3f &vCenter, CVector3f vPolygon[], int vertexCount, float radius) {
	CVector3f vPoint;

	// This function takes in the sphere's center, the polygon's vertices, the vertex count
	// and the radius of the sphere.  We will return true from this function if the sphere
	// is intersecting any of the edges of the polygon.  

	// Go through all of the vertices in the polygon
	for (int i = 0; i < vertexCount; i++)
	{
		// This returns the closest point on the current edge to the center of the sphere.
		vPoint = ClosestPointOnLine(vPolygon[i], vPolygon[(i + 1) % vertexCount], vCenter);

		// Now, we want to calculate the distance between the closest point and the center
		float distance = Distance(vPoint, vCenter);

		// If the distance is less than the radius, there must be a collision so return true
		if (distance < radius)
			return true;
	}

	// The was no intersection of the sphere and the edges of the polygon
	return false;
}

CVector3f ClosestPointOnLine(CVector3f vA, CVector3f vB, CVector3f vPoint)
{
	// Create the vector from end point vA to our point vPoint.
	CVector3f vVector1 = vPoint - vA;

	// Create a normalized direction vector from end point vA to end point vB
	CVector3f vVector2 = Normalize(vB - vA);

	// Use the distance formula to find the distance of the line segment (or magnitude)
	float d = Distance(vA, vB);

	// Using the dot product, we project the vVector1 onto the vector vVector2.
	// This essentially gives us the distance from our projected vector from vA.
	float t = vVector2 * vVector1;

	// If our projected distance from vA, "t", is less than or equal to 0, it must
	// be closest to the end point vA.  We want to return this end point.
	if (t <= 0)
		return vA;

	// If our projected distance from vA, "t", is greater than or equal to the magnitude
	// or distance of the line segment, it must be closest to the end point vB.  So, return vB.
	if (t >= d)
		return vB;

	// Here we create a vector that is of length t and in the direction of vVector2
	CVector3f vVector3 = vVector2 * t;

	// To find the closest point on the line segment, we just add vVector3 to the original
	// end point vA.  
	CVector3f vClosestPoint = vA + vVector3;

	// Return the closest point on the line segment
	return vClosestPoint;
}

GLfloat* Normal(GLfloat p[3], GLfloat q[3]) {	// Method to calculate normals from GLfloats
	float a = p[1] * q[2] - p[2] * q[1];
	float b = p[2] * q[0] - p[0] * q[2];
	float c = p[0] * q[1] - p[1] * q[0];
	GLfloat normal[3] = { a, b, c };
	return normal;
}

GLfloat* Normal(CVector3f p, CVector3f q) {	// Method to calculate normals from CVectors, returning a GLfloat
	float a = p.y * q.z - p.z * q.y;
	float b = p.z * q.x - p.x * q.z;
	float c = p.x * q.y - p.y * q.x;
	GLfloat normal[3] = { a, b, c };
	return normal;
}

GLfloat* VertexNormal(CVector3f p, CVector3f q, CVector3f r){
	CVector3f v1 = q - p;
	CVector3f v2 = r - p;
	CVector3f v3 = Cross(v1, v2);
	v3.Normalise();
	GLfloat result[3] = { v3.x, v3.y, v3.z };
	return result;
}


CVector3f Normal(CVector3f vPolygon[]) {	//method to calculate normals from an array of 3 CVectors, returning a CVector
	CVector3f vVector1 = vPolygon[2] - vPolygon[0];
	CVector3f vVector2 = vPolygon[1] - vPolygon[0];
	CVector3f vNormal = vVector1 % vVector2;
	vNormal.Normalise();
	return vNormal;
}

CVector3f Normalize(CVector3f vNormal)
{
	float magnitude = Magnitude(vNormal);				// Get the magnitude of our normal

	// Now that we have the magnitude, we can divide our normal by that magnitude.
	// That will make our normal a total length of 1.  This makes it easier to work with too.

	vNormal.x /= magnitude;								// Divide the X value of our normal by it's magnitude
	vNormal.y /= magnitude;								// Divide the Y value of our normal by it's magnitude
	vNormal.z /= magnitude;								// Divide the Z value of our normal by it's magnitude

	// Finally, return our normalized normal.

	return vNormal;										// Return the new normal of length 1.
}

float Absolute(float num) {	// returns absolute value of float passed in
	if (num < 0) {
		return 0 - num;
	}
	return num;
}

float PlaneDistance(CVector3f Normal, CVector3f Point) {
	float distance = 0;
	distance = -((Normal.x * Point.x) + (Normal.y * Point.y) + (Normal.z * Point.z));
	return distance;
}

bool InsidePolygon(CVector3f intersection, CVector3f poly[], long verticeCount) {
	const double MATCH_FACTOR = 0.99;
	double Angle = 0.0f;
	CVector3f vA, vB;

	for (int i = 0; i < verticeCount; i++) {
		vA = poly[i] - intersection;
		vB = poly[(i + 1) % verticeCount] - intersection;
		Angle += AngleBetweenVectors(vA, vB);
	}

	if (Angle >= (MATCH_FACTOR * (2.0 * M_PI))) {
		return true;
	}
	return false;
}

double AngleBetweenVectors(CVector3f vec1, CVector3f vec2) {
	float dotProduct = Dot(vec1, vec2);
	float vectorsMagnitude = Magnitude(vec1) * Magnitude(vec2);
	double angle = acos(dotProduct / vectorsMagnitude);
	if (_isnan(angle)) {
		return 0;
	}
	return (angle);
}

float Distance(CVector3f vPoint1, CVector3f vPoint2)
{
	double distance = sqrt((vPoint2.x - vPoint1.x) * (vPoint2.x - vPoint1.x) +
		(vPoint2.y - vPoint1.y) * (vPoint2.y - vPoint1.y) +
		(vPoint2.z - vPoint1.z) * (vPoint2.z - vPoint1.z));

	// Return the distance between the 2 points
	return (float)distance;
}

CVector3f GetCollisionOffset(CVector3f & vNormal, float radius, float distance)
{
	CVector3f vOffset = CVector3f(0, 0, 0);
	if (distance > 0) {
		float distanceOver = radius/2 - distance;
		vOffset = vNormal * distanceOver;
	}
	else {
		float distanceOver = radius/2 + distance;
		vOffset = vNormal * -distanceOver;
	}
	return vOffset;
}

float Dot(CVector3f vVector1, CVector3f vVector2) {
	return ((vVector1.x * vVector2.x) + (vVector1.y * vVector2.y) + (vVector1.z * vVector2.z));
}

float Magnitude(CVector3f vNormal) {
	return (float)sqrt((vNormal.x * vNormal.x) + (vNormal.y * vNormal.y) + (vNormal.z * vNormal.z));
}

CVector3f Cross(CVector3f p, CVector3f q) {
	float a = p.y * q.z - p.z * q.y;
	float b = p.z * q.x - p.x * q.z;
	float c = p.x * q.y - p.y * q.x;
	return CVector3f(a, b, c);
}

