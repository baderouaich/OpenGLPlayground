#pragma once
#include "Scenes/Scene.hpp"
#include <Graphics/Shader/Shader.hpp>
#include <Graphics/Buffer/VertexBuffer/VertexBuffer.hpp>
#include <Graphics/Buffer/VertexArray/VertexArray.hpp>


class DynamicTriangleScene : public Scene
{
public:
	DynamicTriangleScene() = default;
	~DynamicTriangleScene() = default;

public: /* Scene Life Cicle */
	void OnCreate() override;
	void OnEvent(Event& event) override;
	void OnUpdate(float dt)  override;
	void OnDraw()  override;
	void OnImGuiDraw()  override;
	void OnDestroy()  override;
	

private:
	std::shared_ptr<VertexBuffer> m_vertex_buffer; // < Triangle's vertex buffer, will store vertices to gpu and keep track
	std::shared_ptr<VertexArray> m_vertex_array; // < Triangle's vertex array, will hold vertex buffers, and index buffer
	std::shared_ptr<Shader> m_shader; // < Triangle's shader

	// 3 Vertices (3 points) to draw triangle (See OpenGL Tutorials/Triangle Vertices.png)
	std::array<float, 9> m_vertices
	{
		/* Vertex 1 xyz */ -0.5f, -0.5f, 0.0f, // left bottom 0
		/* Vertex 2 xyz */ 0.0f, 0.5f, 0.0f,   // top center 1
		/* Vertex 3 xyz */ 0.5f, -0.5f, 0.0f   // right bottom 2
	};
};
