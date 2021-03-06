/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/09 (Last Modified on: 15/11)
----------------------------------------------*/
#ifndef __APPLICATION_H_
#define __APPLICATION_H_

#include "RE\ReEngAppClass.h"
#include <SFML\Graphics.hpp>

#include "Board.h"
#include "Physics.h"
#include "GameManager.h"

using namespace ReEng; //Using ReEng namespace to use all the classes in the dll

enum GameStateEnum {
	start,
	in_play,
	end_round,
	end_game,
};

class AppClass : public ReEngAppClass
{
	Board m_bBoard;
	PrimitiveClass* m_pPlayer1Puck = nullptr;
	PrimitiveClass* m_pPlayer2Puck = nullptr;
	Physics* m_pPhysics = nullptr;
	PrimitiveClass* m_pPlayerArrow = nullptr;
	GameManager* m_pGameMngr = nullptr;

	PrimitiveClass* m_pCubeMeter = nullptr;
	PrimitiveClass* m_pMeterBG = nullptr;

	matrix4 m_mPuck = IDENTITY_M4;
	matrix4 m_mArrow = IDENTITY_M4;
	matrix4 scaleMeter = IDENTITY_M4;
	matrix4 scaleMBG = IDENTITY_M4;

	vector3 m_vPosition = vector3(0.0f, 0.0f, 0.0f);

	bool rotate = false;
	bool movement = true;
	bool m_bSpacePressed = false;
	bool shooting = false;
	bool shootingfinished = false;

	float fPercentage;
	float fPercentage2;

	bool player1Turn = true;
	GameStateEnum gameState = GameStateEnum::start;

	float totalR = 0.0f; // total rotation of the current puck
	float totalP = 0.0f; // total amount left/right of puck

	int maxTurns = 0; // the max turns will be 6 - 3 each puck

	vector3 newPosition;
public:
	typedef ReEngAppClass super;

	/*
	USAGE: Constructor
	ARGUMENTS:
	- HINSTANCE hInstance -> Instance of the window
	- LPWSTR lpCmdLine -> Command line
	- int nCmdShow -> Number or arguments
	- bool a_bConsole = false -> create command window flag
	OUTPUT: ---
	*/
	AppClass(HINSTANCE hInstance, LPWSTR lpCmdLine, int nCmdShow, bool a_bUsingConsole = false) : super(hInstance, lpCmdLine, nCmdShow, a_bUsingConsole) {}
	/*
	USAGE: Destructor
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	~AppClass(void) { Release(); }
	/*
	USAGE: Reads the configuration of the application to a file
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	virtual void ReadConfig(void) final {}
	/*
	USAGE: Writes the configuration of the application to a file
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	virtual void WriteConfig(void) final {}
	/*
	USAGE: Initialize ReEng variables necessary to create the window
	ARGUMENTS: String a_sWindowName -> Name of the window
	OUTPUT: ---
	*/
	virtual void InitWindow(String a_sWindowName) final;
	/*
	USAGE: Initializes user specific variables, this is executed right after InitApplicationVariables,
	the purpose of this member function is to initialize member variables specific for this lesson
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	virtual void InitVariables(void) final;
	/*
	USAGE: Updates the scene
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	virtual void Update(void) final;
	/*
	USAGE: Displays the scene
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	virtual void Prints(void) final;
	/*
	USAGE: Displays text for gameplay and for debugging
	*/
	virtual void Display(void) final;
	/*
	USAGE: Manage the response of key presses
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	virtual void ProcessKeyboard(void) final;
	/*
	USAGE: Manage the response of key presses and mouse position
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	virtual void ProcessMouse(void) final;
	/*
	USAGE: Releases the application
	IF INHERITED AND OVERRIDEN MAKE SURE TO RELEASE BASE POINTERS (OR CALL BASED CLASS RELEASE)
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	virtual void Release(void) final;

	virtual void SwitchGameState(GameStateEnum a_eNewState);

	virtual void SpacebarInput();

	virtual void Shoot();
};
/*
USAGE:
ARGUMENTS: ---
OUTPUT: ---
*/
#endif //__APPLICATION_H_
