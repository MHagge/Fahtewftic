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


void Physics::Shoot(float a_fAngle, float a_fPower)
{
	m_fVelocity = 0.0f;
	m_fVelocity = a_fPower;
}

void Physics::UpdatePhysics(Puck &a_puObject)
{
	matrix4 a_m4model = a_puObject.GetMatrix();
	m_fVelocity *= m_fFriction;
	a_m4model *= m_fVelocity;
	a_puObject.SetMatrix(a_m4model);
}

void Physics::Init(void)
{
	m_fFriction = 1.00f;
}

Physics::Physics() { Init(); }
Physics::Physics(Physics const& other) { }
Physics & Physics::operator=(Physics const & other){ return *this; }
Physics::~Physics(){ Release(); }


