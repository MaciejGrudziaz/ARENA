#pragma once
#include "WinAPIwindow.h"
#include "GUI.h"

//------------------------------------------------------------------------------------------
//--------------------------------PRZETWARZANIE GRAFIKI GRY---------------------------------
//------------------------------klasa obs�uguj�ca grafik� gry:------------------------------
//----------------------------------WY�WIETLANIE MODELI 3D----------------------------------
//------------------------------------USTAWIENIA KAMERY-------------------------------------
//------------------------------------------------------------------------------------------

class GameGraphics {
	GameGraphics(){}												//prywatny konstruktor domy�lny - singleton

	static void DrawMaps();											//rysowanie wszystkich obiekt�w klasy Map

	static void DrawCharacters();									//rysowanie wszystkich obiekt�w klasy Character

	static void DrawPlayers();										//rysowanie wszystkich obiekt�w klasy Player

	static void DrawBots();

	static void SetCameraPosition();								//ustalenie odpowiedniej pozycji

	static void SetCameraOrientation();								//ustalenie odpowiedniej orientacji kamery

	static void SetCamera();										//wszystkie ustawienia kamery

	static void ShowConsoleOutput();								//wy�wietlenie danych wyj�ciowych z 'konsoli'

	static void ShowGUI();

public:

	static void ProccessGraphics();									//przetwarzanie grafiki
};