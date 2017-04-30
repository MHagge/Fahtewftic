#include "AppClass.h"
#include "Puck.h"
void AppClass::InitWindow(String a_sWindowName)
{
	super::InitWindow("Planetary ShuffleBoard"); // Window Name
								  // Set the clear color based on Microsoft's CornflowerBlue (default in XNA)
								  //if this line is in Init Application it will depend on the .cfg file, if it
								  //is on the InitVariables it will always force it regardless of the .cfg
	m_v4ClearColor = vector4(0.4f, 0.6f, 0.9f, 0.0f);
	m_pSystem->SetWindowResolution(RESOLUTIONS::C_1280x720_16x9_HD);
	//m_pSystem->SetWindowFullscreen(); //Sets the window to be fullscreen
	//m_pSystem->SetWindowBorderless(true); //Sets the window to not have borders
}

void AppClass::InitVariables(void)
{
	//Reset the selection to -1, -1
	m_selection = std::pair<int, int>(-1, -1);
	//Set the camera position
	m_pCameraMngr->SetPositionTargetAndView(
		vector3(0.0f, 2.5f, 15.0f),//Camera position
		vector3(0.0f, 2.5f, 0.0f),//What Im looking at
		REAXISY);//What is up

	//Load a model onto the Mesh manager

	m_pGameMngr = GameManager::GetInstance();
	m_pPhysics = Physics::GetInstance();

	//m_bBoard = Board(vector3(0, 0, -10));
	//m_bBoard.Init();

	//m_pMeshMngr->LoadModel("Planets\\03A_Moon.obj", "Moon");
	//m_pMeshMngr->LoadModel("Planets\\03_Earth.obj", "Earth");

	m_pGameMngr->AddNewPuck(false);

	//Contains player pucks. WIll certainly be cleaned up in the future
	//int numPucks = 5;
	//for (int i = 0; i < numPucks; i++) {
	//	Puck* nPuck = new Puck();
	//	p1Pucks.push_back(nPuck);
	//	p2Pucks.push_back(nPuck);
	//}

	//for (int i = 0; i < p1Pucks.size; i++) {
	//	//m_pPuck->(pucks[i].xPos, pucks[i].yPos,pucks[i].zPos REBLACK);
	//}
  
				 //Load a model onto the Mesh manager

	m_pPlayerArrow = new PrimitiveClass();

	m_pPlayerArrow->GenerateCone(0.5f, 1.5f, 10, REGREEN);

}

void AppClass::Update(void)
{
	SpacebarInput();

	// position arrow for puck
	m_mArrow = m_mPuck;
	m_mArrow *= glm::translate(vector3(0.0f, 0.0f, -2.0f));
	m_mArrow *= glm::rotate(IDENTITY_M4, 270.0f, REAXISX);

	//Update the system's time
	m_pSystem->UpdateTime();

	//Update the mesh manager's time without updating for collision detection
	m_pMeshMngr->Update();

	//First person camera movement
	if (m_bFPC == true)
		CameraRotation();

	//Call the arcball method
	ArcBall();

	//Set the model matrix for the first model to be the arcball
	m_pMeshMngr->SetModelMatrix(ToMatrix4(m_qArcBall), 0);


	//if (player1Turn) {
	//	m_pMeshMngr->SetModelMatrix(m_mPuck, "Moon");
	//	m_pMeshMngr->AddInstanceToRenderList("Moon");
	//}
	//else {
	//	m_pMeshMngr->SetModelMatrix(m_mPuck, "Earth");
	//	m_pMeshMngr->AddInstanceToRenderList("Earth");
	//}

	m_pGameMngr->Update();

	m_pGameMngr->SetModelMatrix(m_pGameMngr->GetNumOfPucks(), m_mPuck);
	//Adds all loaded instance to the render list
	m_pMeshMngr->AddSkyboxToRenderList();

	Prints();
}

void AppClass::Prints(void)
{
	//Indicate the FPS
	int nFPS = m_pSystem->GetFPS();

	//Print info on the screen
	m_pMeshMngr->PrintLine("");//Add a line on top
	m_pMeshMngr->PrintLine(m_pSystem->GetAppName(), REYELLOW);

	m_pMeshMngr->Print("Selection: ");
	m_pMeshMngr->PrintLine(m_pMeshMngr->GetInstanceGroupName(m_selection.first, m_selection.second), REYELLOW);

	m_pMeshMngr->Print("FPS:");
	m_pMeshMngr->PrintLine(std::to_string(nFPS), RERED);

	m_pMeshMngr->Print("player1Turn: ");
	if (player1Turn == 0) {
		m_pMeshMngr->PrintLine("true", REBLUE);
	}
	else {
		m_pMeshMngr->PrintLine("false", REBLUE);
	}

	m_pMeshMngr->Print("Game State: ");
	if (gameState == 0) {
		m_pMeshMngr->PrintLine("START");
	}
	else if (gameState == 1) {
		m_pMeshMngr->PrintLine("IN_PLAY");
	}
	else if (gameState == 2) {
		m_pMeshMngr->PrintLine("END_ROUND");
	}
	else if (gameState == 3) {
		m_pMeshMngr->PrintLine("END_GAME");
	}

	if (gameState == 0) {
		m_pMeshMngr->PrintLine("Press Tab to Begin");
	}
}

void AppClass::Display(void)
{
	//clear the screen
	ClearScreen();

	matrix4 m4Projection = m_pCameraMngr->GetProjectionMatrix();
	matrix4 m4View = m_pCameraMngr->GetViewMatrix();

	m_pPlayerArrow->Render(m4Projection, m4View, m_mArrow);

	//m_bBoard.Render(m4Projection, m4View);
	m_pGameMngr->RenderObjects(m4Projection, m4View);

	//Render the grid based on the camera's mode:
	//m_pMeshMngr->AddGridToRenderListBasedOnCamera(m_pCameraMngr->GetCameraMode());
	m_pMeshMngr->Render(); //renders the render list
	m_pMeshMngr->ClearRenderList(); //Reset the Render list after render
	m_pGLSystem->GLSwapBuffers(); //Swaps the OpenGL buffers
}

void AppClass::Release(void)
{
	SafeDelete(m_pPlayer1Puck);
	SafeDelete(m_pPlayer2Puck);
	SafeDelete(m_pPlayerArrow);

	m_bBoard.DeleteBoard();

	m_pGameMngr->Release();
	m_pGameMngr->ReleaseInstance();

	m_pPhysics->Release();
	m_pPhysics->ReleaseInstance();


	super::Release(); //release the memory of the inherited fields
}

void AppClass::SwitchGameState(GameStateEnum a_eNewState) {
	switch (gameState)
	{
		case GameStateEnum::start:
			gameState = in_play;
			break;
		case GameStateEnum::in_play:
			gameState = end_round;
			break;
		case GameStateEnum::end_round:
			gameState = end_game;
			break;
		case GameStateEnum::end_game:
			gameState = start;
			break;
	}
}

void AppClass::SpacebarInput()
{
	if (m_bSpacePressed) {
		if (!rotate) {
			rotate = true;
		}
		else {
			rotate = false;
			player1Turn = !player1Turn;
			matrix4 m4puck = m_mPuck;
			m_pGameMngr->SetModelMatrix(m_pGameMngr->GetNumOfPucks(), matrix4(0));
			m_pGameMngr->AddNewPuck(!player1Turn);
		}
		m_bSpacePressed = false;
	}
}