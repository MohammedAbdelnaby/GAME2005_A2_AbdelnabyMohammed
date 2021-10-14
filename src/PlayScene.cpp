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
	SDL_RenderDrawLine(Renderer::Instance().getRenderer(), 0, 300, 0 + cos(-m_box->getAngle() *(3.14/180)) * 600,
		300 + sin(m_box->getAngle() * (3.14 / 180)) * 600);
	SDL_SetRenderDrawColor(Renderer::Instance().getRenderer(), 255, 255, 255, 255);
}

void PlayScene::update()
{
	float DeltaTime = 0.016;
	updateDisplayList();
	//if (m_box->getTransform()->position.x >= )
	//{
	//	m_isGrounded = true;
	//}
	//else
	//{
	//	m_isGrounded = false;
	//}
	if (/*m_box->getTransform()->position.y > 0 ||*/ m_isGrounded)
	{
		std::cout << m_box->getTransform()->position.y << ", " << m_box->getTransform()->position.x << std::endl;
		velocity.y = 0;
	}
	else
	{

		velocity.y -= m_gravity * DeltaTime;
	}
	//std::cout << m_box->getTransform()->position.y << ", " << m_box->getTransform()->position.x << std::endl;
	//std::cout << velocity.x << std::endl;
	m_box->getTransform()->position.y += velocity.y * DeltaTime;
	m_box->getTransform()->position.x += velocity.x * DeltaTime;
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
	m_box->getTransform()->position = glm::vec2(10.0f, 80.0f);
	m_box->setAngle(36.86);
	addChild(m_box);
	//TextureManager::Instance().load("../Assets/textures/ramp.png", "ramp");
	ImGuiWindowFrame::Instance().setGUIFunction(std::bind(&PlayScene::GUI_Function, this));
}

void PlayScene::GUI_Function() const
{
	// Always open with a NewFrame
	ImGui::NewFrame();

	// See examples by uncommenting the following - also look at imgui_demo.cpp in the IMGUI filter
	//ImGui::ShowDemoWindow();
	
	ImGui::Begin("Your Window Title Goes Here", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoMove);

	if(ImGui::Button("My Button"))
	{
		std::cout << "My Button Pressed" << std::endl;
	}

	ImGui::Separator();

	static float float3[3] = { 0.0f, 1.0f, 1.5f };
	if(ImGui::SliderFloat3("My Slider", float3, 0.0f, 2.0f))
	{
		std::cout << float3[0] << std::endl;
		std::cout << float3[1] << std::endl;
		std::cout << float3[2] << std::endl;
		std::cout << "---------------------------\n";
	}
	
	ImGui::End();
}
