#include "Physics.h"

Physics::Physics()
{
	m_fFriction = 0.1f;
	vector3 m_v3Velocity = vector3(0.0f, 0.0f, 0.0f);
}

Physics::Physics(const Physics & other)
{
}

Physics::~Physics(void)
{
}

vector3 Physics::Shoot(vector3 a_v3Position, float a_fAngle, float a_fPower)
{
	m_v3Velocity = vector3(1.0f, 1.0f, 1.0f);
	m_v3Velocity *= a_fPower;
	return m_v3Velocity;
}

vector3 Physics::UpdatePhysics(vector3 a_v3Position)
{
	a_v3Position += m_v3Velocity;
	m_v3Velocity *= m_fFriction;
	return m_v3Velocity;
}
