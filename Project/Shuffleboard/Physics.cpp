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

Puck& Physics::Shoot(Puck &a_puObject, float a_fPower)
{
	vector3 direction = (vector3)glm::normalize(a_puObject.GetMatrix()*vector4(1, 1, 1, 0));
	direction *= a_fPower;
	a_puObject.SetVelocity(direction);

	return a_puObject;
	//m_fVelocity = 0.0f;
	//m_fVelocity = a_fPower;
}

Puck& Physics::UpdatePhysics(Puck &a_puObject)
{
	a_puObject.SetVelocity(a_puObject.GetVelocity()*m_fFriction);
	a_puObject.SetMatrix(glm::translate(a_puObject.GetMatrix(), a_puObject.GetVelocity()));

	return a_puObject;
	//matrix4 a_m4model = a_puObject.GetMatrix();
	//m_fVelocity *= m_fFriction;
	//a_m4model *= m_fVelocity;
	//a_puObject.SetMatrix(a_m4model);
}

void Physics::Init(void)
{
	m_fFriction = .05f;
}

Physics::Physics() { Init(); }
Physics::Physics(Physics const& other) { }
Physics & Physics::operator=(Physics const & other){ return *this; }
Physics::~Physics(){ Release(); }


