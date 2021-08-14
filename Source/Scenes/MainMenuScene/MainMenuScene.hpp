#pragma once
#include "Scenes/Scene.hpp"

class MainMenuScene : public Scene
{
public:
	MainMenuScene() = default;
	~MainMenuScene() = default;

public: /* Scene Life Cicle */
	void OnCreate() override;
	void OnEvent(Event& event) override;
	void OnUpdate(float dt)  override;
	void OnDraw()  override;
	void OnImGuiDraw()  override;
	void OnDestroy()  override;
};

