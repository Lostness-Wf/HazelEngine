#pragma once

#if HZ_PLATFORM_WINDOWS

extern Hazel::Application* Hazel::CreatApplication();

int main(int argc, char** argv) {
	//Log
	Hazel::Log::Init();
	HZ_CORE_INFO("Init Log");
	HZ_INFO("Init Log");

	auto app = Hazel::CreatApplication();
	app->Run();
	delete app;
}

#endif // HZ_PLATFROM_WINDOWS
