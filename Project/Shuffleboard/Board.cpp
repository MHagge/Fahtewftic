#include "Board.h"

Board::Board(vector3 a_v3Position)
{
	m_v3Position = a_v3Position;

	m_fwidth = 6.0f;
	m_fheight = 10.5f;
	m_fsize = 1.0f;

	m_pMeshMngr = MeshManagerSingleton::GetInstance();
}

Board::Board(vector3 a_v3Position, float a_size)
{
	m_v3Position = a_v3Position;

	m_fwidth = 6 * a_size;
	m_fheight = 10.5 * a_size;
	m_fsize = a_size;

	m_pMeshMngr = MeshManagerSingleton::GetInstance();
}

Board::Board(Board & other)
{

	m_pMeshMngr = MeshManagerSingleton::GetInstance();
}

Board::~Board()
{
}

int Board::CalculatePoints()
{
	return 0;
}

void Board::Render()
{
	vector3 centerPoint = vector3();
	vector3 topPoint = vector3(m_v3Position.x, m_v3Position.y, m_v3Position.z + 5.25);

	MyMesh topTriangle = MyMesh();

	topTriangle.AddVertexPosition(topPoint);
}
