#include <Hazel.h>
#include <Hazel/Core/EntryPoint.h>

#include "EditorLayer.h"

namespace Hazel {

	class HazelEditor : public Application
	{
	public:
		HazelEditor(ApplicationCommandLineArgs args)
			: Application("Hazel Editor", args)
		{
			PushLayer(new EditorLayer());
		}

		~HazelEditor()
		{
		}
	};

	Application* CreateApplication(ApplicationCommandLineArgs args)
	{
		return new HazelEditor(args);
	}

}