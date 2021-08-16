#pragma once
#include "Scenes/Scene.hpp"
#include <Graphics/Shader/Shader.hpp>
#include <Graphics/Buffer/VertexBuffer/VertexBuffer.hpp>
#include <Graphics/Buffer/VertexBufferArray/VertexBufferArray.hpp>

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

private: /* Initializers */

	/** Create VBO, sets buffer data (trianble vertices)
	*/
	void InitVertexBuffer();

	/** Create IB (which tells opengl which order it should draw vertices 0 1 4 2 3 ...)
	*/
	void InitIndexBuffer();

	/** Create VAO, adds vertex buffer to it
	*/
	void InitVertexBufferArray();

	/** Creates program of vertex and fragment shaders
	*/
	void InitShader();


private: // see example to use bellow at https://github.com/BaderEddineOuaich/PragmaticGameEngine/blob/cd459ac23925a04f7a233afd5bec5ccec655ba14/Sandbox/Source/SandboxApp.cpp
	std::shared_ptr<Shader> m_shader; // Triangle's Shader
	std::shared_ptr<VertexBuffer> m_vertex_buffer; // TRIANGLE_VERTICES's VertexBuffer VBO
	std::shared_ptr<IndexBuffer> m_index_buffer; // TRIANGLE_VERTICES's IndexBuffer IB
	std::shared_ptr<VertexBufferArray> m_vertex_buffer_array; // TRIANGLE_VERTICES's VertexBufferArray VAO
};

