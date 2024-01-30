#include "hzpch.h"
#include "Hazel/Renderer/OrthographicCamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Hazel {

	/*glm::ortho 函数创建一个正交投影矩阵，它表示对象在屏幕上的平行投影。这种投影保留了对象相对大小，
	而不管它们与相机的距离。它通常用于 2D 图形或 3D 图形，其中深度感知不重要。生成的矩阵将指定的视锥体映射到归一化设备坐标，
	其范围在所有三个维度上都是 - 1 到 1。超出此范围的对象将被剪裁并且不会在屏幕上可见。*/
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

		/*投影矩阵是用来将三维空间中的点映射到二维屏幕上的矩阵。它的作用是将空间中的每个顶点坐标从观察空间（eye space 或 view space）
		变换到裁剪坐标（clip coordinate，属于裁剪空间，clip space）1。投影矩阵有两种主要类型：正交投影和透视投影。
		正交投影矩阵的视锥体是一个四棱锥的一部分，其中近平面为 z = n，远平面为 z = f。
		我们要把这个视锥体转换到一个正方体[-1, 1][-1, 1][-1, 1] 中，可以先把远平面压缩，把视锥体压缩成一个长方体，
		然后再通过第二步中的正交投影矩阵就可以变换到正方体中2。透视投影矩阵则使用了类似小孔成像的原理，
		因为小孔成像相对简单，同时又可体现近大远小的透视效果，在计算机中也不存在成像变暗的情况，
		倒立的像也可像人类视觉系统一样人为地反过来1。总之，投影矩阵通过缩放平移 x, y, z 坐标，
		将坐标由观察空间坐标系变换到剪裁空间坐标系。这样观察空间的视锥体就变换成了剪裁空间的立方体。
		先进行剪裁，再投影可以极大地提高渲染效率。*/
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) *
		glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0, 0, 1));

		/*此函数返回作为参数传递的矩阵的逆矩阵。如果输入矩阵是奇异的或条件差（近乎奇异）的，则返回矩阵中的值未定义。
		如果输入矩阵是奇异的，那么它的行列式为零，这意味着它没有逆矩阵。在这种情况下，glm::inverse 函数返回的矩阵中的值是未定义的1。
		条件差（近乎奇异）的矩阵是指其条件数很大的矩阵。条件数是一种用来衡量矩阵在数值计算中稳定性的指标。
		条件数越大，矩阵在数值计算中越不稳定。当矩阵的条件数很大时，即使输入数据只有微小的变化，
		计算结果也可能发生很大的变化。因此，对于条件差（近乎奇异）的矩阵，使用 glm::inverse 函数计算其逆矩阵可能会产生不准确的结果。*/
		m_ViewMatrix = glm::inverse(transform);
		/*这段代码创建了一个变换矩阵，表示一个物体的平移和旋转。首先，它使用 glm::translate 函数创建一个平移矩阵，
		将物体沿着 m_Position 向量平移。然后，它使用 glm::rotate 函数创建一个旋转矩阵，
		将物体绕 z 轴旋转 m_Rotation 度。这两个矩阵相乘得到最终的变换矩阵。接下来，代码计算了视图矩阵和视图投影矩阵。
		视图矩阵是变换矩阵的逆矩阵，它将世界坐标系中的点变换到相机坐标系中。视图投影矩阵是投影矩阵和视图矩阵的乘积，
		它将世界坐标系中的点变换到裁剪空间中。*/
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

}