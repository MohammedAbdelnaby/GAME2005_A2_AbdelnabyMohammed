#pragma once
#ifndef __PLAY_SCENE__
#define __PLAY_SCENE__

#include "Scene.h"
#include "Plane.h"
#include "Player.h"
#include "Button.h"
#include "Label.h"
#include "Box.h"

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
	void GUI_Function();
	std::string m_guiTitle;
	Box* m_box;
	Label* m_pInstructionsLabel{};
	glm::vec2 m_mousePosition;
	Label* m_distanceUI{};


	float m_mass = 128;
	float m_velocityY;
	float m_velocityX;
	float m_angle = 36.87;
	float m_gravity = -980;
	float m_accelerationX;
	float m_forceX;
	float m_forceY;
	float m_accelerationY;
	float m_friction = 0.42;
	float m_frictionForce;
	bool m_isGrounded;
	bool m_launch = false;
	float m_distance = 0;
	float m_time = 0;
};

#endif /* defined (__PLAY_SCENE__) */