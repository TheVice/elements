
#include "LightScatteredOccludingDemo.h"
#include "LightScatteredOccludingUi.h"
#include <RenderingGame.h>
#include <ClearBackground.h>

#ifdef WIN32
#if defined(DEBUG) || defined(_DEBUG)
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#endif
#include <tchar.h>
#else
#include <iostream>
#endif

#ifndef WIN32
int main(int argc, char** argv)
{
	(void)argc;
	(void)argv;
#else
int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	(void)hInstance;
	(void)hPrevInstance;
	(void)lpCmdLine;
	(void)nCmdShow;
#if defined(DEBUG) || defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
#endif
	auto game =
		std::make_unique<Library::RenderingGame>("LightScatteredOccluding [Sources experiments/light/occluding]");
	game->addComponent<Library::ClearBackground>();
	game->addService<Rendering::LightScatteredOccludingUi>("assets/settings/experiments/light/occluding.xml");
	game->addComponent<Rendering::LightScatteredOccludingDemo>();

	try
	{
		game->Run();
	}
	catch (const std::runtime_error& aExc)
	{
#ifndef WIN32
		std::cerr << aExc.what() << std::endl;
#else
		MessageBoxA(game->GetWindowHandle(), aExc.what(),
					game->GetWindowTitle().c_str(), MB_ABORTRETRYIGNORE);
#endif
	}

	return 0;
}