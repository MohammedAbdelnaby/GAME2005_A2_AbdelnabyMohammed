#pragma once
#ifndef __PLAY_SCENE__
#define __PLAY_SCENE__

#include "Scene.h"
#include "Plane.h"
#include "Player.h"
#include "Button.h"
#include "Label.h"
#include "Box.h"
#include "Obstacle.h"

class PlayScene : public Scene
{
public:
	PlayScene();
	~PlayScene();

	// Scene LifeCycle Functions
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	virtual void handleEvents() override;
	virtual void start() override;
private:
	// IMGUI Function
	void GUI_Function() const;
	std::string m_guiTitle;
	Box* m_box;
	glm::vec2 m_mousePosition;
	float m_mass = 12.8;
	glm::vec2 m_acceleration;
	glm::vec2 velocity;
	float m_gravity = -980;
	float m_friction = 0.42;
	bool m_isGrounded;
	Obstacle* m_obstacle;

};

#endif /* defined (__PLAY_SCENE__) */