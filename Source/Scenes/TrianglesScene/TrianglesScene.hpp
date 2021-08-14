#pragma once
#include "Scenes/Scene.hpp"

class TrianglesScene : public Scene
{
public:
	TrianglesScene() = default;
	~TrianglesScene() = default;

public: /* Scene Life Cicle */
	void OnCreate() override;
	void OnEvent(Event& event) override;
	void OnUpdate(float dt)  override;
	void OnDraw()  override;
	void OnImGuiDraw()  override;
	void OnDestroy()  override;
};

