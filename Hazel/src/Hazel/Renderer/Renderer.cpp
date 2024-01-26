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
		/*�����ڽ� shared_ptr ���͵�����ָ���һ������ת��Ϊ��һ�����͡���ִ�ж�̬ת����
		����ζ�������԰�ȫ���ڼ̳в�νṹ�����ϡ����ºͺ���ת��ָ������á����磬�������һ������ A ��һ�������� B��
		��������һ�� shared_ptr<A> ���͵�����ָ�룬������ʹ�� std::dynamic_pointer_cast 
		����ת��Ϊ shared_ptr<B> ���͵�����ָ�롣���ת���ɹ����򷵻�һ���µ� shared_ptr ����
		�ö�����ԭʼ����ָ�빲������Ȩ�����ü����������ת��ʧ�ܣ��򷵻�һ���յ� shared_ptr ����*/
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_ViewProjection", m_SceneData->ViewProjectionMatrix);
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_Transform", transform);

		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}