#pragma once
#include "WinAPIwindow.h"
#include "GUI.h"

//------------------------------------------------------------------------------------------
//--------------------------------PRZETWARZANIE GRAFIKI GRY---------------------------------
//------------------------------klasa obsługująca grafikę gry:------------------------------
//----------------------------------WYŚWIETLANIE MODELI 3D----------------------------------
//------------------------------------USTAWIENIA KAMERY-------------------------------------
//------------------------------------------------------------------------------------------

class GameGraphics {
	GameGraphics(){}												//prywatny konstruktor domyślny - singleton

	static void DrawMaps();											//rysowanie wszystkich obiektów klasy Map

	static void DrawCharacters();									//rysowanie wszystkich obiektów klasy Character

	static void DrawPlayers();										//rysowanie wszystkich obiektów klasy Player

	static void DrawBots();

	static void SetCameraPosition();								//ustalenie odpowiedniej pozycji

	static void SetCameraOrientation();								//ustalenie odpowiedniej orientacji kamery

	static void SetCamera();										//wszystkie ustawienia kamery

	static void ShowConsoleOutput();								//wyświetlenie danych wyjściowych z 'konsoli'

	static void ShowGUI();

public:

	static void ProccessGraphics();									//przetwarzanie grafiki
};