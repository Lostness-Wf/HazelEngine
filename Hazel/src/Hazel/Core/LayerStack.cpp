#include "hzpch.h"
#include "Hazel/Core/LayerStack.h"

namespace Hazel {

	LayerStack::~LayerStack()
	{
		for (Layer* layer : m_Layers)
		{
			layer->OnDetach();
			delete layer;
		}
	}

	//push�Ĳ�λ��ջ��overlay������棬��ͨlayer��������
	void LayerStack::PushLayer(Layer* layer)
	{
		/*����push��insert��Ա����ʱ�����ǽ�Ԫ�����͵Ķ��󴫵ݸ����ǣ���Щ���󱻿����������С�
		����һ��emplace��Ա����ʱ�����ǽ��������ݸ�Ԫ�����͵Ĺ��캯����
		emplace��Աʹ����Щ����������������ڴ�ռ���ֱ�ӹ���Ԫ�أ�������ʡȥ�˿����Ĺ��̡�*/
		m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, layer);
		m_LayerInsertIndex++;
	}

	//push�Ĳ�λ��ջ����Ҳ���������Ⱦ�Ĳ�
	void LayerStack::PushOverlay(Layer* overlay)
	{
		m_Layers.emplace_back(overlay);
	}

	//�����Ĳ㲻������
	void LayerStack::PopLayer(Layer* layer)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
		if (it != m_Layers.end())
		{
			layer->OnDetach();
			m_Layers.erase(it);
			m_LayerInsertIndex--;
		}
	}

	void LayerStack::PopOverlay(Layer* overlay)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.end(), overlay);
		if (it != m_Layers.end())
		{
			overlay->OnDetach();
			m_Layers.erase(it);
		}
	}

}