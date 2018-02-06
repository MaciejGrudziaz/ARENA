#include "GamePhysicsConst.h"

GamePhysicsConst* GamePhysicsConst::instance = nullptr;

//pobranie instancji klasy
GamePhysicsConst* GamePhysicsConst::GetInstance() {
	if (instance == nullptr) {																							//je�li nie utworzono jeszcze instancji klasy
		instance = new GamePhysicsConst();																				//utw�rz instancj� klasy
	}

	return instance;																									//zwr�� aktualn� instancj� klasy
}

//konstruktor domy�lny
GamePhysicsConst::GamePhysicsConst() {
	G = 10.0;
}