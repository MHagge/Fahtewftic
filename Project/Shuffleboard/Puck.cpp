#include "Puck.h"



Puck::Puck()
{
	m_sName = "";
	m_v3Position = vector3(0);
	m_v3Velocity = vector3(0);
	m_v3Accel = vector3(0);
}

Puck::Puck(String a_sName, vector3 a_v3Position)
{
	m_sName = a_sName;
	m_v3Position = a_v3Position;
	m_v3Velocity = vector3(0);
	m_v3Accel = vector3(0);

}

Puck & Puck::operator=(Puck const & other)
{
	return *this;
}

Puck::~Puck()
{
}

String Puck::GetName()
{
	return m_sName;
}

vector3 Puck::GetPosition()
{
	return m_v3Position;
}

vector3 Puck::GetVelocity()
{
	return m_v3Velocity;
}

vector3 Puck::GetAcceleration()
{
	return m_v3Accel;
}

matrix4 Puck::GetMatrix()
{
	return m_m4Matrix;
}

void Puck::SetPosition(vector3 a_v3New)
{
	m_v3Position = a_v3New;
}

void Puck::SetVelocity(vector3 a_v3New)
{
	m_v3Velocity = a_v3New;
}

void Puck::SetAcceleration(vector3 a_v3New)
{
	m_v3Accel = a_v3New;
}

void Puck::SetMatrix(matrix4 a_m4New)
{
	m_m4Matrix = a_m4New;
}
