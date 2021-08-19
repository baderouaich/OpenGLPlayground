// Book: https://learnopengl.com/book/book_pdf.pdf
#pragma once
#include <Scenes/Scene.hpp>

class Basics_Page41_Section5_8 : public Scene
{
	
public:
	Basics_Page41_Section5_8() = default;
	~Basics_Page41_Section5_8() = default;

public: /* Scene Life Cicle */
	void OnCreate() override
	{

	}
	void OnEvent(Event& event) override {
		EventDispatcher dispatcher(event);
		// Handle Keyboard ESCAPE Press
		dispatcher.Dispatch<KeyPressedEvent>([this](KeyPressedEvent& e) -> bool
			{
				if (e.GetKeyCode() == KeyCode::Escape)
				{
					Scene::Exit();
					return true;
				}
				return false;
			});
	}
	void OnUpdate(float dt)  override {

	}
	void OnDraw()  override {
		// Clear buffers
		glAssert(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));
		glAssert(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT));

	}
	void OnImGuiDraw()  override {

	}
	void OnDestroy()  override {

	}

private:
	

};

