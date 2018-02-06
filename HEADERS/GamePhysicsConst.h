#pragma once

//---------------------------------------------------------------------------------------------------------------------
//------------------------------KLASA SINGLETONOWA OPISUJ�CA DODATKOWE ZMIENNE �WIATA GRY------------------------------
//---------------------------------------------------[klasa testowa]---------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------

class GamePhysicsConst {
	GamePhysicsConst();
	GamePhysicsConst(const GamePhysicsConst& obj) {}
	GamePhysicsConst& operator=(const GamePhysicsConst& obj) {}

	static GamePhysicsConst* instance;																	//instancja klasy

	double G;																							//przyspieszenie grawitacyjne [si�a ci��enia]

public:

	static GamePhysicsConst* GetInstance();																//pobranie instancji klasy

	//funkcje pobieraj�ce sk�adowe klasy
	double GetG() { return G; }																			

	//funkcje ustawiaj�ce warto�ci dla sk�adowych klasy
	void SetG(double _G) { G = _G; }
};