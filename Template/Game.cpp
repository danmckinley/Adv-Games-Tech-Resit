/* 
OpenGL Template for IN3026
City University London, School of Informatics
Source code drawn from a number of sources and examples, including contributions from
 - Ben Humphrey (gametutorials.com), Christy Quinn, Sam Kellett, and others

 For educational use by Deparment of Computer Science, City University London UK.

 This template contains a skybox, simple terrain, camera, lighting, mesh loader, sipmle physics, texturing, audio

 Potential ways to modify the code:  Add new geometry types, change the terrain, load new meshes, set up lighting, 
 add in additional music / sound FX, modify camera control, put in a startup screen, collision detection, etc.
 
 Template version 4.0a 13/09/2017
 Dr Greg Slabaugh (gregory.slabaugh.1@city.ac.uk) 
*/


#include "Game.h"


// Constructor.  
Game::Game()  
{
	m_introScreen = true;
	m_dt = 0.0f;
	m_animation = 0;
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



	// Load some meshes
	m_tree.Load("Resources\\Meshes\\elm.3ds");
	m_cow.Load("Resources\\Meshes\\cow4.3ds");

	// Initialise the bouncing ball (position, velocity, acceleration, coefficient of restitution, motion threshold
	m_ball.Initialise(CVector3f(60.0f, 30.0f, 60.0f), CVector3f(0.0f, 0.0f, 0.0f), CVector3f(0.0f, -9.8f, 0.0f), 0.9f, 0.25f);

	// Initialise audio and play background music
	m_audio.Initialise();
	m_audio.LoadEventSound("Resources\\Audio\\Bounce.wav");					// Royalty free sound from freesound.org
	m_audio.LoadMusicStream("Resources\\Audio\\DST-impuretechnology.mp3");	// Royalty free music from http://www.nosoapradio.us/
	m_audio.PlayMusicStream();

	// Load an animated character -- free to use from http://www.gamers.org/pub/idgames2/quake2/graphics/md2/ 
	m_yohko.Load("Resources\\Meshes\\Yohko.md2", "Resources\\Meshes\\Yohko.bmp", "Resources\\Meshes\\YohkoWeapon.md2", "Resources\\Meshes\\YohkoWeapon.bmp");

	m_tetrahedron.Initialise();

	//m_jeep.Load("Resources\\Meshes\\jeep1.obj");
	m_watchTower.Load("Resources\\Meshes\\obj\\wooden watch tower2.obj");
	m_player.Initialise();
	m_supportBeam.Initialise();
	m_splashScreen.Initialise();

	m_lightPos = CVector3f(20, 5, 0);

	for (int i = 0; i < 5; i++) {
		CMetalFloor floor;
		floor.Initialise();
		m_metalFloors.push_back(floor);
	}

	

	/*
	// If you plan to load a number of enemies and store them on an std::vector, it is best to use pointers, like this:
	for (unsigned int i = 0; i < 5; i++) {
	   m_enemies.push_back(new CMD2Model);
	   m_enemies[i]->Load(...);
	}
	*/



}

// Update game objects using a timer
void Game::Update() 
{
	// Update the camera
	if (GetFocus() == m_GameWindow.GetHwnd())
		//m_camera.Update(m_dt);		// original "noclip" style first person camera
		m_player.UpdateCamera(m_camera); //THIRD PERSON camera

			// Often it will be useful to perform collision detection and response in Update()

		
	m_player.Update(m_dt);


	// Update the physical simulation
	bool bounce = m_ball.UpdatePhysics(m_dt);
	if (bounce)
		m_audio.PlayEventSound();				

	// Periodically update audio being played back by FMOD
	m_audio.Update();
	
	m_GameWindow.UpdateFrameRate(m_dt);
}

// Render the scene
void Game::Render() 
{
	// GLuint errCode = glGetError(); // Can check for OpenGL errors with this -- should be zero if no error

	// Clear the buffers and load the identity matrix into the modelview matrix
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	// Calling look will put the viewing matrix onto the modelview matrix stack
	m_camera.Look();

	// Get the camera position and view vector
	CVector3f vPos	= m_camera.GetPosition();
	CVector3f vView = m_camera.GetViewPoint();


	if (m_introScreen == true) {	//If we are on an introscreen, we can render it here, else...
		m_splashScreen.Render(1,1,1,1);

	} else {
		// Render skybox with no lighting
		glDisable(GL_LIGHTING);
		m_skybox.Render(vPos.x,  vPos.y,  vPos.z, 250, 500, 250);  // Render the skybox with lighting off
		m_text.Render("Orange text", 10, 540, 1, 0.5, 0);  // Draw some text -- useful for debugging and head's up displays
		glEnable(GL_LIGHTING);
		

		// Set materials and lighting for the scene
		m_lighting.SetDefaultLighting();
		m_material.SetDefaultMaterial();

		/*									
		m_lighting.SetLight(m_lightPos);		//Here I was experimenting with a point light
		glDisable(GL_LIGHTING);
		glColor3f(1, 1, 1);
		glPushMatrix(); {	//sphere for white light
			glTranslatef(m_lightPos.x, m_lightPos.y, m_lightPos.z);
			glutSolidSphere(0.5, 25, 25);
		}
		glPopMatrix();*/

		// Render the terrain
		m_terrain.Render();

		
		// Render the cow
		/*glPushMatrix();
			glTranslatef(75, 0, 40);
			m_cow.Render(); 
		glPopMatrix();
		
		// Render the tree
		glPushMatrix();
			glTranslatef(20, 0, 20);
			m_tree.Render(); 
		glPopMatrix();

		glPushMatrix(); {
			glTranslatef(0, 0, 50);
			m_jeep.Render();
		}
		glPopMatrix();
		*/

		glPushMatrix(); {
			glTranslatef(30, 0, 30);
			m_supportBeam.Render(0.75, 0.75, 0.75, 1);
		}
		glPopMatrix();

		RenderMetalFloors();			// Method responsible for rendering all of the metalFloors stored in the m_metalFloors vector

		m_player.Render();		

		
		
		glPushMatrix(); {
			glTranslatef(25, -2, 35);
			glScalef(2, 2, 2);
			m_watchTower.Render();
		}
		glPopMatrix();
		
		
		// Render the ball using a red material, no texture 
		glDisable(GL_TEXTURE_2D);
		m_material.SetRedMaterial();
		m_ball.Render();
		glEnable(GL_TEXTURE_2D);
		
		
	}
	SwapBuffers(m_GameWindow.GetHdc());		
}

void Game::RenderMetalFloors()			// Method responsible for rendering all of the metalFloors stored in the m_metalFloors vector
{
	glPushMatrix(); {
		glTranslatef(30, 0, 30);
		m_metalFloors[0].Render(0.75, 0.75, 0.75, 1);
	}
	glPopMatrix();
	glPushMatrix(); {
		glTranslatef(35, 1, 30);
		glScalef(1.25, 1.25, 1.25);
		m_metalFloors[1].Render(0.75, 0.75, 0.75, 1);
	}
	glPopMatrix();
	glPushMatrix(); {
		glTranslatef(40, 2, 30);
		glScalef(1.5, 1.5, 1.5);
		m_metalFloors[2].Render(0.75, 0.75, 0.75, 1);
	}
	glPopMatrix();
	glPushMatrix(); {
		glTranslatef(50, 10, 20);
		glRotatef(90, 1, 0, 0);
		glScalef(2,2,2);
		m_metalFloors[3].Render(0.75, 0.75, 0.75, 1);
	}
	glPopMatrix();
	glPushMatrix(); {
		glTranslatef(50, 2, 10);
		glRotatef(45, 1, 0, 1);
		m_metalFloors[4].Render(0.75, 0.75, 0.75, 1);
	}
	glPopMatrix();
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



LRESULT Game::ProcessEvents(HWND window,UINT message, WPARAM w_param, LPARAM l_param) 
{
	LRESULT result = 0;

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
			case 'a': {
				//m_player.Turn(3);
			}
			break;
			case 'd': {
				//m_player.Turn(-3);
			}
			break;
			case '3': {
				//m_player.Attack();
			}
		}
		break;
	case WM_PAINT:
		PAINTSTRUCT ps;
		BeginPaint(window, &ps);
		EndPaint(window, &ps);
		break;

	case WM_KEYDOWN:
		switch(w_param) {
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;
		case VK_SPACE:
			m_animation++;
			m_yohko.SetAnimation(m_animation);
			break;
		}
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		result = DefWindowProc(window, message, w_param, l_param);
		break;
	}

	return result;
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
