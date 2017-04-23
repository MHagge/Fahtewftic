#pragma once
#include "RE\ReEng.h"

class Puck {
private:
	vector3 m_v3Position;
	vector3 m_v3Velocity;
	vector3 m_v3Accel;
	String m_sName;

public:

	Puck();
	Puck(String a_sName, vector3 a_v3Position);
	~Puck();

	String GetName();
	vector3 GetPosition();
	vector3 GetVelocity();
	vector3 GetAcceleration();
	void SetPosition(vector3 a_v3New);
	void SetVelocity(vector3 a_v3New);
	void SetAcceleration(vector3 a_v3New);
};