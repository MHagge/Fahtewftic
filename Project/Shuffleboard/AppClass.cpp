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
		vector3(0.0f, 25.0f, 15.0f),//Camera position
		vector3(0.0f, 5.0f, 0.0f),//What Im looking at
		REAXISY);//What is up


	//Load a model onto the Mesh manager

	m_pGameMngr = GameManager::GetInstance();
	m_pPhysics = Physics::GetInstance();

	m_pGameMngr->AddNewPuck(true);

	m_pPlayerArrow = new PrimitiveClass();
	m_pPlayerArrow->GenerateCone(0.5f, 1.5f, 10, REBLUE);

	m_pCubeMeter = new PrimitiveClass();
	m_pCubeMeter->GenerateCube(1.0f, REWHITE);

	m_pMeterBG = new PrimitiveClass();
	m_pMeterBG->GenerateCube(1.0f, REBLACK);
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

	static float fTimer = 0.0f;//creates a timer
	static uint uClock = m_pSystem->GenClock();//ask the system for a new clock id
	float fDeltaTime = m_pSystem->LapClock(uClock);//lap the selected clock
	fTimer += fDeltaTime;//add the delta time to the current clock

	vector3 v3Offset(3.0f, 0.0f, 0.0f); //Offset from the center
	float fTotalTime = 1.5f; //total Time the animation will last
	fPercentage = MapValue(fTimer, 0.0f, fTotalTime, 0.0f, 1.0f); //percentage of the time used

	static vector3 scale1 = vector3(1.0f, 0.0f, 0.0f);
	static vector3 scale2 = vector3(1.0f, 0.0f, 6.0f);

	vector3 v3Meter = glm::lerp(scale1, scale2, fPercentage);
	scaleMeter = glm::translate(IDENTITY_M4, vector3(6.0f, 2.0f, 2.0f));
	scaleMeter = glm::scale(scaleMeter, v3Meter);

	if (fPercentage > 1.0f) {
		std::swap(scale1, scale2);
		fTimer = 0.0f;
	}

	scaleMBG = glm::translate(IDENTITY_M4, vector3(6.0f, 1.9f, 2.0f));
	scaleMBG = glm::scale(scaleMBG, 1.2f, 0.0f, 6.2f);

	static float fTimer2 = 0.0f;//creates a timer
	if (shooting) {
		fTimer2 += fDeltaTime;//add the delta time to the current clock

		fPercentage2 = MapValue(fTimer2, 0.0f, fTotalTime, 0.0f, 1.0f);

		vector3 currentPosition = glm::lerp(m_vPosition, newPosition, fPercentage2);

		m_mPuck = glm::translate(IDENTITY_M4, currentPosition);

		if (fPercentage2 >= 1 && !shootingfinished) {
			//shooting = false;
			shootingfinished = true;
			fTimer2 = 0.0f;
			m_vPosition = newPosition;
		}
	}

	m_pGameMngr->SetModelMatrix(m_pGameMngr->GetNumOfPucks() - 1, m_mPuck);
	//std::cout << m_pGameMngr->GetNumOfPucks() << std::endl;

	//for (uint i = 0; i < m_pGameMngr->GetNumOfPucks(); i++) {
	
	//m_pGameMngr->GetPuckByIndex(0).SetMatrix(m_pPhysics->UpdatePhysics(m_pGameMngr->GetPuckByIndex(0)));

	//m_pGameMngr->GetPuckByIndex(m_pGameMngr->GetNumOfPucks() - 1) = m_pPhysics->UpdatePhysics(m_pGameMngr->GetPuckByIndex(m_pGameMngr->GetNumOfPucks() - 1));
	
		//m_pPhysics->UpdatePhysics(m_pGameMngr->GetPuckByIndex(0));
		//m_pPhysics->UpdatePhysics(m_pGameMngr->GetPuckByIndex(m_pGameMngr->GetNumOfPucks()-1));
	//}
	//m_pGameMngr->SetModelMatrix(0, m_pPhysics->UpdatePhysics(m_pGameMngr->GetPuckByIndex(0), m_pGameMngr->GetModelMatrix(0)));
	m_pGameMngr->Update();

	m_pGameMngr->AddInstances();
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

	m_pMeshMngr->Print("Player 1 Score: ");
	m_pMeshMngr->PrintLine(std::to_string(m_pGameMngr->p1Score), REGREEN);

	m_pMeshMngr->Print("Player 2 Score: ");
	m_pMeshMngr->PrintLine(std::to_string(m_pGameMngr->p2Score), RERED);
}

void AppClass::Display(void)
{
	//clear the screen
	ClearScreen();

	matrix4 m4Projection = m_pCameraMngr->GetProjectionMatrix();
	matrix4 m4View = m_pCameraMngr->GetViewMatrix();

	if (gameState != end_round) {
		m_pPlayerArrow->Render(m4Projection, m4View, m_mArrow);
	}
	if (!rotate && !movement && gameState != end_round) {
		m_pCubeMeter->Render(m4Projection, m4View, scaleMeter);
		m_pMeterBG->Render(m4Projection, m4View, scaleMBG);
	}

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
			m_pGameMngr->SetUpGame();
			m_mPuck = IDENTITY_M4;
			player1Turn = false;
			totalP = 0.0f;
			totalP = 0.0f;
			break;
		case GameStateEnum::in_play:
			gameState = end_round;
			break;
		case GameStateEnum::end_round:
			gameState = end_game;
			break;
		case GameStateEnum::end_game:
			gameState = start;
			maxTurns = 0;
			break;
	}
}

void AppClass::SpacebarInput()
{
	if (m_bSpacePressed) {
		if (!rotate && movement) {
			rotate = true;
			movement = false;
		}
		else if (rotate && !movement) {
			rotate = false;
		}
		else if (!rotate && !movement) {
			if (maxTurns < 5) {
				
				if (!shooting) {
					Shoot();
				}
				if(shootingfinished){
					shooting = false;
					movement = true;
					player1Turn = !player1Turn;
					//m_pGameMngr->SetModelMatrix(0, m_pPhysics->Shoot(m_pGameMngr->GetPuckByIndex(0), m_pGameMngr->GetModelMatrix(0), 0, 2));
					//Puck newPuck = Puck(std::to_string(m_pGameMngr->GetNumOfPucks()), vector3(0, 0, 0));

					m_pGameMngr->AddNewPuck(!player1Turn);

					totalP = 0.0f;
					m_vPosition = vector3(0);
					m_mPuck = IDENTITY_M4;
					maxTurns++;
					fPercentage = 0.0f;
				}
			}
			else {
				SwitchGameState(end_round);
				rotate = false;
				maxTurns = 0;
			}
		}
		m_bSpacePressed = false;
	}
}

void AppClass::Shoot()
{
	shooting = true;
	shootingfinished = false;
	vector3 direction = glm::rotate(vector3(0, 0, -2), totalR, REAXISY);
	//m_vPosition - (m_vPosition + vector3(0, 0, -2));
	direction *= fPercentage*10;

	newPosition = direction;
}
