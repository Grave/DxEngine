////////////////////////////////////////////////////////////////////////////////
// Filename: SystemSlass.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

///
/// Here we define WIN32_LEAN_AND_MEAN. We do this to speed up
///the build process, it reduces the size of the Win32 header 
///files by excluding some of the less used APIs.
///
#define WIN32_LEAN_AND_MEAN

//////////////
// INCLUDES //
//////////////
#include "stdafx.h"
#include <windows.h>

#include "InputClass.h"
#include "GraphicsClass.h"

///
///The definition of the class is fairly simple. We see the Initialize, 
///Shutdown, and Run function that was called in WinMain defined here.
///There are also some private functions that will be called inside those 
///functions. We have also put a MessageHandler function in the class to 
///handle the windows system messages that will get sent to the application
///while it is running. And finally we have some private variables m_Input
///and m_Graphics which will be pointers to the two objects that will handle
///graphics and input.
///
class SystemClass
{
public:
	SystemClass();
	SystemClass(const SystemClass&);
	~SystemClass();

	bool Initialize();
	void Shutdown();
	void Run();

	LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);

private:
	bool Frame();
	void InitializeWindows(int&, int&);
	void ShutdownWindows();

private:
	LPCWSTR m_applicationName;
	HINSTANCE m_hinstance;
	HWND m_hwnd;

	GraphicsClass m_Graphics;
	std::unique_ptr<InputClass> m_Input;
};


///
///The WndProc function and ApplicationHandle pointer are also included
///in this class file so we can re-direct the windows system messaging
///into our MessageHandler function inside the system class.
///

/////////////////////////
// FUNCTION PROTOTYPES //
/////////////////////////
static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);


/////////////
// GLOBALS //
/////////////
static SystemClass* ApplicationHandle = 0;
