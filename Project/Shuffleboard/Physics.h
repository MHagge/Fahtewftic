#pragma once

#include "RE\ReEngAppClass.h"
#include "RE\ReEng.h"

using namespace ReEng;

class Physics {
private:
	float m_fFriction;
	float m_fAcceleration;
	float m_fVelocity;

	vector3 m_v3Friction;
	vector3 m_v3Acceleration;
	vector3 m_v3Velocity;

public:
	Physics();
	Physics(const Physics& other);
	~Physics(void);

	void Shoot();
};