// ---------------------------------------------------------------------------
// includes

#include <crtdbg.h> // To check for memory leaks
#include "AEEngine.h"

#include "Utils/Utils.h"
#include "Manager/GameStateManager.h"
#include "Manager/EventManager.h"
#include "State/GameState.h"
#include "State/SampleSave.h"
#include "State/MainMenu.h"
#include "State/GameClear.h"
// ---------------------------------------------------------------------------
// main

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);


	int gGameRunning = 1;

	// Initialization of your own variables go here

	// Using custom window procedure
	AESysInit(hInstance, nCmdShow, windowWidth, windowHeight, 1, 60, true, NULL);
	
	// Changing the window title
	AESysSetWindowTitle("Blade of the Flame");

	// reset the system modules
	AESysReset();

	GameState gameState;
	SampleSave sampleSave;
	MainMenu mainMenu;

	GameStateManager& gsm = GameStateManager::GetInstance();
	gsm.ChangeState(&sampleSave);

	// Game Loop
	while (gGameRunning)
	{
		// Informing the system about the loop's start
		AESysFrameStart();

		gsm.Update();

		// Informing the system about the loop's end
		AESysFrameEnd();

		// check if forcing the application to quit
		if (AEInputCheckTriggered(AEVK_ESCAPE) || 0 == AESysDoesWindowExist())
			gGameRunning = 0;
	}

	gsm.Exit();

	// free the system
	AESysExit();

}