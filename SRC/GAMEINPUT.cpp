#include "GAMEINPUT.h"

//inicajlizacja systemu wej�cia
void GAMEINPUT::InitalizeInputSystem() { 
	//inicajlizacja systemu wej�cia DirectInput
	if (WinAPIwindow::fullscreen) DIRECTINPUT::Initialize();								//je�li apliakcja znajduje si� w trybie pe�noekranowym to wywo��j inicjalizacj� z trybem 'ekskluzywnym'
	else DIRECTINPUT::Initialize(false);													//jesli nie to wy��cz tryb 'ekskluzywny'
	/*TRYB EKSKLUZYWNY:
		tryb w kt�ym nie wida� myszy na ekranie oraz jest ona na wy��czno�� obecnej apliakcji*/
}

//uaktualnienie sygna��w z systemu wej�cia
void GAMEINPUT::UpdateInputSystem() { DIRECTINPUT::Update(); }

//zamkni�cie i zwolnienie danego systemu wej�cia
void GAMEINPUT::ShutdownInputSystem() { DIRECTINPUT::Shutdown(); }

//sprawdzenie czy przycisk dany kodem 'key' jest wci�ni�ty
bool GAMEINPUT::KeyDown(int key) { return(DIRECTINPUT::KeyDown(key)); }

//sprawdzenie czy przycisk dany kodem 'key' jest puszczony
bool GAMEINPUT::KeyUp(int key) { return(DIRECTINPUT::KeyUp(key)); }

//sprawdzenie czy przycisk na myszy dany kodem 'key' jest wci�niety
bool GAMEINPUT::MouseButtonDown(int key) { return(DIRECTINPUT::ButtonDown(key)); }

//sprawdzenie czy przycisk na myszy dany kodem 'key' jest puszczony
bool GAMEINPUT::MouseButtonUp(int key) { return(DIRECTINPUT::ButtonUp(key)); }

//pobranie bezwzgl�dnej pozycji kursora myszy na ekranie apliakcji
POSITION GAMEINPUT::GetMouseAbsPos() { return(WinAPImessages::GetMousePos()); }

//pobranie przemieszczenia [pozycji wzgl�dnej] myszy
POSITION GAMEINPUT::GetMouseMove() {
	POSITION retPos;

	DIRECTINPUT::GetMouseMovement(retPos.x, retPos.y);										//wczytanie warto�ci x i y dla struktury zwracaj�cej warto�� przesuni�cia myszy

	return retPos;
}