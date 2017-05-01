#include "Board.h"

void Board::Init()
{
	m_vpPlanes = std::vector<PrimitiveClass*>();
	m_vm4WorldMats = std::vector<matrix4>();

	m_vsNames = std::vector<String>();

	boManagerObj = MyBOManager::GetInstance();


	//m_vpPlanes[0]->AddVertexPosition(vector3(m_v3Position.x, m_v3Position.y, m_v3Position.z + 5.25f));
	//m_vpPlanes[0]->AddVertexColor(RERED);
	//m_vpPlanes[0]->AddVertexPosition(vector3(m_v3Position.x - .5f, m_v3Position.y, m_v3Position.z + 2.25f));
	//m_vpPlanes[0]->AddVertexColor(RERED);
	//m_vpPlanes[0]->AddVertexPosition(vector3(m_v3Position.x + .5f, m_v3Position.y, m_v3Position.z + 2.25f));
	//m_vpPlanes[0]->AddVertexColor(RERED);
	//
	//m_vpPlanes[0]->CompleteTriangleInfo(true);
	//m_vpPlanes[0]->CompileOpenGL3X();

	//Board Layout
	//    10
	//   8  8
	//  7    7
	// 10   off

	//10 Scoring Area
	m_vpPlanes.push_back(new PrimitiveClass());
	m_vpPlanes[0]->GeneratePlane(1.0f, RERED);

	m_vsNames.push_back("10 Points");
	matrix4 working = glm::translate(IDENTITY_M4, vector3(m_v3Position.x, m_v3Position.y, m_v3Position.z + 3.0f));
	working = glm::rotate(working, 90.0f, vector3(1, 0, 0));
	working = glm::scale(working, vector3(1.5, 3, 2));
	boManagerObj->AddObject(m_vsNames[0], vector3(m_v3Position.x, m_v3Position.y, m_v3Position.z + 3.0f), vector3(1.5f, 3.0f, 3.0f));

	m_vm4WorldMats.push_back(working);

	//8 Scoring Areas
	m_vpPlanes.push_back(new PrimitiveClass());
	m_vpPlanes[1]->GeneratePlane(1.0f, REORANGE);

	m_vsNames.push_back("8 Points L");
	working = glm::translate(IDENTITY_M4, vector3(m_v3Position.x - 1.0f, m_v3Position.y, m_v3Position.z));
	working = glm::rotate(working, 90.0f, vector3(1, 0, 0));
	working = glm::scale(working, vector3(2, 3, 3));
	boManagerObj->AddObject(m_vsNames[1], vector3(m_v3Position.x - 1.0f, m_v3Position.y, m_v3Position.z), vector3(2.0f, 3.0f, 3.0f));

	m_vm4WorldMats.push_back(working);

	m_vpPlanes.push_back(new PrimitiveClass());
	m_vpPlanes[2]->GeneratePlane(1.0f, REORANGE);

	m_vsNames.push_back("8 Points R");
	working = glm::translate(IDENTITY_M4, vector3(m_v3Position.x + 1.0f, m_v3Position.y, m_v3Position.z));
	working = glm::rotate(working, 90.0f, vector3(1, 0, 0));
	working = glm::scale(working, vector3(2, 3, 3));
	boManagerObj->AddObject(m_vsNames[2], vector3(m_v3Position.x + 1.0f, m_v3Position.y, m_v3Position.z), vector3(2.0f, 3.0f, 3.0f));

	m_vm4WorldMats.push_back(working);

	//7 Scoring Areas
	m_vpPlanes.push_back(new PrimitiveClass());
	m_vpPlanes[3]->GeneratePlane(1.0f, REYELLOW);

	m_vsNames.push_back("7 Points L");
	working = glm::translate(IDENTITY_M4, vector3(m_v3Position.x - 1.5f, m_v3Position.y, m_v3Position.z - 3.0f));
	working = glm::rotate(working, 90.0f, vector3(1, 0, 0));
	working = glm::scale(working, vector3(3, 3, 3));
	boManagerObj->AddObject(m_vsNames[3], vector3(m_v3Position.x - 1.5f, m_v3Position.y, m_v3Position.z - 3.0f), vector3(3.0f, 3.0f, 3.0f));

	m_vm4WorldMats.push_back(working);

	m_vpPlanes.push_back(new PrimitiveClass());
	m_vpPlanes[4]->GeneratePlane(1.0f, REYELLOW);

	m_vsNames.push_back("7 Points R");
	working = glm::translate(IDENTITY_M4, vector3(m_v3Position.x + 1.5f, m_v3Position.y, m_v3Position.z - 3.0f));
	working = glm::rotate(working, 90.0f, vector3(1, 0, 0));
	working = glm::scale(working, vector3(3, 3, 3));
	boManagerObj->AddObject(m_vsNames[4], vector3(m_v3Position.x + 1.5f, m_v3Position.y, m_v3Position.z - 3.0f), vector3(3.0f, 3.0f, 3.0f));

	m_vm4WorldMats.push_back(working);

	//Back Scoring Areas
	m_vpPlanes.push_back(new PrimitiveClass());
	m_vpPlanes[5]->GeneratePlane(1.0f, REBLACK);

	m_vsNames.push_back("OFF");
	working = glm::translate(IDENTITY_M4, vector3(m_v3Position.x - 1.5f, m_v3Position.y, m_v3Position.z - 5.0f));
	working = glm::rotate(working, 90.0f, vector3(1, 0, 0));
	working = glm::scale(working, vector3(3, 1, 1));
	boManagerObj->AddObject(m_vsNames[5], vector3(m_v3Position.x - 1.5f, m_v3Position.y, m_v3Position.z - 5.0f), vector3(3.0f, 3.0f, 1.0f));

	m_vm4WorldMats.push_back(working);

	m_vpPlanes.push_back(new PrimitiveClass());
	m_vpPlanes[6]->GeneratePlane(1.0f, RERED);

	m_vsNames.push_back("10 Points Back");
	working = glm::translate(IDENTITY_M4, vector3(m_v3Position.x + 1.5f, m_v3Position.y, m_v3Position.z - 5.0f));
	working = glm::rotate(working, 90.0f, vector3(1, 0, 0));
	working = glm::scale(working, vector3(3, 1, 1));
	boManagerObj->AddObject(m_vsNames[6], vector3(m_v3Position.x + 1.5f, m_v3Position.y, m_v3Position.z - 5.0f), vector3(3.0f, 3.0f, 1.0f));

	m_vm4WorldMats.push_back(working);

}

Board::Board()
{
	m_v3Position = vector3(0, 0, 0);

	m_fwidth = 6.0f;
	m_fheight = 10.5f;
	m_fsize = 1.0f;
}

Board::Board(vector3 a_v3Position)
{
	m_v3Position = a_v3Position;

	m_fwidth = 6.0f;
	m_fheight = 10.5f;
	m_fsize = 1.0f;
}

Board::Board(vector3 a_v3Position, float a_size)
{
	m_v3Position = a_v3Position;

	m_fwidth = 6 * a_size;
	m_fheight = 10.5 * a_size;
	m_fsize = a_size;
}

Board::Board(Board & other)
{

}


Board & Board::operator=(Board const & other)
{
	return *this;
}


void Board::DeleteBoard() {
	for (int i = 0; i < m_vpPlanes.size(); i++) {
		SafeDelete(m_vpPlanes[i]);
	}
}

int Board::CalculatePoints()
{
	//Check colliders for Collisions

	return 0;
}

void Board::Render(matrix4 a_m4Proj, matrix4 a_m4View)
{
	for (int i = 0; i < m_vpPlanes.size(); i++) {
		m_vpPlanes[i]->Render(a_m4Proj, a_m4View, m_vm4WorldMats[i]);
	}


	for (int i = 0; i < m_vsNames.size(); i++) {
		boManagerObj->DisplayOriented(m_vsNames[i], REBLUE);
	}
}

void Board::SetPosition(vector3 a_v3Input)
{
	m_v3Position = a_v3Input;
}

void Board::SetPosition(vector3 a_v3Input)
{
	m_v3Position = a_v3Input;

}
