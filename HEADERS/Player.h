#pragma once
#include <memory>
#include "Character.h"
#include "GAMEINPUT_CONSTANTS.h"
#include "TIMER.h"
#include "LOGFILE.h"
#include "Camera.h"
#include "SpecialMath.h"
#include "Quaternion.h"
#include "Action.h"
#include "DynamicCharacter.h"
#include "Gun.h"

//-------------------------------------------------------------------------------------
//---------------------------------------PLAYER----------------------------------------
//--------------------klasa opisuj�ca posta� sterowan� przez gracza--------------------
//-------------------------------------------------------------------------------------

typedef std::shared_ptr<Weapon> WeaponPtr;

class Player : public DynamicCharacter {														//klasa dziedziczy po obiekcie postaci [elementy niestatyczne w grze]
	std::vector<ACTION_INPUT> action_keyboard_relations;										//wektor przechowuj�cy wszystkie relacje akcja - sygna� wej�ciowy z klawiatury dla danej postaci
	std::vector<ACTION_INPUT> action_mouse_relations;											//wektor przechowuj�cy wszystkie relacje akcja - sygna� wej�ciowy z myszy dla danej postaci

	WeaponPtr weapon;

public:
	//konstruktory
	Player(const std::string& filename);
	Player(const std::string& filename, const std::string& Name, const Vector& Position, const Vector& Orientation);

	void AddWeapon(const std::string& weaponName);												//dodanie broni dla postaci gracza

	void PerformAdditionalAction(ActionPtr Action);												//dodatkowe akcje postaci gracza

	bool CheckKeyboardInputVal(int val);														//sprawdzenie czy dany sygna� wej�ciowy znajduje si� w wektorze relacji akcja - sygna� wej�ciowy z klawiatury
	void AddKeyboardAction(int inputVal);														//dodanie nowej akcji do wektora przypisanej do danego sygna�u wej�ciowego 'inputVal' z klawiatury

	bool CheckMouseInputVal(int val);															//sprawdzenie czy dany sygna� wej�ciowy znajduje si� w wektorze relacji akcja - sygna� wej�ciowy z myszy
	void AddMouseAction(int inputVal,int Param);												//dodanie nowej akcji do wektora przypisanej do danego sygna�u wej�ciowego 'inputVal' z myszy	

	//pobranie wekotra akcja - sygna� wej�ciowy z klawiatury
	std::vector<ACTION_INPUT> GetActionKeyboardRelations() { return action_keyboard_relations; }		

	//pobranie wektora akcja - sygna� wej�ciowy z myszy
	std::vector<ACTION_INPUT> GetActionMouseRelations() { return action_mouse_relations; }

	WeaponPtr GetWeapon() { return weapon; }

	void UpdatePosition();
	void UpdateOrientation();
	void Update();

	void DrawModel();
};
