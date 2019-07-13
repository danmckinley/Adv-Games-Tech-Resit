#ifndef CAMERA_H
#define CAMERA_H

#include "Vector3f.h"

#define MAX_VERTICAL_ROTATION 50

class Camera {
public:
	Camera();
	
	void Set(const CVector3f &position, const CVector3f &view, const CVector3f &up_vector, const float &speed);
	
	CVector3f GetPosition() const;		// Return the camera position (in world coordinates)
	CVector3f GetViewPoint() const;		// Return the point where the camera is looking (in world coordinates)
	CVector3f GetUpVector() const;		// Return the camera up vector (in world coordinates)
	CVector3f GetStrafeVector() const;	// Return the camera strafe vector (in world coordinates)

	void Strafe(float speed);	// Strafing moves the camera left / right
	void Advance(float speed);	// Advance moves the camera forward / backward
	void MoveUp(float speed);	// MoveUp moves the camera up / down

	void Update(double dt);
	void Look();				// Calls gluLookAt() to put the viewing matrix on the modelview matrix stack
	
	void RotateView(float angle, CVector3f &point);
	void SetViewByMouse();
	float SetCameraViewByPlayer(); //
	void Movement(double dt);

private:
	CVector3f m_position;
	CVector3f m_viewPoint;
	CVector3f m_upVector;
	CVector3f m_strafeVector;

	float m_currentSpeed;
	float m_totalVerticalRotation;

};

#endif