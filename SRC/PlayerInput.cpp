#include "PlayerInput.h"

//inicjalizacja obiekt�w statycznych klasy
std::vector<int> PlayerInput::playerKeyboardInputs;
std::vector<int> PlayerInput::playerMouseInputs;
unsigned long PlayerInput::terminalDelayChar[25] = { 0 };
unsigned long PlayerInput::terminalDelayNum[2]={ 0 };
unsigned long PlayerInput::terminalDelaySpecial[4] = { 0 };
unsigned long PlayerInput::delay = TerminalReadDelayVal;

//inicjalizacja wszystkich sygna��w wej�ciowych [mysz + klawiatura]
void PlayerInput::InitializePlayerInputs() {
	InitializePlayerKeyboardInputs();												//inicjalizacja sygna��w wej�ciowych z klawiatury
	InitilizePlayerMouseInputs();													//inicjalizacja sygna��w wej�ciowych z myszy
}

//przetwarzanie sygna��w wej�ciowych
void PlayerInput::ProccessInput() {
	GAMEINPUT::UpdateInputSystem();													//aktualizacja sygna��w z wej�cia

	if (!CONSOLE::GetTerminalStatus()) {
		CheckAllKeyboardInputs();														//sprawdzenie wszystkich sygna��w wej�ciowych z klawiatury umieszczonych w wektorze 'playerKeyboardInputs'

		CheckAllMouseInputs();															//sprawdzenie wszystkich sygna��w wej�ciowych z myszy umieszczonych w wektorze 'playerMouseInputs'
	}
	else CheckConsoleInput();
}

//inicjalizacja sygna��w wej�ciowych z klawiatury dla postaci sterowanej przez gracza
void PlayerInput::InitializePlayerKeyboardInputs() {
	for (unsigned int i = 0; i < GameObjects::players.size(); i++) {				//sprawdzenie wszystkich postaci z wektora postaci
		//pobranie wekotra relacji akcji i sygna��w wej�ciowych dla danej postaci
		std::vector<ACTION_INPUT> playerActionVec = GameObjects::players[i].GetActionKeyboardRelations();
		unsigned int n = playerActionVec.size();
		for (unsigned int j = 0; j<n; j++) {										//sprwadzenie wszystkich sygna��w wej�ciowych zwekotra relacji akcja - wej�cie
			int val = playerActionVec[j].input;										//pobranie warto�ci sygna�u wej�ciowego z wektora realcji akcja - wej�cie
			if (!CheckPlayerKeyboardInputsVector(val))								//je�li dany sygna� wej�ciowy nie zosta� jeszcze dodany do wektora sygna��w wej�ciowych dla postaci
				playerKeyboardInputs.push_back(val);								//dodaj sygna� do wektora
		}
	}
}

//sprawdzenie czy dany sygna� ['key'] ZANJDUJE SI� w wektorze sygna��w wej�ciowych z klawaitury
bool PlayerInput::CheckPlayerKeyboardInputsVector(int val) {
	for (unsigned int i = 0; i < playerKeyboardInputs.size(); i++) {
		if (playerKeyboardInputs[i] == val) return true;							//je�li TAK zwr�� TRUE
	}
	return false;																	//w przciwnym wypadku - FALSE
}

//sprwadzenie wszystkich sygna��w wej�ciowych z klawiatury dodanych do wektora 'playerKeyboardInputs'
void PlayerInput::CheckAllKeyboardInputs() {
	for (unsigned int i = 0; i < playerKeyboardInputs.size(); i++) {				//sprawdzenie wszystkich element� wektora 'playerKeyboardInputs'		
		int input = playerKeyboardInputs[i];										//pobranie sygna�u wej�ciowego
		if (GAMEINPUT::KeyDown(input)) {											//jesli sygna� jest aktywny [dany przycisk zosta� wci�ni�ty]
			unsigned int n = GameObjects::players.size();							
			for (unsigned j = 0; j < n; j++) {										//przejrzenie wszystkich dostepnych postaci gracza
				if (GameObjects::players[j].IsEnabled() &&
					GameObjects::players[j].CheckKeyboardInputVal(input)) {			//je�li posta� jest 'odblokowana' i obs�uguje ona dany sygna� wej�ciowy
					GameObjects::players[j].AddKeyboardAction(input);				//dodaj akcj� powi�zan� z tym sygna�em do wekotra akcji postaci gracza
				}
			}
		}
	}
}

//inicjalizacja sygna��w wej�ciowych z myszy dla postaci sterowanej przez gracza
void PlayerInput::InitilizePlayerMouseInputs() {
	for (unsigned int i = 0; i < GameObjects::players.size(); i++) {				//sprawdzenie wszystkich postaci z wektora postaci
		//pobranie wekotra relacji akcji i sygna��w wej�ciowych dla danej postaci
		std::vector<ACTION_INPUT> playerActionVec = GameObjects::players[i].GetActionMouseRelations();
		unsigned int n = playerActionVec.size();
		for (unsigned int j = 0; j<n; j++) {										//sprawdzenie wszystkich sygna��w wej�ciowych z wekotra akacja - wej�cie
			int val = playerActionVec[j].input;										//pobranie warto�ci sygna�u wejsciowego z wekotra akcja - wej�cie
			if (!CheckPlayerMouseInputsVector(val))									//je�li dany sygna� wej�ciowy nie zosta� jeszcze dodany do wektora sygna��w wej�ciowych z myszy dla postaci
				playerMouseInputs.push_back(val);									//dodaj sygna� wej�ciwoy do wektora
		}
	}
}

//sprawdzenie czy dany sygna� ['val'] znajduje si� w wekotrze sygna��w wej�ciowych z myszy
bool PlayerInput::CheckPlayerMouseInputsVector(int val) {
	for (unsigned int i = 0; i < playerMouseInputs.size(); i++) {
		if (playerMouseInputs[i] == val) return true;								//je�li TAK zwr�� TRUE
	}
	return false;																	//w przeciwnym wypadku - FALSE
}

//sprwadzenie czy dany sygna� z myszy ['val'] wydarzy� si�
bool PlayerInput::CheckMouseInput(int val) {
	POSITION mouseMove = GAMEINPUT::GetMouseMove();									//pobranie przesuniecia wzgl�dnego myszy

	switch (val) {
	case INPUTCONST::MOUSE_RIGHT:													//przesuni�cie w PRAWO
		if (mouseMove.x > 0) return true;											//jesli warto�� przesuni�cia w osi x > 0 zwr�� TRUE
		else return false;															//w przeciwnym wypadu - FALSE
		break;

	case INPUTCONST::MOUSE_LEFT:													//przesuni�cie w LEWO
		if (mouseMove.x < 0) return true;											//je�li warto�� przesuni�cia w osi x < 0 zwr�� TRUE
		else return false;															//w przeciwnym wypadku - FALSE
		break;

	case INPUTCONST::MOUSE_UP:														//przesuni�cie do G�RY				
		if (mouseMove.y > 0) return true;											//jesli warto�� przesuni�cia w osi y > 0 zwr�� TRUE
		else return false;															//w przeciwnym wypadku - FALSE
		break;
		
	case INPUTCONST::MOUSE_DOWN:													//przesuni�cie w Dӣ
		if (mouseMove.y < 0) return true;											//je�li warto�� przesuni�cia w osi y < 0 zwr�� TRUE
		else return false;															//w przeciwnym wypadku - FALSE	
		break;

	case INPUTCONST::MOUSE_LEFT_BUT:
		return GAMEINPUT::MouseButtonDown(INPUTCONST::MOUSE_LEFT_BUT);
		break;

	case INPUTCONST::MOUSE_RIGHT_BUT:
		return GAMEINPUT::MouseButtonDown(INPUTCONST::MOUSE_RIGHT_BUT);
		break;

	default:																		//w ka�dym innym przypadku zwracana jest warto�� FALSE
		return false;
		break;
	}
}

//funkcja zwracja�ca parametr przesuni�cia myszy w danej osi dla danego sygna�u wejsciowego 'val'
int PlayerInput::GetMouseInputParam(int val) {
	POSITION mouseMove = GAMEINPUT::GetMouseMove();									//pobranie przesuni�cia wzgl�dnego myszy

	switch (val) {
	case INPUTCONST::MOUSE_RIGHT:													//przesuniecie w PRAWO
		return mouseMove.x;															//warto�� przesuni�cia myszy w osi X
		break;

	case INPUTCONST::MOUSE_LEFT:													//przesuniecie w LEWO
		return -mouseMove.x;														//warto�� przesuniecia myszy w osi X
		break;

	case INPUTCONST::MOUSE_UP:														//przesuniecie do G�RY
		return mouseMove.y;															//warto�� przesuniecia myszy w osi Y
		break;

	case INPUTCONST::MOUSE_DOWN:													//przesuniecie w Dӣ
		return -mouseMove.y;														//warto�� przesuni�cia myszy w osi Y
		break;

	default:
		return 0;																	//w ka�dym innym przypadku zwracana jest warto�� 0
		break;
	}

}

//sprawdzenie wszystkich sygna��w z myszy zapisanych w wekotrze 'playerMouseInputs'
void PlayerInput::CheckAllMouseInputs() {
	POSITION mouseMove = GAMEINPUT::GetMouseMove();									//pobranie przesuni�cia wzgl�dnego myszy
	for (unsigned int i = 0; i < playerMouseInputs.size(); i++) {				//sprawd� wszystkie sygna�y wej�ciowe z myszy
		int input = playerMouseInputs[i];										//pobranie sygna�u wej�ciowego
		if (CheckMouseInput(input)) {											//sprawdzenie czy dany sygna� wej�ciowy zaszed�
			int param = GetMouseInputParam(input);								//pobranie parametru przesuni�cia myszy
			unsigned int n = GameObjects::players.size();
			for (unsigned int j = 0; j < n; j++) {								//sprawdzenie wekotra postaci sterowanych przez gracza
				if (GameObjects::players[j].IsEnabled() &&
					GameObjects::players[j].CheckMouseInputVal(input)) {		//jesli dana posta� jest 'odblokowana' i dany sygna� wej�ciowy znajduje si� w jej wektorze relacji akcja - wej�cie
					GameObjects::players[j].AddMouseAction(input, param);		//dodaj akcj� powi�zan� z danym sygna�em wej�ciwoym do wekotra akcji
				}
			}
		}
	}
}

//sprawdzenie sygna��w wej�ciowych w terminalu konsoli
void PlayerInput::CheckConsoleInput() {
	delay += static_cast<unsigned long>(PHYSICSMODULE::targetFrameTime);		//dodanie czasu trwania jednej klatki do licznika op�nienia wczytywania znak�w							

	//wczytywanie znak�w alfabetycznych
	if (GAMEINPUT::KeyDown(INPUTCONST::A))
		if(delay-terminalDelayChar[0] > TerminalReadDelayVal) {
		CONSOLE::GetTerminalInput('a');  terminalDelayChar[0] = delay;
	}
	if (GAMEINPUT::KeyDown(INPUTCONST::B))
		if(delay-terminalDelayChar[1] > TerminalReadDelayVal) {
		CONSOLE::GetTerminalInput('b'); terminalDelayChar[1] = delay;
	}
	if (GAMEINPUT::KeyDown(INPUTCONST::C))
		if(delay-terminalDelayChar[2] > TerminalReadDelayVal) {
		CONSOLE::GetTerminalInput('c'); terminalDelayChar[2] = delay;
	}
	if (GAMEINPUT::KeyDown(INPUTCONST::D))
		if(delay - terminalDelayChar[3] > TerminalReadDelayVal) {
		CONSOLE::GetTerminalInput('d'); terminalDelayChar[3] = delay;
	}
	if (GAMEINPUT::KeyDown(INPUTCONST::E))
		if(delay - terminalDelayChar[3] > TerminalReadDelayVal) {
		CONSOLE::GetTerminalInput('e'); terminalDelayChar[3] = delay;
	}
	if (GAMEINPUT::KeyDown(INPUTCONST::F))
		if(delay - terminalDelayChar[4] > TerminalReadDelayVal){
		CONSOLE::GetTerminalInput('f'); terminalDelayChar[4] = delay;
	}
	if (GAMEINPUT::KeyDown(INPUTCONST::G))
		if(delay - terminalDelayChar[5] > TerminalReadDelayVal) {
		CONSOLE::GetTerminalInput('g'); terminalDelayChar[5] = delay;
	}
	if (GAMEINPUT::KeyDown(INPUTCONST::H))
		if(delay - terminalDelayChar[6] > TerminalReadDelayVal) {
		CONSOLE::GetTerminalInput('h'); terminalDelayChar[6] = delay;
	}
	if (GAMEINPUT::KeyDown(INPUTCONST::I))
		if(delay - terminalDelayChar[7] > TerminalReadDelayVal) {
		CONSOLE::GetTerminalInput('i'); terminalDelayChar[7] = delay;
	}
	if (GAMEINPUT::KeyDown(INPUTCONST::J))
		if(delay - terminalDelayChar[8] > TerminalReadDelayVal) {
		CONSOLE::GetTerminalInput('j'); terminalDelayChar[8] = delay;
	}
	if (GAMEINPUT::KeyDown(INPUTCONST::K))
		if(delay - terminalDelayChar[9] > TerminalReadDelayVal) {
		CONSOLE::GetTerminalInput('k'); terminalDelayChar[9] = delay;
	}
	if (GAMEINPUT::KeyDown(INPUTCONST::L))
		if(delay - terminalDelayChar[10] > TerminalReadDelayVal) {
		CONSOLE::GetTerminalInput('l'); terminalDelayChar[10] = delay;
	}
	if (GAMEINPUT::KeyDown(INPUTCONST::M))
		if(delay - terminalDelayChar[11] > TerminalReadDelayVal) {
		CONSOLE::GetTerminalInput('m'); terminalDelayChar[11] = delay;
	}
	if (GAMEINPUT::KeyDown(INPUTCONST::N))
		if(delay - terminalDelayChar[12] > TerminalReadDelayVal) {
		CONSOLE::GetTerminalInput('n'); terminalDelayChar[12] = delay;
	}
	if (GAMEINPUT::KeyDown(INPUTCONST::O))
		if(delay - terminalDelayChar[13] > TerminalReadDelayVal) {
		CONSOLE::GetTerminalInput('o'); terminalDelayChar[13] = delay;
	}
	if (GAMEINPUT::KeyDown(INPUTCONST::P))
		if(delay - terminalDelayChar[14] > TerminalReadDelayVal) {
		CONSOLE::GetTerminalInput('p'); terminalDelayChar[14] = delay;
	}
	if (GAMEINPUT::KeyDown(INPUTCONST::R))
		if(delay - terminalDelayChar[15] > TerminalReadDelayVal) {
		CONSOLE::GetTerminalInput('r'); terminalDelayChar[15] = delay;
	}
	if (GAMEINPUT::KeyDown(INPUTCONST::S))
		if(delay - terminalDelayChar[16] > TerminalReadDelayVal) {
		CONSOLE::GetTerminalInput('s'); terminalDelayChar[16] = delay;
	}
	if (GAMEINPUT::KeyDown(INPUTCONST::T))
		if(delay - terminalDelayChar[17] > TerminalReadDelayVal) {
		CONSOLE::GetTerminalInput('t'); terminalDelayChar[17] = delay;
	}
	if (GAMEINPUT::KeyDown(INPUTCONST::U))
		if(delay - terminalDelayChar[18] > TerminalReadDelayVal) {
		CONSOLE::GetTerminalInput('u'); terminalDelayChar[18] = delay;
	}
	if (GAMEINPUT::KeyDown(INPUTCONST::V))
		if(delay - terminalDelayChar[19] > TerminalReadDelayVal) {
		CONSOLE::GetTerminalInput('v'); terminalDelayChar[19] = delay;
	}
	if (GAMEINPUT::KeyDown(INPUTCONST::W))
		if(delay - terminalDelayChar[20] > TerminalReadDelayVal) {
		CONSOLE::GetTerminalInput('w'); terminalDelayChar[20] = delay;
	}
	if (GAMEINPUT::KeyDown(INPUTCONST::X))
		if(delay - terminalDelayChar[21] > TerminalReadDelayVal) {
		CONSOLE::GetTerminalInput('x'); terminalDelayChar[21] = delay;
	}
	if (GAMEINPUT::KeyDown(INPUTCONST::Y))
		if(delay - terminalDelayChar[22] > TerminalReadDelayVal) {
		CONSOLE::GetTerminalInput('y'); terminalDelayChar[22] = delay;
	}
	if (GAMEINPUT::KeyDown(INPUTCONST::Z))
		if(delay - terminalDelayChar[23] > TerminalReadDelayVal) {
		CONSOLE::GetTerminalInput('z'); terminalDelayChar[23] = delay;
	}

	//wczytywanie cyfr
	if (GAMEINPUT::KeyDown(INPUTCONST::_0))
		if(delay - terminalDelayNum[0] > TerminalReadDelayVal) {
		CONSOLE::GetTerminalInput('0'); terminalDelayNum[0] = delay;
	}
	if (GAMEINPUT::KeyDown(INPUTCONST::_1))
		if(delay - terminalDelayNum[1] > TerminalReadDelayVal) {
		CONSOLE::GetTerminalInput('1'); terminalDelayNum[1] = delay;
	}

	//wczytywanie znak�w specjalnych
	if (GAMEINPUT::KeyDown(INPUTCONST::BACKSPACE))
		if(delay - terminalDelaySpecial[0] > TerminalReadDelayVal) {
		CONSOLE::GetTerminalInput(0x08); terminalDelaySpecial[0] = delay;
	}
	if (GAMEINPUT::KeyDown(INPUTCONST::DECIMAL_POINT))
		if(delay - terminalDelaySpecial[1] > TerminalReadDelayVal) {
		CONSOLE::GetTerminalInput('.'); terminalDelaySpecial[1] = delay;
	}
	if (GAMEINPUT::KeyDown(INPUTCONST::EQUALS))
		if(delay - terminalDelaySpecial[2] > TerminalReadDelayVal) {
		CONSOLE::GetTerminalInput('='); terminalDelaySpecial[2] = delay;
	}
	if (GAMEINPUT::KeyDown(INPUTCONST::ENTER))
		if(delay - terminalDelaySpecial[3] > TerminalReadDelayVal) {
		CONSOLE::GetTerminalInput(0x0A); terminalDelaySpecial[3] = delay;
	}
}