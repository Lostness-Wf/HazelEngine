#include "hzpch.h"
#include "LayerStack.h"

namespace Hazel {

	LayerStack::LayerStack()
	{
		
	}

	LayerStack::~LayerStack()
	{
		for (Layer* layer : m_Layers)
			delete layer;
	}

	//push的层位于栈顶overlay层的下面，普通layer的最上面
	void LayerStack::PushLayer(Layer* layer)
	{
		/*调用push或insert成员函数时，我们将元素类型的对象传递给它们，这些对象被拷贝到容器中。
		调用一个emplace成员函数时，则是将参数传递给元素类型的构造函数。
		emplace成员使用这些参数在容器管理的内存空间中直接构造元素，这样就省去了拷贝的过程。*/
		m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, layer);
		m_LayerInsertIndex++;
		layer->OnAttach();
	}

	//push的层位于栈顶，也就是最后渲染的层
	void LayerStack::PushOverlay(Layer* overlay)
	{
		m_Layers.emplace_back(overlay);
		overlay->OnAttach();
	}

	//弹出的层不会销毁
	void LayerStack::PopLayer(Layer* layer)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
		if (it != m_Layers.end())
		{
			m_Layers.erase(it);
			m_LayerInsertIndex--;
			layer->OnDetach();
		}
	}

	void LayerStack::PopOverlay(Layer* overlay)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.end(), overlay);
		if (it != m_Layers.end())
		{
			m_Layers.erase(it);
			overlay->OnDetach();
		}
	}

}