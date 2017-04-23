#include "Physics.h"

Physics* Physics::m_pInstance = nullptr;

Physics * Physics::GetInstance()
{
	if (m_pInstance == nullptr)
	{
		m_pInstance = new Physics();
	}
	return m_pInstance;
}

void Physics::Release(void)
{
}

void Physics::ReleaseInstance()
{
	if (m_pInstance != nullptr)
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}
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

void Physics::Init(void)
{
	m_fFriction = 0.1f;
}

Physics::Physics() { Init(); }
Physics::Physics(Physics const& other) { }
Physics & Physics::operator=(Physics const & other){ return *this; }
Physics::~Physics(){ Release(); }


