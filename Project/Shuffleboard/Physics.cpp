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

matrix4 Physics::Shoot(Puck &a_puObject, matrix4 a_m4model, float a_fAngle, float a_fPower)
{
	vector3 velocity = vector3(1.0f, 0.0f, 1.0f);
	velocity *= a_fPower;
	a_puObject.SetVelocity(velocity);
	a_m4model *= glm::translate(velocity);
	return a_m4model;
}

matrix4 Physics::UpdatePhysics(Puck &a_puObject, matrix4 a_m4model)
{
	vector3 position = a_puObject.GetPosition();
	vector3 velocity = a_puObject.GetVelocity();
	velocity *= m_fFriction;
	a_puObject.SetVelocity(velocity);
	a_m4model *= glm::translate(velocity);
	return a_m4model;
}

void Physics::Init(void)
{
	m_fFriction = 1.00f;
}

Physics::Physics() { Init(); }
Physics::Physics(Physics const& other) { }
Physics & Physics::operator=(Physics const & other){ return *this; }
Physics::~Physics(){ Release(); }


