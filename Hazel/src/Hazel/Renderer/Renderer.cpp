#include "hzpch.h"
#include "Renderer.h"

#include <Platform/OpenGL/OpenGLShader.h>

namespace Hazel {
	Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData;

	void Renderer::Init()
	{
		RenderCommand::Init();
	}

	void Renderer::OnWindowResize(uint32_t width, uint32_t height)
	{
		RenderCommand::SetViewport(0, 0, width, height);
	}

	void Renderer::BeginScene(OrthographicCamera& camera)
	{
		m_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, const glm::mat4& transform)
	{
		shader->Bind();
		/*它用于将 shared_ptr 类型的智能指针从一种类型转换为另一种类型。它执行动态转换，
		这意味着它可以安全地在继承层次结构中向上、向下和横向转换指针和引用。例如，如果您有一个基类 A 和一个派生类 B，
		并且您有一个 shared_ptr<A> 类型的智能指针，您可以使用 std::dynamic_pointer_cast 
		将其转换为 shared_ptr<B> 类型的智能指针。如果转换成功，则返回一个新的 shared_ptr 对象，
		该对象与原始智能指针共享所有权（引用计数）。如果转换失败，则返回一个空的 shared_ptr 对象。*/
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_ViewProjection", m_SceneData->ViewProjectionMatrix);
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_Transform", transform);

		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}