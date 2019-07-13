#include "camera.h"
#include <Windows.h>

#include ".\include\glew.h"									// Header File For The Glaux Library
#include ".\include\gl.h"											// Header File For The OpenGL32 Library
#include ".\include\glu.h"									// Header File For The GLu32 Library

#include <math.h>

#include "gamewindow.h"

// Set up a default camera
Camera::Camera()
{
	m_position = CVector3f(0.0f, 4.0f, 0.0f);
	m_viewPoint = CVector3f(0.0f, 0.75f, 5.0f);
	m_upVector = CVector3f(0.0f, 0.0f, 0.0f); 
	m_currentSpeed = 5.0f;
	m_totalVerticalRotation = 0.0f;
}

// Set a specific camera
void Camera::Set(const CVector3f &position, const CVector3f &view, const CVector3f &up_vector, const float &speed)
{
	m_position = position;
	m_viewPoint = view;
	//m_viewPoint.RotateAboutAxis
	m_upVector = up_vector;
	m_currentSpeed = speed;

	Look();
}

// Get the camera rotation using the mouse
void Camera::SetViewByMouse()
{  
	int middle_x = GameWindow::SCREEN_WIDTH >> 1;
	int middle_y = GameWindow::SCREEN_HEIGHT >> 1;


	POINT mouse;
	GetCursorPos(&mouse);

	if (mouse.x == middle_x && mouse.y == middle_y) {
		return;
	}

	SetCursorPos(middle_x, middle_y);

	float dx = (float) (middle_x - mouse.x) / 50.0f;
	float dy = (float) (middle_y - mouse.y) / 50.0f;


	m_totalVerticalRotation += dy;

	// Clip the rotation rotation about the strafe vector to [-MAX_STRAFE_ROTATION, MAX_STRAFE_ROTATION]
	if (m_totalVerticalRotation > MAX_VERTICAL_ROTATION) {
		m_totalVerticalRotation = MAX_VERTICAL_ROTATION;
	} else if (m_totalVerticalRotation < -MAX_VERTICAL_ROTATION) {
		m_totalVerticalRotation = -MAX_VERTICAL_ROTATION;
	} else {
		RotateView(dy, m_strafeVector);
	}

	RotateView(dx, CVector3f(0, 1, 0));
}

// Returns angle to rotate the player model by and handles vertical camera rotation
float Camera::SetCameraViewByPlayer()
{
	int middle_x = GameWindow::SCREEN_WIDTH >> 1;
	int middle_y = GameWindow::SCREEN_HEIGHT >> 1;


	POINT mouse;
	GetCursorPos(&mouse);

	if (mouse.x == middle_x && mouse.y == middle_y) {
		return 0;
	}

	SetCursorPos(middle_x, middle_y);
	
	float dx = (float)(middle_x - mouse.x) / 50.0f;
	float dy = (float)(middle_y - mouse.y) / 50.0f;

	m_totalVerticalRotation += dy;

	// Clip the rotation rotation about the strafe vector to [-MAX_STRAFE_ROTATION, MAX_STRAFE_ROTATION]
	if (m_totalVerticalRotation > MAX_VERTICAL_ROTATION) {
		m_totalVerticalRotation = MAX_VERTICAL_ROTATION;
	}
	else if (m_totalVerticalRotation < -(MAX_VERTICAL_ROTATION/2)) {
		m_totalVerticalRotation = -(MAX_VERTICAL_ROTATION/2);
	}
	else {
		RotateView(dy, m_strafeVector);
	}

	return dx;
}

// Rotate the camera viewpoint around a vector
void Camera::RotateView(float angle, CVector3f &vector)
{
	CVector3f view = m_viewPoint - m_position;
	CVector3f rotatedView = view.RotateAboutAxis(angle, vector);
	m_viewPoint = m_position + rotatedView;
}

// Move the camera left/right
void Camera::Strafe(float speed)
{
	m_position.x += m_strafeVector.x * speed;
	m_position.z += m_strafeVector.z * speed;

	m_viewPoint.x += m_strafeVector.x * speed;
	m_viewPoint.z += m_strafeVector.z * speed;
}

// Move the camera forward/backward
void Camera::Advance(float speed)
{
	CVector3f view = m_viewPoint - m_position;
	view.Normalise();

	m_position += view * speed;
	m_viewPoint += view * speed;

}

// Move the camera up / down
void Camera::MoveUp(float speed)
{
	m_position += m_upVector * speed;
	m_viewPoint += m_upVector * speed;
}

// Update the camera -- note this typically involves updating the camera position (m_vPosition), viewpoint (m_vViewPoint), and stafe vector (m_vStrafeVector)
void Camera::Update(double dt)
{
	//float yValue = m_position.y;		//uncomment for terrain height based camera
	Movement(dt);
	//m_position.y = yValue;			//uncomment for terrain height based camera
	SetViewByMouse();
}

// Call gluLookAt to put a viewing matrix on the modelview matrix stack
void Camera::Look()
{
	gluLookAt(
		m_position.x, m_position.y, m_position.z,
		m_viewPoint.x, m_viewPoint.y, m_viewPoint.z,
		m_upVector.x, m_upVector.y, m_upVector.z);

	m_strafeVector = (m_viewPoint - m_position) % m_upVector;
	m_strafeVector.Normalise();

}

// Move the camera based on arrow keys or WSAD keys
void Camera::Movement(double dt)
{	
	float speed = (float) dt * m_currentSpeed;

	if((GetKeyState(VK_UP) & 0x80 || GetKeyState('W') & 0x80)) {		
		Advance(speed);	// Forward
	}

	if((GetKeyState(VK_DOWN) & 0x80 || GetKeyState('S') & 0x80)) {	
		Advance(-speed);	// Backward
	}

	if((GetKeyState(VK_LEFT) & 0x80 || GetKeyState('A') & 0x80)) {	
		Strafe(-speed); // Left
	}

	if((GetKeyState(VK_RIGHT) & 0x80 || GetKeyState('D') & 0x80)) {			
		Strafe(speed); // Right
	}	
}

CVector3f Camera::GetPosition() const
{
	return m_position;
}

CVector3f Camera::GetViewPoint() const
{
	return m_viewPoint;
}

CVector3f Camera::GetUpVector() const
{
	return m_upVector;
}

CVector3f Camera::GetStrafeVector() const
{
	return m_strafeVector;
}