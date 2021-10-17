#include "PlayScene.h"
#include "Game.h"
#include "EventManager.h"

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
	drawDisplayList();
	//TextureManager::Instance().draw("ramp", 192, 450, 0, 255, true);
	SDL_SetRenderDrawColor(Renderer::Instance().getRenderer(), 0, 0, 255, 255);
	SDL_RenderDrawLine(Renderer::Instance().getRenderer(), 0, startingY,
		0 + cos(-m_angle *(3.14/180)) * 800,300 + sin(m_angle * (3.14 / 180)) * 800);
	SDL_SetRenderDrawColor(Renderer::Instance().getRenderer(), 255, 255, 255, 255);
}

void PlayScene::update()
{
	float DeltaTime = Game::Instance().getDeltaTime();
	updateDisplayList();
	if (m_launch)
	{
		if (m_box->getTransform()->position.y <= 600 - m_box->getHeight() / 2)
		{
			velocityY -= m_accelerationY * (sin(m_angle * (M_PI / 180))) * DeltaTime;
			velocityX += m_accelerationX * cos(m_angle * (M_PI / 180)) * DeltaTime;
			m_box->getTransform()->position.y += velocityY * DeltaTime;
			m_box->getTransform()->position.x += velocityX * DeltaTime;
		}
		else
		{
			m_box->setAngle(0);
			if (velocityX >= 0)
			{
				m_accelerationX = -(m_frictionForce - m_forceY) / m_mass;
				velocityX += m_accelerationX * DeltaTime;
				m_box->getTransform()->position.x += velocityX * DeltaTime;
			}
		}
		std::cout << (m_box->getTransform()->position.x - 10) << std::endl;
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
	// Set GUI Title
	m_guiTitle = "Play Scene";
	m_obstacle = new Obstacle();
	m_obstacle->getTransform()->position = glm::vec2(200.0f, 455.0f);
	addChild(m_obstacle);
	m_box = new Box();
	m_box->getTransform()->position = glm::vec2(10.0f, 275.0f);
	m_box->setAngle(m_angle);
	addChild(m_box);
	//TextureManager::Instance().load("../Assets/textures/ramp.png", "ramp");
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
	ImGui::SliderInt("Y", &startingY, 0, 300, "%.2f");
	ImGui::SliderFloat("Angle", &m_angle, 30, 45, "%.2f");
	ImGui::Separator();

	if (ImGui::Button("LAUNCH"))
	{
		m_launch = true;
	}
	ImGui::SliderFloat("Gravity", &m_gravity, 0.0f, -2000, "%.1f");
	ImGui::End();
}
