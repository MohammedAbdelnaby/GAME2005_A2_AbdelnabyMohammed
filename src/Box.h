#pragma once
#ifndef __BOX__
#define __BOX__
#include "DisplayObject.h"

class Box final : public DisplayObject
{
public:
	// constructors
	Box();

	// destructor
	~Box();

	// life cycle functions
	void draw() override;
	void update() override;
	void clean() override;
	void setAngle(float angle);
	float getAngle();
private:
	float m_angle = 0;
};

#endif /* defined (__OBSTACLE__) */