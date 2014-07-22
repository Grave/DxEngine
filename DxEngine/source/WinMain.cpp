////////////////////////////////////////////////////////////////////////////////
// Filename: main.cpp
////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "SystemClass.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow)
{
	SystemClass system;

	// Initialize and run the system object.
	bool result = system.Initialize();
	if (result)
	{
		system.Run();
	}

	// Shutdown the system object.
	system.Shutdown();

	return 0;
}
