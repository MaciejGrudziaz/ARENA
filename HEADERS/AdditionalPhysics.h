#pragma once
#include <map>
#include "PhysicsModel.h"

//-------------------------------------------------------------------------------------------------------------
//------------------------------KLASA GRUPUJĄCA WSZYSTKIE DODATKOWE MODELE FIZYKI------------------------------
//-------------------------------------------------------------------------------------------------------------

class AdditionalPhysics {
	static std::map<int,PhysicsModel*> models;													//mapa przechowująca dodatkowe modele fizyki

public:

	static void ProcessAllModels();																//przetworzenie wszystkich zarejestrowanych modeli

	static void RegisterModel(PhysicsModel* newModel,int priority);								//rejestracja nowego modelu fizyki
};