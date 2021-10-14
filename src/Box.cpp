#include "Box.h"
#include "SoundManager.h"
#include "TextureManager.h"

Box::Box()
{
	TextureManager::Instance().load("../Assets/textures/box.png", "box");

	auto size = TextureManager::Instance().getTextureSize("box");
	setWidth(size.x);
	setHeight(size.y);

	getTransform()->position = glm::vec2(300.0f, 300.0f);
	
	getRigidBody()->isColliding = false;

}

Box::~Box()
= default;

void Box::draw()
{
	TextureManager::Instance().draw("box",
		getTransform()->position.x, getTransform()->position.y, m_angle, 255, true);
}

void Box::update()
{
}

void Box::clean()
{
}

void Box::setAngle(float angle)
{
	m_angle = angle;
}

float Box::getAngle()
{
	return m_angle;
}


