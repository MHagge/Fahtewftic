#include "AppClass.h"
void AppClass::InitWindow(String a_sWindowName)
{
	super::InitWindow("Sandbox"); // Window Name

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

	m_pPlayer1Puck = new PrimitiveClass();
	m_pPlayer2Puck = new PrimitiveClass();


	m_pPlayer1Puck->GenerateSphere(0.5f, 5, RERED);
	m_pPlayer2Puck->GenerateSphere(0.5f, 5, REBLUE);


}

void AppClass::Update(void)
{
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

	//Adds all loaded instance to the render list
	m_pMeshMngr->AddSkyboxToRenderList();
	m_pMeshMngr->AddInstanceToRenderList("ALL");

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

	if (player1Turn) {
		m_pPlayer1Puck->Render(m4Projection, m4View, m_mPuck);
	}
	else {
		m_pPlayer2Puck->Render(m4Projection, m4View, m_mPuck);
	}

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

	super::Release(); //release the memory of the inherited fields
}