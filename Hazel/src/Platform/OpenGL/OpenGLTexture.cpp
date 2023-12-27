#include "hzpch.h"
#include "OpenGLTexture.h"

#include "stb_image.h"

#include <glad/glad.h>

namespace Hazel {

	OpenGLTexture2D::OpenGLTexture2D(const std::string& path)
		: m_Path(path)
	{
		int width, height, channels;
		stbi_set_flip_vertically_on_load(1);
		stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
		HZ_CORE_ASSERT(data, "Failed to load image!");
		m_Width = width;
		m_Height = height;

		/*�� OpenGL �У��ڲ���ʽ��internal format�������ݸ�ʽ��data format����������ͬ�ĸ��
		�ڲ���ʽָ���������� GPU �ڴ��еĴ洢��ʽ�������ݸ�ʽָ�����ϴ��� GPU ��ͼ�����ݵĸ�ʽ��
		���磬���ͼ��������ÿ�����ذ����졢�̡���������ɫͨ���������ݸ�ʽ����ָ��Ϊ GL_RGB��
		���ڲ���ʽ����ָ��Ϊ GL_RGB8����ʾ�� GPU �ڴ��У�ÿ����ɫͨ��ռ�� 8 λ���ڲ���ʽ�����ݸ�ʽ֮���ƥ�����Ҫ��
		��ȷ��ͼ�������ܹ���ȷ���ϴ��� GPU ����ʾ������*/
		GLenum internalFormat = 0, dataFormat = 0;
		if (channels == 4)
		{
			internalFormat = GL_RGBA8;
			dataFormat = GL_RGBA;
		}
		else if (channels == 3)
		{
			internalFormat = GL_RGB8;
			dataFormat = GL_RGB;
		}

		HZ_CORE_ASSERT(internalFormat & dataFormat, "Format not supported!");

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		glTextureStorage2D(m_RendererID, 1, internalFormat, m_Width, m_Height);

		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, dataFormat, GL_UNSIGNED_BYTE, data);
		stbi_image_free(data);
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &m_RendererID);
	}

	void OpenGLTexture2D::Bind(uint32_t slot) const
	{
		glBindTextureUnit(slot, m_RendererID);
	}
}