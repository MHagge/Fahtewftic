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

	void Init(void);
	GameManager::GameManager();
	GameManager::GameManager(GameManager const& other);
	GameManager& GameManager::operator=(GameManager const& other);
	GameManager::~GameManager();
public:

	GameManager* GetInstance();
	void Release(void);
	void ReleaseInstance();

	void RenderObjects(matrix4 a_m4Proj, matrix4 a_m4View);
	void AddNewPuck(Puck a_puNewPuck);
	void AddNewPuck();
};