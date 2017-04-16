#pragma once

#include "RE\ReEngAppClass.h"
#include "RE\ReEng.h"
#include "MyPrimitive.h"

using namespace ReEng;

class Board {
private:
	float m_fwidth;
	float m_fheight;
	float m_fsize;
	vector3 m_v3Position;
	std::vector<PrimitiveClass> m_vpcolliders;
	MeshManagerSingleton* m_pMeshMngr = nullptr;

public:
	Board(vector3 a_v3Position);
	Board(vector3 a_v3Position, float a_size);
	Board(Board &other);
	~Board();

	int CalculatePoints();
	void Render();
};