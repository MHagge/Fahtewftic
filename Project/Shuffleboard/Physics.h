#pragma once

#include "RE\ReEngAppClass.h"
#include "RE\ReEng.h"
#include "Puck.h"

using namespace ReEng;

class Physics {
private:
	static Physics* m_pInstance;

	float m_fFriction;
	float m_fVelocity;

	void Init(void);
	Physics::Physics();
	Physics::Physics(Physics const& other);
	Physics& Physics::operator=(Physics const& other);
	Physics::~Physics();

public:
	static Physics* GetInstance();
	void Release(void);
	static void ReleaseInstance();
	void Shoot(float a_fAngle, float a_fPower);
	void UpdatePhysics(Puck& a_puObject);

};