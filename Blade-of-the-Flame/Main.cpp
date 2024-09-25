// ---------------------------------------------------------------------------
// includes

#include <crtdbg.h> // To check for memory leaks
#include "AEEngine.h"

#include "Utils/Utils.h"
#include "Manager/GameStateManager.h"
#include "State/GameState.h"
#include "State/SampleSave.h"
#include "State/MainMenu.h"
#include "State/GameClear.h"
#include "State/OpeningLogos.h"
#include "State/BossSample/BossSampleSave.h"

namespace Manager
{
	extern GameStateManager& gsMgr;
}

// ---------------------------------------------------------------------------
// main

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(307);

	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);


	int gGameRunning = 1;

	// Initialization of your own variables go here

	// Using custom window procedure
	s32 showConsole = 0;
#ifdef _DEBUG
	showConsole = 1;
#endif
	AESysInit(hInstance, nCmdShow, windowWidth, windowHeight, showConsole, 60, true, NULL);
	//AESysSetFullScreen(1);
	
	// Changing the window title
	AESysSetWindowTitle("Blade of the Flame");

	// reset the system modules
	AESysReset();

	//GameState* gameState = new GameState();
	//SampleSave* sampleSave = new SampleSave();
	//MainMenu* mainMenu = new MainMenu();
	OpeningLogos* opening = new OpeningLogos();
	//BossSampleSave bossSample;

	Manager::gsMgr.ChangeState(opening);

	// Game Loop
	while (Manager::gsMgr.ShouldExit() == false && gGameRunning)
	{
		AEFrameRateControllerReset();

		// Informing the system about the loop's start
		AESysFrameStart();

		Manager::gsMgr.Update();

		// Informing the system about the loop's end
		AESysFrameEnd();

		// check if forcing the application to quit
		if (AEInputCheckTriggered(AEVK_ESCAPE) || 0 == AESysDoesWindowExist())
			gGameRunning = 0;
	}

	Manager::gsMgr.Exit();

	// free the system
	AESysExit();

}