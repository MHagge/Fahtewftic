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
	std::vector<PrimitiveClass*> m_vpPlanes;
	std::vector<matrix4> m_vm4WorldMats;

public:
	Board();
	Board(vector3 a_v3Position);
	Board(vector3 a_v3Position, float a_size);
	Board(Board &other);
	void DeleteBoard();
	void Init();

	int CalculatePoints();
	void Render(matrix4 a_m4Proj, matrix4 a_mView);
	void SetPosition(vector3 a_v3Input);
};