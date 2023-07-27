#include "hzpch.h"
#include "Application.h"

#include "Events/ApplicationEvent.h"
#include "Log.h"

namespace Hazel {

	Hazel::Application::Application()
	{

	}

	Hazel::Application::~Application()
	{

	}

	void Application::Run()
	{
		//Test
		WindowResizeEvent e(1280, 1280);
		HZ_TRACE(e);

		while (true);
	}

}