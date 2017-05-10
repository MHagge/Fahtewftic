#include "GameManager.h"

GameManager* GameManager::m_pInstance = nullptr;
void GameManager::Init(void)
{
	m_pMeshMngr = MeshManagerSingleton::GetInstance();
	m_pBOMngr = MyBOManager::GetInstance();

	m_bBoard.SetPosition(vector3(0, 0, -10));
	m_bBoard.Init();

	m_nPucks = 0;
	m_lPucks = std::vector<Puck>();
	m_lPuckNames = std::vector<std::string>();
}
void GameManager::Release(void)
{
	m_lPucks.clear();
	m_lPuckNames.clear();
	m_lModelMatrices.clear();

	m_bBoard.DeleteBoard();

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

	m_bBoard.Render(a_m4Proj, a_m4View);
}
void GameManager::AddNewPuck(bool a_bearth)
{
	Puck newPuck;
	if (m_lPuckNames.size() == 0) {
		newPuck = Puck("First", vector3(0, 0, 0));
	}
	else {
		newPuck = Puck(m_lPuckNames[m_lPuckNames.size() - 1] + std::to_string(m_lPuckNames.size()), vector3(0, 0, 0));
	}
	 
	m_lPucks.push_back(newPuck);
	m_lPuckNames.push_back(newPuck.GetName());
	m_lModelMatrices.push_back(matrix4(0));
	m_nPucks++;
	m_pBOMngr->AddObject(newPuck.GetName());
	if (a_bearth) {
		m_pMeshMngr->LoadModel("Planets\\03_Earth.obj", newPuck.GetName());
	}
	else {
		m_pMeshMngr->LoadModel("Planets\\03A_Moon.obj", newPuck.GetName());
	}
	
}
void GameManager::AddNewPuck(bool a_bearth, Puck a_puNewPuck)
{
	m_lPucks.push_back(a_puNewPuck);
	m_lPuckNames.push_back(a_puNewPuck.GetName());
	m_lModelMatrices.push_back(matrix4(0));

	m_pBOMngr->AddObject(a_puNewPuck.GetName());
}
void GameManager::AddNewPuck(bool a_bearth, Puck a_puNewPuck, matrix4 a_m4Model)
{
	m_lPucks.push_back(a_puNewPuck);
	m_lPuckNames.push_back(a_puNewPuck.GetName());
	m_lModelMatrices.push_back(a_m4Model);
	m_nPucks++;
	m_pBOMngr->AddObject(a_puNewPuck.GetName());
	if (a_bearth) {
		m_pMeshMngr->LoadModel("Planets\\03_Earth.obj", a_puNewPuck.GetName());
	}
	else {
		m_pMeshMngr->LoadModel("Planets\\03A_Moon.obj", a_puNewPuck.GetName());
	}

}
void GameManager::SetModelMatrix(int a_nIndex, matrix4 a_m4Model)
{
	m_lModelMatrices[a_nIndex] = a_m4Model;
}
void GameManager::Update() {
	for (uint i = 0; i < m_lModelMatrices.size(); i++) {
		m_lModelMatrices[i] *= glm::translate(m_lPucks[i].GetPosition());

		m_pMeshMngr->SetModelMatrix(m_lModelMatrices[i], m_lPuckNames[i]);
		m_pBOMngr->SetModelMatrix(m_lModelMatrices[i], m_lPuckNames[i]);
	}
	m_pBOMngr->Update();
	for (uint i = 0; i < m_pBOMngr->GetIndexSize() - 1; i++) {

		//For each index collision, also get the object collided with
		//Get all objects collided from colliding indices list
		//fill vector of confirmed collisions
		std::vector<int> indicesA = m_pBOMngr->GetCollidingVector(i);
		std::vector<int> indicesB = m_pBOMngr->GetCollidingVector(i + 1);

		if (indicesA == indicesB) { //placeholder, trying to figure out logistics
			collisions.push_back(indicesA);
			collisions.push_back(indicesB);
		}
	}
}


matrix4 GameManager::GetModelMatrix(int a_nIndex)
{
	return m_lModelMatrices[a_nIndex];
}
void GameManager::SetPuckByIndex(int a_nIndex, Puck a_puNew)
{
	m_lPucks[a_nIndex] = a_puNew;
}
Puck GameManager::GetPuckByIndex(int a_nIndex)
{
	return m_lPucks[a_nIndex];
}
void GameManager::AddInstances()
{
	m_pMeshMngr->AddInstanceToRenderList("ALL");
}
int GameManager::GetNumOfPucks()
{
	return m_nPucks;
}
//The big 3
GameManager::GameManager() { Init(); }
GameManager::GameManager(GameManager const& other) { }
GameManager& GameManager::operator=(GameManager const& other) { return *this; }
GameManager::~GameManager() { Release(); }