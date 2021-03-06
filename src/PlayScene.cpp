#include "PlayScene.h"
#include "Game.h"
#include "EventManager.h"
#include <sstream>

// required for IMGUI
#include "imgui.h"
#include "imgui_sdl.h"
#include "Renderer.h"
#include "Util.h"

PlayScene::PlayScene()
{
	PlayScene::start();
}

PlayScene::~PlayScene()
= default;

void PlayScene::draw()
{
	TextureManager::Instance().draw("background", 400, 300, 0, 255, true);
	drawDisplayList();
	SDL_SetRenderDrawColor(Renderer::Instance().getRenderer(), 0, 0, 255, 255);
	SDL_RenderDrawLine(Renderer::Instance().getRenderer(), 0, 300,
		0 + cos(-m_angle * (3.14 / 180)) * 800, 300 + sin(m_angle * (3.14 / 180)) * 800);
	SDL_SetRenderDrawColor(Renderer::Instance().getRenderer(), 255, 255, 255, 255);
}

void PlayScene::update()
{
	float DeltaTime = Game::Instance().getDeltaTime();
	updateDisplayList();
	if (m_launch)
	{
		if (m_velocityX >= 0)
		{
			m_time += DeltaTime;
		}
		if (m_box->getTransform()->position.y <= 600 - m_box->getHeight() / 2)
		{
			m_velocityY -= m_accelerationY * (sin(m_angle * (M_PI / 180))) * DeltaTime;
			m_velocityX += m_accelerationX * cos(m_angle * (M_PI / 180)) * DeltaTime;
			m_box->getTransform()->position.y += m_velocityY * DeltaTime;
			m_box->getTransform()->position.x += m_velocityX * DeltaTime;
		}
		else
		{
			m_box->setAngle(0);
			if (m_velocityX >= 0)
			{
				m_accelerationX = -(m_frictionForce - m_forceY) / m_mass * (cos(m_angle * (M_PI / 180)));
				m_velocityX += m_accelerationX * DeltaTime;
				m_box->getTransform()->position.x += m_velocityX * DeltaTime;
			}
		}
	}
	else
	{
		m_box->setAngle(m_angle);
		m_forceX = m_mass * -m_gravity * (sin(m_angle * (M_PI / 180)));
		m_forceY = m_mass * m_gravity * (sin(m_angle * (M_PI / 180)));
		m_frictionForce = m_forceY * m_friction;
		m_accelerationX = m_forceX / m_mass;
		m_accelerationY = m_forceY / m_mass;
	}
	m_distance = (m_box->getTransform()->position.x - 10);
	std::stringstream distancetravled;
	distancetravled << "Displacement(X):" << m_distance << " Angle:" << m_angle << " Gravity:" << m_gravity << " Time:" << m_time;
	const std::string distanceString = distancetravled.str();
	m_distanceUI->setText(distanceString);
}

void PlayScene::clean()
{
	removeAllChildren();
}

void PlayScene::handleEvents()
{
	EventManager::Instance().update();


	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance().quit();
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_1))
	{
		TheGame::Instance().changeSceneState(START_SCENE);
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_2))
	{
		TheGame::Instance().changeSceneState(END_SCENE);
	}
}

void PlayScene::start()
{
	const SDL_Color blue = { 0 , 0, 255, 255 };
	// Set GUI Title
	m_guiTitle = "Play Scene";
	TextureManager::Instance().load("../Assets/textures/background.png", "background");


	m_box = new Box();
	m_box->getTransform()->position = glm::vec2(10.0f, 275.0f);
	m_box->setAngle(m_angle);
	addChild(m_box);


	m_pInstructionsLabel = new Label("\" ` \" for ImGui and all the controls", "Consolas", 40, blue, glm::vec2(400.0f, 23.0f));
	m_pInstructionsLabel->setParent(this);
	addChild(m_pInstructionsLabel);
	m_distanceUI = new Label("", "Consolas", 20, blue, glm::vec2(400.0f, 60.0f));
	m_distanceUI->setParent(this);
	addChild(m_distanceUI);
	ImGuiWindowFrame::Instance().setGUIFunction(std::bind(&PlayScene::GUI_Function, this));
}

void PlayScene::GUI_Function()
{
	// Always open with a NewFrame
	ImGui::NewFrame();

	// See examples by uncommenting the following - also look at imgui_demo.cpp in the IMGUI filter
	//ImGui::ShowDemoWindow();

	ImGui::Begin("Your Window Title Goes Here", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoMove);

	ImGui::SliderFloat("Mass", &m_mass, 20, -20, "%.2f");
	ImGui::SliderFloat("Angle", &m_angle, 30, 45, "%.2f");
	ImGui::SliderFloat("Friction", &m_friction, 1, 0, "%.2f");
	ImGui::SliderFloat("Gravity", &m_gravity, 0.0f, -2000, "%.1f");
	ImGui::Separator();
	if (ImGui::Button("LAUNCH"))
	{
		m_launch = true;
	}
	ImGui::SameLine();
	if (ImGui::Button("RESET"))
	{
		m_launch = false;
		m_box->getTransform()->position = glm::vec2(10.0f, 275.0f);
		m_box->setAngle(m_angle);
		m_forceX = m_mass * -m_gravity * (sin(m_angle * (M_PI / 180)));
		m_forceY = m_mass * m_gravity * (sin(m_angle * (M_PI / 180)));
		m_frictionForce = m_forceY * m_friction;
		m_accelerationX = m_forceX / m_mass;
		m_accelerationY = m_forceY / m_mass;
		m_velocityY = 0;
		m_velocityX = 0;
		m_distance = 0;
		m_time = 0;
	}
	ImGui::End();
}
