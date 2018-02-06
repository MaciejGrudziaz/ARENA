#pragma once
#include <memory>
#include "Character.h"
#include "Action.h"
#include "Quaternion.h"
#include "TIMER.h"
#include "Camera.h"
#include "LOGFILE.h"
#include "PhysicsModuleConst.h"
#include "GamePhysicsConst.h"

//-------------------------------------------------------------------------------------
//------------------------------KLASA POSTACI DYNAMICZNEJ------------------------------
//----------------------------------[klasa wirtualna]----------------------------------
//-------------------------------------------------------------------------------------

typedef std::shared_ptr<ACTION> ActionPtr;

class DynamicCharacter:public Character{
protected:
	double speed;																				//pr�dko�� przemieszczenia postaci
	double turnSensitivity;																		//czu�o�� obrotu i rozgl�dania si� postaci	
	//double G;																					//warto�� przyspieszenia ziemskiego dla postaci
	double weight;
	double jumpStrength;																		//warto�� si�y wyskoku

	double lookAngle;																			//k�t 'widzenia' postaci [odchylenie kamery wzd�u� osi 'x' uk�ady lokalnego modelu]

	std::vector<ActionPtr> actions;																//wektor przechowuj�cy wszystkie akcje kt�re maj� zosta� wykonane przez posta�

public:
	//konstruktory
	DynamicCharacter(const std::string& filename);
	DynamicCharacter(const std::string& filename, const std::string& Name, const Vector& Position, const Vector& Orientation);

	void SetDefaultValues();																	//ustawienie domy�lnych warto�ci dla sk�adowych klasy

	void AddAction(ACTION& action);																//dodanie akcji

	bool ActionsAvailable();																	//sprawdzenie czy w wekotrze 'actions' znajduj� si� akcje do wykonania

	bool CheckAirAction();																		//sprawdzenie czy istnieje akcja z subklasy 'AIR'

	bool RemoveAirAction();																		//usuni�cie istniej�cej akcji z subklasy 'AIR'

	void PerformAction(ActionPtr Action);														//funkcja wykonywuj�ca dan� akcj� 'Action' postaci
	virtual void PerformAdditionalAction(ActionPtr Action) = 0;
	void PerformAllActions();																	//wykonanie wszystkich akcji z wekotra 'actions' postaci

	void UpdateTransformMatrix();																//aktualizacja macierzy przekszta�ce� postaci

	void AdjustMoveAction(Vector k);															//dostosowanie akcji przemieszczenia

	void UpdatePosition();																		//aktualizacja pozycji
	void UpdateOrientation();																	//aktualizacja orientacji

	void Update();

	//pobranie warto�ci sk�adowych klasy
	double GetSpeed() { return speed; }															//pobranie warto�ci pr�dko�ci postaci gracza
	double GetTurnSensitivity() { return turnSensitivity; }										//pobranie warto�ci czu�o�ci obrotu postaci gracza
	double GetWeight() { return weight; }
	double GetJumpStrength() { return jumpStrength; }
	//IdxPair GetSectorIdx() { return sectorIdx; }
	double GetLookAngle() { return lookAngle; }

	//ustwienie odpowiednich warto�ci sk�adowych klasy
	void SetSpeed(double Speed) { speed = Speed; }												//ustawienie warto�ci pr�dko�ci postaci gracza
	void SetTurnSensitivity(double Sensitivity) { turnSensitivity = Sensitivity; }				//ustawienie warto�ci czu�o�ci obrotu gracza
	void SetWeight(double _weight) { weight=_weight; }
	void SetJumpStrength(double JumpStrength) { jumpStrength = JumpStrength; }
	void SetSectorIdx(const IdxPair& newIdx) { sectorIdx = newIdx; }
};