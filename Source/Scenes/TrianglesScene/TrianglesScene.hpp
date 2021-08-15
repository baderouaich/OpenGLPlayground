#pragma once
#include "Scenes/Scene.hpp"
#include <Shader/Shader.hpp>
#include <memory>

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

private:
	std::unique_ptr<Shader> m_shader;
};

