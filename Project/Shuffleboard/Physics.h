#pragma once

#include "RE\ReEngAppClass.h"
#include "RE\ReEng.h"
#include "Puck.h"

using namespace ReEng;

class Physics {
private:
	static Physics* m_pInstance;

	float m_fFriction;

	void Init(void);
	Physics::Physics();
	Physics::Physics(Physics const& other);
	Physics& Physics::operator=(Physics const& other);
	Physics::~Physics();

public:
	static Physics* GetInstance();
	void Release(void);
	static void ReleaseInstance();
	matrix4 Shoot(Puck& a_puObject, matrix4 a_m4model, float a_fAngle, float a_fPower);
	matrix4 UpdatePhysics(Puck& a_puObject, matrix4 a_m4model);
};