#pragma once
#include "RE\ReEng.h"

class Puck {
private:
	vector3 m_v3Position;
	String m_sName;

public:

	Puck();
	Puck(String a_sName, vector3 a_v3Position);
	~Puck();

	String GetName();
};