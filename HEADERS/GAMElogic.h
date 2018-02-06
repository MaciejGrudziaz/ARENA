#pragma once
#include "GAMEINPUT.h"
#include "Camera.h"
#include "GameObjects.h"
#include "TIMER.h"
#include "LOGFILE.h"
#include "CONSOLE.h"
#include "WeaponDatabase.h"
#include "CharacterRegister.h"

#include "PhysicsModule.h"
#include "GameGraphics.h"

//---------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------G��WNA LOGIKA GRY--------------------------------------------------
//--------------------------------------klasa odpowiadaj�ca za g��wn� logik� gry---------------------------------------
//-----w klasie tej definiuje si� mapy [obiekty statyczne], postacie [obiekty dynamiczne], kamer� oraz o�wietlenie-----
//---------------------------------------------------------------------------------------------------------------------

class GAMElogic {
	GAMElogic();

	static void InitilizeCamera();
	static void InitializeOpenGLProperties();						//inicjalizacja podstawowych w�a�ciwo�ci okna OpenGL
	static void InitializeLights();									//inicjalizacja �r�de� �wiat�a
	static void InitializeMaterials();								//inicjalizacja materia��w [wersja prototypowa]
	static void InitializePlayer();									//inicjalizacja postaci gracza [klasa Player]
	static void InitializeBots();									//inicjalizacja bot�w
	static void InitializeCharacters();								//inicjalizacja postaci [klasa Character]
	static void InitializeMaps();									//inicjalizacja map [klasa Map]
	static void InitilizeLogFiles();								//inicjalizacja plik�w log�w
	static void InitilizeTimers();									//inicjalizacja timer�w

	static void AddNewBot(const Vector& position, const Vector& orientation);

public:
	static void InitializeGameLogic();								//inicjalziacja logiki gry

	static void RefreshGameLogicInitialization();					//ponowna inicjalizacja logiki gry [wykonywana w razie 'zniszczenia' okna gry]

	static void ProccessFrame();									//przetworzenie pojedynczej klatki gry

};