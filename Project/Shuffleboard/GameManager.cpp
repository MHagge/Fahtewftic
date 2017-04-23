#include "GameManager.h"

GameManager* GameManager::m_pInstance = nullptr;
void GameManager::Init(void)
{
	m_pMeshMngr = MeshManagerSingleton::GetInstance();
	m_pBOMngr = MyBOManager::GetInstance();
	m_bBoard = Board(vector3(0, 0, -10));
	m_nPucks = 0;
	m_lPucks = std::vector<Puck>();
	m_lPuckNames = std::vector<std::string>();
}
void GameManager::Release(void)
{
	m_lPucks.clear();
}
GameManager* GameManager::GetInstance()
{
	if (m_pInstance == nullptr)
	{
		m_pInstance = new GameManager();
	}
	return m_pInstance;
}
void GameManager::ReleaseInstance()
{
	if (m_pInstance != nullptr)
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}
}
void GameManager::RenderObjects(matrix4 a_m4Proj, matrix4 a_m4View)
{
	m_pMeshMngr->AddInstanceToRenderList(m_lPuckNames);
	m_bBoard.Render(a_m4Proj, a_m4View);
}
void GameManager::AddNewPuck()
{
	Puck newPuck = Puck(m_lPuckNames[m_lPuckNames.size()] + std::to_string(m_lPuckNames.size()), vector3(0, 0, 0));
	m_lPucks.push_back(newPuck);
	m_lPuckNames.push_back(newPuck.GetName());
	m_lModelMatrices.push_back(matrix4(0));
	m_pBOMngr->AddObject(newPuck.GetName());
}
void GameManager::AddNewPuck(Puck a_puNewPuck)
{
	m_lPucks.push_back(a_puNewPuck);
	m_lPuckNames.push_back(a_puNewPuck.GetName());
	m_lModelMatrices.push_back(matrix4(0));
	m_pBOMngr->AddObject(a_puNewPuck.GetName());
}
void GameManager::AddNewPuck(Puck a_puNewPuck, matrix4 a_m4Model)
{
	m_lPucks.push_back(a_puNewPuck);
	m_lPuckNames.push_back(a_puNewPuck.GetName());
	m_lModelMatrices.push_back(a_m4Model);
	m_pBOMngr->AddObject(a_puNewPuck.GetName());
}
void GameManager::SetModelMatrix(int a_nIndex, matrix4 a_m4Model)
{
	m_lModelMatrices[a_nIndex] = a_m4Model;
}
void GameManager::Update() {
	for (uint i = 0; i < m_lModelMatrices.size(); i++) {
		m_pMeshMngr->SetModelMatrix(m_lModelMatrices[i], m_lPuckNames[i]);
		m_pBOMngr->SetModelMatrix(m_lModelMatrices[i], m_lPuckNames[i]);
	}
}
//The big 3
GameManager::GameManager() { Init(); }
GameManager::GameManager(GameManager const& other) { }
GameManager& GameManager::operator=(GameManager const& other) { return *this; }
GameManager::~GameManager() { Release(); }