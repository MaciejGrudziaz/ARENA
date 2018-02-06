#pragma once
#include "DIRECTINPUT.h"
#include "WinAPImessages.h"
#include "Vector.h"

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------GAMEINPUT-----------------------------------------------------------------------------------
//--------------------------------------------------------klasa wysokiego poziomu s�u��ca za system wej�cia dla aplikacji-------------------------------------------------------
//-----------------------------------------zadekalrowane w niej s� funkcje za pomoc� kt�rych u�ytkownik odwo�uje si� do systemu wej�cia-----------------------------------------
//--------------------definiecje tych funkcji s� odwo�aniem do konkretnych funkcji klas ni�szego poziomu pochodz�cych z wybranego API [Direct Input, WinAPI]--------------------
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class GAMEINPUT {
	GAMEINPUT() {}

public:
	static void InitalizeInputSystem();										//inicjalizacja systemu wej�cia

	static void UpdateInputSystem();										//uaktualnienie sygna��w z systemu wej�cia

	static void ShutdownInputSystem();										//zamkni�cie i zwolnienie danego systemu wej�cia

	//---------------------------------------------------------------------------------------------------------------------------------

	static bool KeyDown(int key);											//sprawdzenie czy przycisk dany kodem 'key' jest wci�ni�ty

	static bool KeyUp(int key);												//sprawdzenie czy przycisk dany kodem 'key' jest puszczony

	static bool MouseButtonDown(int key);									//sprawdzenie czy przycisk na myszy dany kodem 'key' jest wci�niety

	static bool MouseButtonUp(int key);										//sprawdzenie czy przycisk na myszy dany kodem 'key' jest puszczony

	static POSITION GetMouseAbsPos();										//pobranie bezwzgl�dnej pozycji kursora myszy na ekranie apliakcji

	static POSITION GetMouseMove();											//pobranie przemieszczenia [pozycji wzgl�dnej] myszy
};