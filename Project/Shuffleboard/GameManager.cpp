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
	for (int i = 0; i < m_lPucks.size(); i++) {
		m_lPucks[i].Render(a_m4Proj, a_m4View);
	}
	m_bBoard.Render(a_m4Proj, a_m4View);
}
void GameManager::AddNewPuck(bool a_bearth)
{
	Puck newPuck;
	if (m_lPucks.size() < 1) {
		if (a_bearth) {
			newPuck = Puck("First", REGREEN);
		}
		else {
			newPuck = Puck("First", RERED);
		}
	}
	else {
		if (a_bearth) {
			newPuck = Puck(m_lPuckNames[m_lPuckNames.size() - 1] + std::to_string(m_lPuckNames.size()), REGREEN);
		}
		else {
			newPuck = Puck(m_lPuckNames[m_lPuckNames.size() - 1] + std::to_string(m_lPuckNames.size()), RERED);
		}
	}
	 
	if (a_bearth) {
		newPuck.SetColor(REGREEN);
	}
	else {
		newPuck.SetColor(RERED);
	}
	newPuck.GenerateSphere();
	m_lPucks.push_back(newPuck);
	m_lPuckNames.push_back(newPuck.GetName());
	m_lModelMatrices.push_back(matrix4(0));
	m_nPucks++;
	m_pBOMngr->AddObject(newPuck.GetName());
	
}
void GameManager::AddNewPuck(bool a_bearth, Puck a_puNewPuck)
{
	m_lPucks.push_back(a_puNewPuck);
	m_lPuckNames.push_back(a_puNewPuck.GetName());
	m_lModelMatrices.push_back(matrix4(0));

	m_nPucks++;

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
	if (m_nPucks > 0) {
		m_lPucks[a_nIndex].SetMatrix(a_m4Model);
	}
}
void GameManager::Update() {
	for (uint i = 0; i < m_lPucks.size(); i++) {
		if (m_nPucks > 0) {
			m_pBOMngr->SetModelMatrix(m_lPucks[i].GetMatrix(), m_lPucks[i].GetName());
		}
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

	Scoring();
}


void GameManager::SetUpGame()
{
	ClearList();
	AddNewPuck(true);
	m_nPucks = 1;
}

void GameManager::ClearList()
{
	//m_lPucks.clear();
	m_lPucks = std::vector<Puck>();

}

matrix4 GameManager::GetModelMatrix(int a_nIndex)
{
	return m_lModelMatrices[a_nIndex];
}
void GameManager::SetPuckByIndex(int a_nIndex, Puck a_puNew)
{
	m_lPucks[a_nIndex] = a_puNew;
}
Puck& GameManager::GetPuckByIndex(int a_nIndex)
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
void GameManager::Scoring()
{

	for (int i = 0; i < m_bBoard.m_vsNames.size(); i++) {
		boardCollisions.push_back(m_pBOMngr->GetCollidingVector(m_bBoard.m_vsNames[i]));
	}

	if (boardCollisions.size() > 0) {
		for (int i = 0; i < 7; i++) { //Board piece to board piece

									  //if()
									  //For every board piece
									  //if that index has a vector of colliding objects greater than size 0
									  //and if it does, check color and increase corresponding score
			String name = m_pBOMngr->GetName(m_bBoard.m_vsNames[i]);
			int points = 0;
			bool scored = false;

			if (name == "10 Points" || name == "10 Points Back")
			{
				points = 10;
				scored = true;
			}

			else if (name == "8 Points L" || name == "8 Points R") {

				points = 8;
				scored = true;
			}

			else if (name == "7 Points L" || name == "7 Points R") {
				points = 7;
				scored = true;
			}

			//check to see if that vector is greater than 0
			//If greater than 0, iterate through that vector, For each index get corresponding name
			//loop through m_lPucks, check if above names matches 

			for (int j = 0; j < boardCollisions[i].size(); j++) {
				//boardCollisions[i][j]
				String colName = m_pBOMngr->GetName(boardCollisions[i][j]);
				for (int k = 0; k < m_lPucks.size(); k++) {
					if (m_lPucks[k].GetName() == colName) {
						if (scored) {
							if (m_lPucks[i].GetColor() == RERED) {
								p1Score += points;
							}
							else if (m_lPucks[i].GetColor() == REGREEN) {
								p2Score += points;
							}
						}
					}

				}

			}


		}
	}
}

//The big 3
GameManager::GameManager() { Init(); }
GameManager::GameManager(GameManager const& other) { }
GameManager& GameManager::operator=(GameManager const& other) { return *this; }
GameManager::~GameManager() { Release(); }