#pragma once
#include "MyPrimitive.h"

class Puck : public MyPrimitive {

public:
	//Puck pucks[];
	float xPos, yPos,zPos;

	void createPuck();
	Puck();
	Puck(float x,float y,float z);
	~Puck();
};