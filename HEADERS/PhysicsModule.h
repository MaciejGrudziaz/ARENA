#pragma once
#include "PhysicsModuleConst.h"
#include "TIMER.h"
#include "PlayerInput.h"
#include "BotsActions.h"
#include "GamePhysics.h"
#include "AdditionalPhysics.h"
#include "BulletCollision.h"

//------------------------------------------------------------------------------------------------------
//------------------------------KLASA ODPOWIDAJĄCA ZA WYKONANIE FIZYKI GRY------------------------------
//------------------------------------------------------------------------------------------------------

class PhysicsModule {
	PhysicsModule() {}
	PhysicsModule(const PhysicsModule& module) {}
	PhysicsModule& operator=(const PhysicsModule& module) {}

	static double lastFrameTime;																		//czas wykonania ostatniej klatki gry
	static double frameResidue;																			//'pozostałość' z ostatniej klatki gry

	static void UpdateCharacters();																		//aktualizacja stanu postaci świata gry

public:

	static void ProcessActionsAndPhysics();																//wykonanie wszystkich akcji i obliczeń fizyki

	static void ModelsRegistration();																	//rejestracja dodatkowych modeli fizyki
};