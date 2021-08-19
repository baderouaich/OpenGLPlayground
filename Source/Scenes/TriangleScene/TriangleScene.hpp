#pragma once
#include "Scenes/Scene.hpp"
#include <Graphics/Shader/Shader.hpp>
#include <Graphics/Buffer/VertexBuffer/VertexBuffer.hpp>
#include <Graphics/Buffer/VertexArray/VertexArray.hpp>
#include <Timer/TimeoutTimer.hpp>


class TriangleScene : public Scene
{
public:
	TriangleScene() = default;
	~TriangleScene() = default;

public: /* Scene Life Cicle */
	void OnCreate() override;
	void OnEvent(Event& event) override;
	void OnUpdate(float dt)  override;
	void OnDraw()  override;
	void OnImGuiDraw()  override;
	void OnDestroy()  override;


private:
	std::shared_ptr<VertexArray> m_vertex_array; // < Triangle's vertex array, will hold vertex buffers, and index buffer
	std::shared_ptr<Shader> m_shader; // < Triangle's shader
	glm::vec4 m_triangle_color{1.0f}; // < Triangle's color, will be modified by settings ui, and set to shaders uniforms

	// 3 Vertices (3 points) to draw triangle (See OpenGL Tutorials/Triangle Vertices.png)
	static constexpr std::array<float, 9> TRIANGLE_VERTICES
	{
		/* Vertex 1 xyz */ -1.0f, -1.0f, 0.0f, // left bottom 0
		/* Vertex 2 xyz */ 0.0f, 1.0f, 0.0f,   // top center 1
		/* Vertex 3 xyz */ 1.0f, -1.0f, 0.0f   // right bottom 2
	};
}; 
