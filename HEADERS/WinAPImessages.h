#pragma once
#include <windowsx.h>
//#include <Windows.h>
#include "WinAPIwindow.h"
#include "WINAPI_INPUT.h"

//------------------------------------------------------------------
//--------------------OBS�UGA KOMUNIKAT�W WINAPI--------------------
//----klasa obs�uguj�ca komunikaty pochodz�ce z aplikacji WinAPI----
//----------------[mo�e by� u�yta do obs�ugi wej�cia]---------------
//------------------------------------------------------------------

class WinAPImessages:public WINAPI_INPUT{
	WinAPImessages() {}

	static int ChangeWindowSize();									//funkcja pomocnicza u�ywana przy zmianie trybu wy�wietlania [pe�noekranowy/okienkowy]

	static void WriteTimeMeasurmentstoFile();

public:
	//g�owna funkcja przetwarzaj�ca komunikaty WinAPI
	static LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
};