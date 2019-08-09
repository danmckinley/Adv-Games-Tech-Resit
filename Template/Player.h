#pragma once
#include "Entity.h"

class CPlayer : public CEntity {
public:
	CPlayer();
	void Update(float dt) override;
	void Initialise() override;
	void Render() override;

	void UpdateCamera(Camera &camera); 
	void Advance(float speed);
	void Strafe(float speed);
	void Turn(float angle);
	void Jump();
	void Attack();

	void Movement(double dt);

	void DoPlayerDamage(int damage);

	
									// method which changes the m_rightHandedCamera boolean which 
	void FlipCamera();				// determines which direction the camera is offset behind the player	

	void SetMoveForward(bool b);	//methods for setting the directional movement booleans
	void SetMoveBackwards(bool b);
	void SetStrafeLeft(bool b);
	void SetStrafeRight(bool b);

	void SetStandAnimation();		// methods to set the mesh animation
	void SetRunAnimation();

	void DecreaseShields(int damage);
	int GetShields();
private:
	int m_shieldHealth = 100;
	CVector3f strafeVector; 
	CVector3f camFacing;
	float m_currentSpeed;
	float m_defaultSpeed;
	bool m_rightHandedCamera;		//boolean for handling which side the camera is on relative to player
	bool moveForward = false;		//booleans for handling player movement
	bool moveBackwards = false;
	bool strafeLeft = false;
	bool strafeRight = false;
};