#pragma once
#include "RE\ReEng.h"

class Puck {
private:

	matrix4 m_m4Matrix;
	String m_sName;
	vector3 m_vColor;
	PrimitiveClass* m_pPuck = nullptr;

public:

	Puck();
	Puck(String a_sName);
	Puck(String a_sNamevector3, vector3 a_v3Color);

	Puck& Puck::operator=(Puck const& other);
	~Puck();
	void GenerateSphere();
	String GetName();
	matrix4 GetMatrix();
	vector3 GetColor();
	void SetMatrix(matrix4 a_m4New);
	void SetColor(vector3 a_v3Color);
	void Render(matrix4 m4Projection, matrix4 m4View);
};