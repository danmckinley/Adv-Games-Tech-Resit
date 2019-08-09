/* 
OpenGL Template for IN3026
City University London, School of Informatics
Source code drawn from a number of sources and examples, including contributions from
 - Ben Humphrey (gametutorials.com), Christy Quinn, Sam Kellett, and others

 For educational use by Deparment of Computer Science, City University London UK.

 This template contains a skybox, simple terrain, camera, lighting, mesh loader, simple physics, texturing, audio

 Potential ways to modify the code:  Add new geometry types, change the terrain, load new meshes, set up lighting, 
 add in additional music / sound FX, modify camera control, put in a startup screen, collision detection, etc.
 
 Template version 4.0a 13/09/2017
 Dr Greg Slabaugh (gregory.slabaugh.1@city.ac.uk) 
*/


#include "Game.h"
#include <iostream>


// Constructor.  
Game::Game()  
{
	m_introScreen = true;
	m_dt = 0.0f;
	m_numberOfVerts = 0;
	//m_animation = 0;
}

// Destructor.  Technically we could delete all resources, but when the game ends the OS will free memory for us.
Game::~Game() 
{ 
}

// Initialise the game by loading assets and setting up the scene.  Note, it's best to make OpenGL calls here since we know the rendering context is available.
void Game::Initialise()
{
	// Initialise the camera (position, view point, upvector, and speed)
	m_camera.Set(CVector3f(45, 2, 45), CVector3f(0, 0, 1), CVector3f(0, 1, 0), 5.0f);

	// Create the terrain and skybox
	m_terrain.Initialise();
	m_skybox.Create("", 0.0f);

	// Create a class for rendering text
	m_text.Create(m_GameWindow.GetHdc(), "Arial", 18);

	glClearColor(1, 1, 1, 1);
	// Initialise audio and play background music
	m_audio.Initialise();
	m_audio.LoadEventSound("Resources\\Audio\\Bounce.wav");					// Royalty free sound from freesound.org
	m_audio.LoadMusicStream("Resources\\Audio\\DST-BioIndustrial.mp3");	// Royalty free music from http://www.nosoapradio.us/
	m_audio.PlayMusicStream();

	m_splashScreen.Initialise();
	m_watchTower.Load("Resources\\Meshes\\obj\\wooden watch tower2.obj");
	m_player.Initialise();
	m_enemy.Initialise();
	m_mesh.Load("Resources\\Meshes\\Waste\\tris.md2", "Resources\\Meshes\\Waste\\waste.jpg", "Resources\\Meshes\\Waste\\weapon.md2", "Resources\\Meshes\\Waste\\weapon.jpg");


	m_lightPos = CVector3f(30, 5, 30);

	// CREATE OBSTACLES & LOAD THEM INTO WORLD DATA VECTOR
	for (int i = 0; i < 5; i++) {
		shared_ptr<CMetalFloor> floor = make_shared<CMetalFloor>();
		floor->Initialise();
		m_metalFloors.push_back(floor);
		m_numberOfVerts += floor->GetNumberOfVerts();
		m_obstacles.push_back(floor);
	}
	for (int i = 0; i < 2; i++) {
		shared_ptr<CShippingContainer> container = make_shared<CShippingContainer>();
		container->Initialise();
		m_shippingContainers.push_back(container);
		m_numberOfVerts += container->GetNumberOfVerts();
		m_obstacles.push_back(container);
	}
	for (int i = 0; i < 2; i++) {
		shared_ptr<CLampPost> lamp = make_shared<CLampPost>();
		lamp->Initialise();
		m_lampPosts.push_back(lamp);
		m_numberOfVerts += lamp->GetNumberOfVerts();
		m_obstacles.push_back(lamp);
	}
	m_numberOfVerts += 6; // number of verts from m_terrain
	SetUpStaticObjects(); // positions all the obstacle objects in the world

	// Populate the world data (m_vWorld) with vertices
	m_vWorld = new CVector3f[m_numberOfVerts];
	int index = 0;
	// gets the polygon data for each obstacle and stores it in the world data array
	for (shared_ptr<CPrimitiveObject> o : m_obstacles) {
		// reads one vertex at a time
		for (int i = 0; i < o->GetNumberOfVerts(); i++) {
			// access the vertex at i and store in world data
			CVector3f vertex = o->GetVertexAtIndex(i);
			m_vWorld[index].x = vertex.x;
			m_vWorld[index].y = vertex.y;
			m_vWorld[index].z = vertex.z;
			index++;
		}
	}
	// set up the world data for the terrain
	for (int i = 0; i < 6; i++) {
		CVector3f vertex = m_terrain.GetVertexAtIndex(i);
		m_vWorld[index].x = vertex.x;
		m_vWorld[index].y = vertex.y;
		m_vWorld[index].z = vertex.z;
		index++;
	}

	// create the gems
	for (int i = 0; i < 5; i++) { 
		shared_ptr<CGem> gem = make_shared<CGem>();
		gem->Initialise();
		m_gems.push_back(gem);
	}
	// create the enemies
	for (int i = 0; i < 5; i++) {
		shared_ptr<CEnemy> enemy = make_shared<CEnemy>();
		enemy->Initialise();
		m_enemies.push_back(enemy);
	}
}

// Update game objects using a timer
void Game::Update() 
{
	// Update the camera
	if (GetFocus() == m_GameWindow.GetHwnd())
		//m_camera.Update(m_dt);		// original "noclip" style first person camera
		m_player.UpdateCamera(m_camera); //THIRD PERSON camera

	if (!m_introScreen) {				// only update the player and enemies when there is no intro screen
		m_player.Update(m_dt);
		if (m_enemies.size() > 0) {
			for (shared_ptr<CEnemy> e : m_enemies) {
				e->Update(m_dt);
				e->UpdatePlayerReference(m_player.GetPosition());
			}
		}
		if (m_grenades.size() > 0) {
			for (shared_ptr<CGrenade> g : m_grenades) {
				g->Update(m_dt);
			}
		}
		DetectCollisions();
	}

	if (gemScore >= 5) {
		m_introScreen = true;
		m_splashScreen.SetWinScreen();
	}

	// Periodically update audio being played back by FMOD
	m_audio.Update();
	
	m_GameWindow.UpdateFrameRate(m_dt);
}

void Game::DetectCollisions()
{
	// player collision with world
	m_player.CheckWorldCollision(m_vWorld, m_numberOfVerts);
	// enemy collision
	for (shared_ptr<CEnemy> e : m_enemies) {
		// enemy collision with world
		e->CheckWorldCollision(m_vWorld, m_numberOfVerts);
		//enemy collision with player
		if (Distance(m_player.GetPosition(), e->GetPosition()) < 5.0f) {	// really basic space culling
			//m_player.CheckEntityCollision(e->GetBBox())
				m_player.CheckEntityCollision(e->GetBBox());
				//e->CheckEntityCollision(m_player.GetBBox());
				if (m_player.GetBBox().Collision(e->GetBBox())) {
					m_player.DoPlayerDamage(10); 
				}
				if (m_player.GetHealth() <= 0) {
					m_introScreen = true;
					m_splashScreen.SetLoseScreen();
				}

		}

		if (m_grenades.size() > 0) {
			for (shared_ptr<CGrenade> grenade : m_grenades) {
				if (Distance(e->GetPosition(), grenade->GetPosition()) < 5.0f) {
					if (grenade->CheckEntityCollision(e->GetBBox())) {
						e->DoDamage(25);
						grenade->Explode();
					}
				}
			}
		}
	}
	for (shared_ptr<CGem> g : m_gems) {
		if (Distance(m_player.GetPosition(), g->GetPosition()) < 5.0f && !g->GetCollected()) {
			if (g->CheckPlayerCollision(m_player.GetBBox())) {
				g->SetCollected();
				gemScore++;
			}
		}
	}
}

void Game::SetUpUI() {
	char health_as_string[4];
	int health = m_player.GetHealth();
	sprintf(health_as_string, "%d", health);	// saves the player's health as an int into the char array health_as_string
	char default_health_string[] = "Health: ";			// default element of the health ui, i.e it will always say "Health: ..."
	strcpy(health_ui, "");						// copies an empty string into the health_ui member variable
	strcat(health_ui, default_health_string);			// concats the "default_string" variable with health_ui, giving it "Health: "
	strcat(health_ui, health_as_string);		// concats the "health_as_string" char[] with health_ui, giving it "Health: (player health)"

	char shields_as_string[4];					// does the same as above but for the player's shields instead of health
	int shields = m_player.GetShields();
	sprintf(shields_as_string, "%d", shields);
	char default_shields_string[] = "Shields: ";
	strcpy(shields_ui, "");
	strcat(shields_ui, default_shields_string);
	strcat(shields_ui, shields_as_string);

	char gems_as_string[4];					// does the same as above but for the player's shields instead of health
	//gemScore;
	sprintf(gems_as_string, "%d", gemScore);
	char default_gems_string[] = "Gems: ";
	strcpy(gems_ui, "");
	strcat(gems_ui, default_gems_string);
	strcat(gems_ui, gems_as_string);
}

// Render the scene
void Game::Render()
{
	// GLuint errCode = glGetError(); // Can check for OpenGL errors with this -- should be zero if no error

	// Clear the buffers and load the identity matrix into the modelview matrix
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	// Calling look will put the viewing matrix onto the modelview matrix stack
	m_camera.Look();

	// Get the camera position and view vector
	//CVector3f vPos	= m_camera.GetPosition();
	//CVector3f vView = m_camera.GetViewPoint();
	CVector3f vPos = m_player.GetPosition();		// change vPos to player's position so that when the camera is flipped the skybox doesn't move as much


	if (m_introScreen == true) {	//If we are on an introscreen, we can render it here, else...
		m_splashScreen.Render(1, 1, 1, 1);
	}
	else {
		SetUpUI();
		// Render skybox with no lighting
		m_skybox.Render(vPos.x, vPos.y, vPos.z, 250, 500, 250);  // Render the skybox with lighting off
		glDisable(GL_LIGHTING);
		m_text.Render(health_ui, 200, 10, 1, 0, 0);  // Draw some text -- useful for debugging and head's up displays
		m_text.Render(shields_ui, 380, 10, 0, 0, 1);	
		m_text.Render(gems_ui, 550, 10, 0, 1, 0);

		glEnable(GL_LIGHTING);
		// Set materials and lighting for the scene
		m_lighting.SetDefaultLighting();
		m_material.SetDefaultMaterial();

		m_lighting.SetTestLight(m_lightPos);		//Here I was experimenting with a point light
		glDisable(GL_LIGHTING);
		glColor3f(1, 1, 1);
		glPushMatrix(); {	//sphere for white light
			glTranslatef(m_lightPos.x, m_lightPos.y, m_lightPos.z);
			glutSolidSphere(0.5, 25, 25);
		}
		glPopMatrix();
		glEnable(GL_LIGHTING);

		// RENDER ALL OPAQUE (NON-TRANSPARENT) OBJECTS
		// Render the terrain
		m_terrain.Render();

		RenderMetalFloors();			// Method responsible for rendering all of the metalFloors stored in the m_metalFloors vector
		RenderShippingContainers();
		RenderLampPosts();
		RenderGrenades();

		m_player.Render();
		RenderEnemies();

		glPushMatrix(); {
			glTranslatef(25, -2, 35);
			glScalef(2, 2, 2);
			m_watchTower.Render();
		}
		glPopMatrix();

		glPushMatrix(); {
			glTranslatef(30, 4, 0);
			glScalef(0.1f, 0.1f, 0.1f);
			m_mesh.Render(true);
		}
		glPopMatrix();

		// RENDER TRANSPARENT OBJECTS LAST
		RenderGems();

	}
	SwapBuffers(m_GameWindow.GetHdc());
}

void Game::RenderGems() {
	if (m_gems.size() > 0) {
		for (shared_ptr<CGem> g : m_gems){
		g -> Render();}
	}
}

void Game::RenderEnemies() {
	if (m_enemies.size() > 0) {
		for (shared_ptr<CEnemy> e : m_enemies) {
			e->Render();
		}
	}
}

void Game::RenderGrenades() {
	if (m_grenades.size() > 0) {
		for (shared_ptr<CGrenade> g : m_grenades) {
			g->Render();
		}
	}
}

void Game::RenderMetalFloors()			// Method responsible for rendering all of the metalFloors stored in the m_metalFloors vector
{
		m_metalFloors[0]->Render();
		m_metalFloors[1]->Render();
		m_metalFloors[2]->Render();
		m_metalFloors[3]->Render();
		m_metalFloors[4]->Render();
}

void Game::RenderShippingContainers() {
		m_shippingContainers[0]->Render();
		m_shippingContainers[1]->Render();
}

void Game::RenderLampPosts() {
	m_lampPosts[0]->Render();
	glPopMatrix(); {
		m_lampLightPos = m_lampPosts[0]->GetLightPosition();
		m_lighting.SetLight(m_lampLightPos);		//Here I was experimenting with a point light
		glDisable(GL_LIGHTING);
		glColor3f(1, 1, 0);
		glPushMatrix(); {	//sphere for white light
			glTranslatef(m_lampLightPos.x, m_lampLightPos.y, m_lampLightPos.z);
			glutSolidSphere(0.5, 25, 25);
		}
	}
	glPopMatrix();
	glEnable(GL_LIGHTING);
}

// Sets up all static objects in their positions (in world Coordinates)
void Game::SetUpStaticObjects() {
	//metal floors
	m_metalFloors[0]->SetPosition(CVector3f(30, 1, 30));
	m_metalFloors[0]->SetRotation(90, 1, 0, 0);
	m_metalFloors[1]->SetPosition(CVector3f(35, 1, 30));
	m_metalFloors[1]->SetScaling(1.25, 1.25, 1.25);
	m_metalFloors[2]->SetPosition(CVector3f(40, 1, 30));
	m_metalFloors[2]->SetScaling(1.5, 1.5, 1.5);
	m_metalFloors[3]->SetPosition(CVector3f(50, 3, 20));
	m_metalFloors[4]->SetPosition(CVector3f(50, 2, 10));
	//shipping containers
	m_shippingContainers[0]->SetPosition(CVector3f(20, 0, 20));
	m_shippingContainers[0]->SetRotation(45, 0, 1, 0);
	m_shippingContainers[1]->SetPosition(CVector3f(10, 0, 0));
	//lamp posts
	m_lampPosts[0]->SetPosition(CVector3f(30, 0, 20));
}

void Game::GameLoop()
{
	/*
	// This code implements a fixed timer
	m_dt = m_highResolutionTimer.Elapsed();

	if (m_dt > frame_duration) {
		m_highResolutionTimer.Start();

		Update();
		Render();
	}
	*/

	// This code implements a variable timer
	m_highResolutionTimer.Start();
	Update();
	Render();
	m_dt = m_highResolutionTimer.Elapsed();
			

}

WPARAM Game::Execute() 
{
	m_GameWindow.Init(m_hinstance);

	if(!m_GameWindow.GetHdc()) {
		return 1;
	}

	Initialise();

	m_highResolutionTimer.Start();

	double frame_duration = 1.0 / (double) 30.0;  // 30 FPS

	MSG msg;

	while(1) {													
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) { 
			if(msg.message == WM_QUIT) {
				break;
			}

			TranslateMessage(&msg);	
			DispatchMessage(&msg);
		}else{
			GameLoop();
		} 
	}

	m_GameWindow.Deinit();

	return(msg.wParam);
}

void Game::HandlePlayerInput(UINT message, WPARAM w_param) {

	switch (message) {
	case WM_KEYDOWN:
		switch (w_param) {
		case 'W': {
			m_player.SetMoveForward(true);
		}
				  break;
		case 'A': {
			m_player.SetStrafeLeft(true);
		}
				  break;
		case 'S': {
			m_player.SetMoveBackwards(true);
		}
				  break;
		case 'D': {
			m_player.SetStrafeRight(true);
		}
				  break;
		case 'F': {
			m_player.FlipCamera();
		}
				  break;
		case 'V': {
			m_player.Jump();
		}
				  break;
		case 'T': {
			CVector3f vec = m_player.GetPosition();
			vec.y = vec.y + 30;
			m_player.SetPosition(vec);
		}
				  break;

		case 'Q': {
			m_player.Shoot(m_grenades, m_camera);
		}
				  break;
		}
		break;
	case WM_LBUTTONDOWN:
	{
		//m_player.Shoot(m_grenades, m_camera);
	};
		break;
	case WM_KEYUP:
		switch (w_param) {
		case 'W': {
			m_player.SetMoveForward(false);
		}
				  break;
		case 'A': {
			m_player.SetStrafeLeft(false);
		}
				  break;
		case 'S': {
			m_player.SetMoveBackwards(false);
		}
				  break;
		case 'D': {
			m_player.SetStrafeRight(false);
		}
				  break;
		}
		break;
	}
}

LRESULT Game::ProcessEvents(HWND window, UINT message, WPARAM w_param, LPARAM l_param)
{
	LRESULT result = 0;
	HandlePlayerInput(message, w_param);
	switch (message) {
	case WM_SIZE:
		if (!m_GameWindow.GetFullScreen()) {
			m_GameWindow.SizeOpenGLScreen(LOWORD(l_param), HIWORD(l_param));

			RECT dimensions;
			GetClientRect(window, &dimensions);
			m_GameWindow.SetDimensions(dimensions);
		}
		break;

	case WM_CHAR:
		if (m_introScreen = true) {			//pass intro screen if player presses any key
			m_introScreen = false;
		}
		switch (w_param) {
		case '0': {
			// respond to user pressing 0 key
			m_fx.ActivateFog(0.01, 0.6, 0.6, 0.6);
		}
				  break;
		case '1': {
			m_lightPos.y--;
		}
				  break;
		case '2': {
			m_lightPos.y++;
		}
				  break;
		case '3': {
			m_lightPos.x--;
		}
				  break;
		case '4': {
			m_lightPos.x++;
		}
				  break;
		case '5': {
			m_lightPos.z--;
		}
				  break;
		case '6': {
			m_lightPos.z++;
		}
				  break;
		}
		break;
	case WM_PAINT:
		PAINTSTRUCT ps;
		BeginPaint(window, &ps);
		EndPaint(window, &ps);
		break;

	case WM_KEYDOWN:
		switch (w_param) {
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;

		default:
			result = DefWindowProc(window, message, w_param, l_param);
			break;
		}
		return result;
		break;
	}
}




Game& Game::GetInstance() 
{
	static Game instance;

	return instance;
}

void Game::SetHinstance(HINSTANCE hinstance) 
{
	m_hinstance = hinstance;
}


LRESULT CALLBACK WinProc(HWND window, UINT message, WPARAM w_param, LPARAM l_param)
{
	return Game::GetInstance().ProcessEvents(window, message, w_param, l_param);
}

int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE, PSTR, int) 
{
	Game &game = Game::GetInstance();
	game.SetHinstance(hinstance);

	return game.Execute();
}
