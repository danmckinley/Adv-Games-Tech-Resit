#pragma once

#define _USE_MATH_DEFINES								// Will allow certain constants (like M_PI) to be availabe from <math.h>

#include <windows.h>									// Header File For the Windows Library
#include <stdio.h>										// Header File For the Standard Input/Output Functions
#include <stdlib.h>										// Header File For the Standard Library
#include <math.h>										// Header File For the Math header file
#include ".\include\glew.h"								// Header File For the GLEW Library
#include ".\include\gl.h"								// Header File For the OpenGL32 Library
#include ".\include\glu.h"								// Header File For the GLu32 Library

// Includes for game objects
#include "Camera.h"
#include "Gamewindow.h"
#include "HighResolutionTimer.h"
#include "Terrain.h"
#include "SkyBox.h"
#include "OpenAssetImporterMesh.h"
#include "BouncingBall.h"
#include "Audio.h"
#include "Text.h"
#include "Lighting.h"
#include "Material.h"
#include "Md2Animation.h"
#include "SpecialFX.h"
#include "Tetrahedron.h"
#include "Player.h"
#include "Enemy.h"
#include "MetalFloor.h"
#include "ShippingContainer.h"
#include "LampPost.h"
#include "Grenade.h"
#include "Gem.h"
#include "SplashScreen.h"




class Game {
public:
	void HandlePlayerInput(UINT message, WPARAM w_param);
private:
	void Initialise();		// Initialises the games (load assets, etc.)
	void Update();			// Update the simulation at each time step
	void DetectCollisions();
	void SetUpUI();
	void Render();			// Render the scene
	void RenderGrenades();
	void RenderMetalFloors();
	void RenderShippingContainers();
	void RenderLampPosts();
	void GameLoop();		// The game loop

	// Game objects
	Camera m_camera;								// The camera
	CHighResolutionTimer m_highResolutionTimer;		// A timer for measuring the time between frames
	CTerrain m_terrain;								// The terrain (planar)
	CSkybox m_skybox;								// A skybox surrounding the scene
	//CBouncingBall m_ball;							// A bouncing ball, showing simple physics
	CAudio m_audio;									// Audio using FMOD
	CText m_text;									// Text for the head's up display
	CLighting m_lighting;							// Lighting 
	CMaterial m_material;							// Material
	CSpecialFX m_fx;

	COpenAssetImporterMesh m_jeep;
	CPlayer m_player;
	CEnemy m_enemy;
	
	bool m_introScreen;								// A boolean flag indicating if the intro screen is on
	double m_dt;									// A variable to measure the amount of time elasped between frames
	
	COpenAssetImporterMesh m_watchTower;

	char health_ui[32];														// variable for storing the player's current health in the form "Health: (current health)"
	char shields_ui[32];														// variable for storing player's current shields
	CSplashScreen m_splashScreen;											// Member variable splash screen
	CVector3f m_lightPos;
	CVector3f m_lampLightPos;
	std::vector<shared_ptr<CPrimitiveObject>> m_obstacles;					// vector containing all primitive objects  
	std::vector<shared_ptr<CMetalFloor>> m_metalFloors;						// vector of all metalFloors
	std::vector<shared_ptr<CShippingContainer>> m_shippingContainers;		// vector of all shippingContainers
	std::vector<shared_ptr<CLampPost>> m_lampPosts;							// vector of all lampPosts
	std::vector<shared_ptr<CEntity>> m_entities;
	std::vector<shared_ptr<CGrenade>> m_grenades;
	std::vector<shared_ptr<CGem>> m_gems;

	int m_numberOfVerts;
	CVector3f *m_vWorld;
	
public:
	~Game();
	static Game& GetInstance();
	WPARAM Execute();
	void SetHinstance(HINSTANCE hinstance);
	LRESULT ProcessEvents(HWND window,UINT message, WPARAM w_param, LPARAM l_param);
	
private:
	Game::Game();
	Game::Game(const Game&);
	void Game::operator=(const Game&);

	GameWindow m_GameWindow;
	HINSTANCE m_hinstance;
};