#pragma once

#include "RE\ReEngAppClass.h"
#include "RE\ReEng.h"

using namespace ReEng;

class Physics {
private:
	float m_fFriction;
	float m_fAcceleration;
	//float m_fVelocity;

	//vector3 m_v3Friction;
	//vector3 m_v3Acceleration;
	vector3 m_v3Velocity;

public:
	Physics();
	Physics(const Physics& other);
	~Physics(void);

	vector3 Shoot(vector3 a_v3Position, float a_fAngle, float a_fPower);
	vector3 UpdatePhysics(vector3 a_v3Position);
};