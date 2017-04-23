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

Puck Physics::Shoot(Puck a_puObject, float a_fAngle, float a_fPower)
{
	vector3 velocity = vector3(1.0f, 1.0f, 1.0f);
	velocity *= a_fPower;
	a_puObject.SetVelocity(velocity);
	return a_puObject;
}

Puck Physics::UpdatePhysics(Puck a_puObject)
{
	vector3 position = a_puObject.GetPosition();
	vector3 velocity = a_puObject.GetVelocity();
	velocity *= m_fFriction;
	position += velocity;
	a_puObject.SetPosition(position);
	a_puObject.SetVelocity(velocity);
	return a_puObject;
}

void Physics::Init(void)
{
	m_fFriction = 0.1f;
}

Physics::Physics() { Init(); }
Physics::Physics(Physics const& other) { }
Physics & Physics::operator=(Physics const & other){ return *this; }
Physics::~Physics(){ Release(); }


