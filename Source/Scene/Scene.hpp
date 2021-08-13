#pragma once
#include <Event/Event.hpp>

/*
*	Scene interface
*/
class Scene
{
public:
	friend class Application;

public:
	Scene() noexcept : m_quit(false) {};
	virtual ~Scene() = default;

	/* Scene Life Cicle */
	virtual void OnCreate() = 0;
	virtual void OnEvent(Event& event) = 0;
	virtual void OnUpdate(float dt) = 0;
	virtual void OnDraw() = 0;
	virtual void OnImGuiDraw() = 0;
	virtual void OnDestroy() = 0;

public: /* Accessors */
	const bool WantsToQuit() const noexcept { return m_quit; }

public: /* Modifiers */
	void EndScene() noexcept { m_quit = true; }

protected:
	bool m_quit{};
};