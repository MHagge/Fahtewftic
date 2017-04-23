#pragma once

#include "RE\ReEngAppClass.h"
#include "RE\ReEng.h"

using namespace ReEng;

class Physics {
private:
	static Physics* m_pInstance;

	float m_fFriction;
	float m_fAcceleration;
	vector3 m_v3Velocity;

	void Init(void);
	Physics::Physics();
	Physics::Physics(Physics const& other);
	Physics& Physics::operator=(Physics const& other);
	Physics::~Physics();

public:
	static Physics* GetInstance();
	void Release(void);
	static void ReleaseInstance();

	vector3 Shoot(vector3 a_v3Position, float a_fAngle, float a_fPower);
	vector3 UpdatePhysics(vector3 a_v3Position);
};