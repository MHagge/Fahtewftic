#pragma once
#include "RE\ReEng.h"

class Puck {
private:
	vector3 m_v3Position;
	vector3 m_v3Velocity;
	vector3 m_v3Accel;
	matrix4 m_m4Matrix;
	String m_sName;

public:

	Puck();
	Puck(String a_sName, vector3 a_v3Position);
	Puck& Puck::operator=(Puck const& other);
	~Puck();

	String GetName();
	vector3 GetPosition();
	vector3 GetVelocity();
	vector3 GetAcceleration();
	matrix4 GetMatrix();
	void SetPosition(vector3 a_v3New);
	void SetVelocity(vector3 a_v3New);
	void SetAcceleration(vector3 a_v3New);
	void SetMatrix(matrix4 a_m4New);
};