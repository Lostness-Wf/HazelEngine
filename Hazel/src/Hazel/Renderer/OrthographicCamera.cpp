#include "hzpch.h"
#include "Hazel/Renderer/OrthographicCamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Hazel {

	/*glm::ortho ��������һ������ͶӰ��������ʾ��������Ļ�ϵ�ƽ��ͶӰ������ͶӰ�����˶�����Դ�С��
	����������������ľ��롣��ͨ������ 2D ͼ�λ� 3D ͼ�Σ�������ȸ�֪����Ҫ�����ɵľ���ָ������׶��ӳ�䵽��һ���豸���꣬
	�䷶Χ����������ά���϶��� - 1 �� 1�������˷�Χ�Ķ��󽫱����ò��Ҳ�������Ļ�Ͽɼ���*/
	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
		: m_ProjectionMatrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)), m_ViewMatrix(1.0f)
	{
		HZ_PROFILE_FUNCTION();

		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void OrthographicCamera::SetProjection(float left, float right, float bottom, float top)
	{
		HZ_PROFILE_FUNCTION();

		m_ProjectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void OrthographicCamera::RecalculateViewMatrix()
	{
		HZ_PROFILE_FUNCTION();

		/*ͶӰ��������������ά�ռ��еĵ�ӳ�䵽��ά��Ļ�ϵľ������������ǽ��ռ��е�ÿ����������ӹ۲�ռ䣨eye space �� view space��
		�任���ü����꣨clip coordinate�����ڲü��ռ䣬clip space��1��ͶӰ������������Ҫ���ͣ�����ͶӰ��͸��ͶӰ��
		����ͶӰ�������׶����һ������׶��һ���֣����н�ƽ��Ϊ z = n��Զƽ��Ϊ z = f��
		����Ҫ�������׶��ת����һ��������[-1, 1][-1, 1][-1, 1] �У������Ȱ�Զƽ��ѹ��������׶��ѹ����һ�������壬
		Ȼ����ͨ���ڶ����е�����ͶӰ����Ϳ��Ա任����������2��͸��ͶӰ������ʹ��������С�׳����ԭ��
		��ΪС�׳�����Լ򵥣�ͬʱ�ֿ����ֽ���ԶС��͸��Ч�����ڼ������Ҳ�����ڳ���䰵�������
		��������Ҳ���������Ӿ�ϵͳһ����Ϊ�ط�����1����֮��ͶӰ����ͨ������ƽ�� x, y, z ���꣬
		�������ɹ۲�ռ�����ϵ�任�����ÿռ�����ϵ�������۲�ռ����׶��ͱ任���˼��ÿռ�������塣
		�Ƚ��м��ã���ͶӰ���Լ���������ȾЧ�ʡ�*/
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) *
		glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0, 0, 1));

		/*�˺���������Ϊ�������ݵľ�������������������������Ļ�������������죩�ģ��򷵻ؾ����е�ֵδ���塣
		����������������ģ���ô��������ʽΪ�㣬����ζ����û�����������������£�glm::inverse �������صľ����е�ֵ��δ�����1��
		������������죩�ľ�����ָ���������ܴ�ľ�����������һ������������������ֵ�������ȶ��Ե�ָ�ꡣ
		������Խ�󣬾�������ֵ������Խ���ȶ�����������������ܴ�ʱ����ʹ��������ֻ��΢С�ı仯��
		������Ҳ���ܷ����ܴ�ı仯����ˣ�����������������죩�ľ���ʹ�� glm::inverse �����������������ܻ������׼ȷ�Ľ����*/
		m_ViewMatrix = glm::inverse(transform);
		/*��δ��봴����һ���任���󣬱�ʾһ�������ƽ�ƺ���ת�����ȣ���ʹ�� glm::translate ��������һ��ƽ�ƾ���
		���������� m_Position ����ƽ�ơ�Ȼ����ʹ�� glm::rotate ��������һ����ת����
		�������� z ����ת m_Rotation �ȡ�������������˵õ����յı任���󡣽������������������ͼ�������ͼͶӰ����
		��ͼ�����Ǳ任����������������������ϵ�еĵ�任���������ϵ�С���ͼͶӰ������ͶӰ�������ͼ����ĳ˻���
		������������ϵ�еĵ�任���ü��ռ��С�*/
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

}