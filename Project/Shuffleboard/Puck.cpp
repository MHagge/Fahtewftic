#include "Puck.h"

Puck::Puck()
{
	m_sName = "1";
	m_v3Position = vector3(0);
	m_v3Velocity = vector3(0);
	m_v3Accel = vector3(0);
	m_m4Matrix = IDENTITY_M4;
	m_vColor = RERED;
	m_pPuck = new PrimitiveClass();
}

Puck::Puck(String a_sName, vector3 a_v3Position)
{
	m_sName = a_sName;
	m_v3Position = a_v3Position;
	m_v3Velocity = vector3(0);
	m_v3Accel = vector3(0);
	m_m4Matrix = IDENTITY_M4;
	m_vColor = RERED;
	m_pPuck = new PrimitiveClass();
}

Puck::Puck(String a_sName, vector3 a_v3Position, vector3 a_v3Color) {
	m_sName = a_sName;
	m_v3Position = a_v3Position;
	m_v3Velocity = vector3(0);
	m_v3Accel = vector3(0);
	m_m4Matrix = IDENTITY_M4;
	m_vColor = a_v3Color;
	m_pPuck = new PrimitiveClass();
}

Puck & Puck::operator=(Puck const & other)
{
	return *this;
}

Puck::~Puck()
{
}

void Puck::GenerateSphere()
{
	m_pPuck->GenerateSphere(1.f, 5, m_vColor);
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

vector3 Puck::GetColor()
{
	return m_vColor;
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

void Puck::SetColor(vector3 a_v3Color)
{
	m_vColor = a_v3Color;
}

void Puck::Render(matrix4 m4Projection, matrix4 m4View)
{
	m_pPuck->Render(m4Projection, m4View, m_m4Matrix);
}
