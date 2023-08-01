#include "hzpch.h"
#include "Shader.h"

#include <glad/glad.h>

namespace Hazel {

	//test shader
	/*��δ��봴����һ���յĶ�����ɫ���������������ɫ��Դ���뷢�͵�GL�����붥����ɫ����������Ƿ����ɹ���
	�������ʧ�ܣ�������������־�����ء�����������������һ���յ�Ƭ����ɫ���������Ƭ����ɫ��Դ���뷢�͵�GL��
	����Ƭ����ɫ����������Ƿ����ɹ����������ʧ�ܣ�������������־�����ء�*/
	Shader::Shader(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		// ����һ���յĶ�����ɫ�����
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

		// ��������ɫ��Դ���뷢�͵�GL
		// ע�⣬std::string��.c_str����NULL�ַ���β�ġ�
		const GLchar* source = vertexSrc.c_str();
		glShaderSource(vertexShader, 1, &source, 0);

		// ���붥����ɫ��
		glCompileShader(vertexShader);

		GLint isCompiled = 0;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

			// maxLength����NULL�ַ�
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

			// We don't need the shader anymore.
			glDeleteShader(vertexShader);

			HZ_CORE_ERROR("{0}", infoLog.data());
			HZ_CORE_ASSERT(false, "Vertex shader compilation failure!");
			return;
		}

		// ����һ���յ�Ƭ����ɫ�����
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		// ��Ƭ����ɫ��Դ���뷢�͵�GL
		// ע�⣬std::string��.c_str����NULL�ַ���β�ġ�
		source = fragmentSrc.c_str();
		glShaderSource(fragmentShader, 1, &source, 0);

		// ����Ƭ����ɫ��
		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

			// We don't need the shader anymore.
			glDeleteShader(fragmentShader);
			// Either of them. Don't leak shaders.
			glDeleteShader(vertexShader);

			HZ_CORE_ERROR("{0}", infoLog.data());
			HZ_CORE_ASSERT(false, "Fragment shader compilation failure!");
			return;
		}

		// ��ɫ������ɹ������ڽ��������ӵ�һ�������С�
		// ��ȡ�������
		m_RendererID = glCreateProgram();
		GLuint program = m_RendererID;

		// �����ǵ���ɫ�����ӵ����ǵĳ����ϡ�
		glAttachShader(program, vertexShader);
		glAttachShader(program, fragmentShader);

		// �������ǵĳ���
		glLinkProgram(program);

		// ע������Ĳ�ͬ������glGetProgram*������glGetShader*��
		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			// We don't need the program anymore.
			glDeleteProgram(program);

			// Don't leak shaders either.
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			HZ_CORE_ERROR("{0}", infoLog.data());
			HZ_CORE_ASSERT(false, "Shader link failure!");
			return;
		}

		// �ڳɹ����Ӻ�ʼ�շ�����ɫ����
		glDetachShader(program, vertexShader);
		glDetachShader(program, fragmentShader);
	}

	Shader::~Shader()
	{
		glDeleteProgram(m_RendererID);
	}

	void Shader::Bind() const
	{
		glUseProgram(m_RendererID);
	}

	void Shader::Unbind() const
	{
		glUseProgram(0);
	}

}