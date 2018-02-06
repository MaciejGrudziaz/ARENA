#pragma once
#include <vector>
#include "GAMEINPUT.h"

const int TerminalReadDelayVal = 150000;							//op�nienie pomi�dzy wczytwaniem kolejnych znak�w z terminala [150 ms]

class PlayerInput {
	PlayerInput() {}

	static std::vector<int> playerKeyboardInputs;					//wekotr przechowuj�cy sygna�y wej�ciowe z kalwiatury u�ywane do sterowania postaci� gracza

	static std::vector<int> playerMouseInputs;						//wektor przechowuj�cy sygna�y wej�ciowe z myszy u�ywane do sterowania postaci� gracza

	static unsigned long delay;										//czas trwania aplikacji
	//tablice przechowuj�ce cza w kt�rym zosta� wci�ni�ty dany klawisz
	static unsigned long terminalDelayChar[25];						
	static unsigned long terminalDelayNum[2];
	static unsigned long terminalDelaySpecial[4];

	static void InitializePlayerKeyboardInputs();					//inicjalizacja wekotra sygna��w wej�ciowych z klawiatury
	static bool CheckPlayerKeyboardInputsVector(int val);			//sprawdzenie czy dany sygna� wejsciowy ['key'] zosta� ju� dodany do wektora sygna��w wej�ciowych dla postaci gracza
	static void CheckAllKeyboardInputs();							//sprawdzenie wszystkich sygna��w wej�ciowych z klawiatury umieszczonych w wekotrze 'playerKeyboardInputs'

	static void InitilizePlayerMouseInputs();						//inicjalizacja wektora sygna��w wej�ciowych z myszy
	static bool CheckPlayerMouseInputsVector(int val);				//sprawdzenie czy dany sygna� wejsciowy ['key'] zosta� ju� dodany do wektora sygna��w wej�ciowych dla postaci gracza
	static bool CheckMouseInput(int val);							//sprawdzenie czy akcja opisana sygna�em wej�ciowym 'val' mia�a miejsce
	static int GetMouseInputParam(int val);							//zwr�cenie parametru przesuniecia myszy dla sygna�u wej�ciowego 'val'
	static void CheckAllMouseInputs();								//sprawdzenie wszystkich sygna��w wej�ciowych z myszy umieszczonych w wektorze 'playerMouseInputs'

	static void CheckConsoleInput();								//sprawdzenie sygna��w wej�ciowych w terminalu konsoli

public:

	static void InitializePlayerInputs();							//inicjalizacja wszystkich sygna��w wej�ciowych [mysz + klawiatura]

	static void ProccessInput();									//przetwarzanie sygna��w wej�ciowych
};