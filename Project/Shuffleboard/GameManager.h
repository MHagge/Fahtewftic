#pragma once
#include "RE\ReEng.h"
#include "Puck.h"
#include "MyBOManager.h"
#include "Board.h"

class GameManager {
private:
	static GameManager* m_pInstance;

	MeshManagerSingleton* m_pMeshMngr = nullptr;
	MyBOManager* m_pBOMngr = nullptr;
	Board m_bBoard;
	int m_nPucks;
	std::vector<Puck> m_lPucks;
	std::vector<std::string> m_lPuckNames;
	std::vector<matrix4> m_lModelMatrices;
	std::vector<std::vector<int>> collisions;


	void Init(void);
	GameManager::GameManager();
	GameManager::GameManager(GameManager const& other);
	GameManager& GameManager::operator=(GameManager const& other);
	GameManager::~GameManager();
public:

	static GameManager* GetInstance();
	void Release(void);
	static void ReleaseInstance();

	void RenderObjects(matrix4 a_m4Proj, matrix4 a_m4View);
	void AddNewPuck(bool a_bearth);
	void AddNewPuck(bool a_bearth, Puck a_puNewPuck);
	void AddNewPuck(bool a_bearth, Puck a_puNewPuck, matrix4 a_m4Model);
	void SetModelMatrix(int a_nIndex, matrix4 a_m4Model);
	matrix4 GetModelMatrix(int a_nIndex);
	void SetPuckByIndex(int a_nIndex, Puck a_puNew);
	Puck GetPuckByIndex(int a_nIndex);
	void AddInstances();
	void Update();
	int GetNumOfPucks();
};