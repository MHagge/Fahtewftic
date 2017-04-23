#include "Puck.h"



Puck::Puck()
{
}

Puck::Puck(String a_sName, vector3 a_v3Position)
{
	m_sName = a_sName;
	m_v3Position = a_v3Position;
}

Puck::~Puck()
{
}

String Puck::GetName()
{
	return m_sName;
}
