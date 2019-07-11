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
#include "SupportBeam.h"
#include "MetalFloor.h"
#include "SplashScreen.h"



class Game {
public:

private:
	void Initialise();		// Initialises the games (load assets, etc.)
	void Update();			// Update the simulation at each time step
	void Render();			// Render the scene
	void RenderMetalFloors();
	void GameLoop();		// The game loop

	// Game objects
	Camera m_camera;								// The camera
	CHighResolutionTimer m_highResolutionTimer;		// A timer for measuring the time between frames
	CTerrain m_terrain;								// The terrain (planar)
	CSkybox m_skybox;								// A skybox surrounding the scene
	CBouncingBall m_ball;							// A bouncing ball, showing simple physics
	CAudio m_audio;									// Audio using FMOD
	CText m_text;									// Text for the head's up display
	CLighting m_lighting;							// Lighting 
	CMaterial m_material;							// Material
	COpenAssetImporterMesh m_cow;					// A 3D mesh model 
	COpenAssetImporterMesh m_tree;					// Another 3D mesh model
	CMD2Model m_yohko;								// An animated (MD2) model
	CSpecialFX m_fx;
	CTetrahedron m_tetrahedron;

	COpenAssetImporterMesh m_jeep;
	CPlayer m_player;
	
	bool m_introScreen;								// A boolean flag indicating if the intro screen is on
	double m_dt;									// A variable to measure the amount of time elasped between frames
	int m_animation;								// Current animation of MD2 model

	COpenAssetImporterMesh m_watchTower;

	CSupportBeam m_supportBeam;						// Primitive object made using GL_LINES
	//CMetalFloor m_metalFloor;						// Primitive object made using GL_QUADS and GL_QUAD_STRIP
	CSplashScreen m_splashScreen;					// Member variable splash screen
	std::vector<CMetalFloor> m_metalFloors;
	CVector3f m_lightPos;
	

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