#pragma once

#include "Hazel/Core/Core.h"

#if HZ_PLATFORM_WINDOWS

extern Hazel::Application* Hazel::CreateApplication();

int main(int argc, char** argv) {
	//Log
	Hazel::Log::Init();
	HZ_CORE_INFO("Init Log");
	HZ_INFO("Init Log");

	auto app = Hazel::CreateApplication();
	app->Run();
	delete app;
}

#endif // HZ_PLATFROM_WINDOWS
