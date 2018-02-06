#pragma once
#include "Vector.h"

//--------------------------------------------------------------------------------------------------------------------
//------------------------------PLIK OPISUJ�CY STRUKTURY DLA AKCJI OBIEKT�W DYNAMICZNYCH------------------------------
//---------------------------------------------[akcje gracza, bot�w itp.]---------------------------------------------
//--------------------------------------------------------------------------------------------------------------------

//typ wyliczeniowy okre�laj�cy akcje wykonywane przez postacie
enum ACTION_NAME {
	MOVE_RIGHT, MOVE_LEFT, MOVE_FORWARD, MOVE_BACKWARD,
	TURN_RIGHT, TURN_LEFT, LOOK_UP, LOOK_DOWN,
	FALL, JUMP,
	SHOOT, RELOAD
};

//typ wyliczeniowy okre�laj�cy kategorie akcji wykonywanych przez posatcie
enum SUB_ACTION_NAME { MOVEMENT, ORIENTATION, AIR, OTHER };

//struktura s�u��ca do definiowania akcji wykonywanych przez posta� gracza
//akcja jest definiowana poprzez jej nazw� okre�lon� poprzez typ wyliczeniowy ACTION_NAME oraz jej kategori� opisana przez SUB_ACTION_NAME
class ACTION {
public:
	ACTION_NAME name;																			//nazwa akcji
	SUB_ACTION_NAME subActionName;																//nazwa kategorii

	//KONSTRUKTORY
	ACTION() {}
	ACTION(ACTION_NAME Name, SUB_ACTION_NAME subAction) {
		name = Name;
		subActionName = subAction;
	}
};

//akcja ruchu
class MOVE_ACTION : public ACTION {
public:
	MOVE_ACTION(ACTION_NAME name) :ACTION(name, MOVEMENT) {}
};

//akcja zmiany orientacji
class LOOK_ACTION : public ACTION {
public:
	double mouseMove;																			//parametr przemieszczenia myszy	

	LOOK_ACTION(ACTION_NAME name,double _mouseMove) :ACTION(name, ORIENTATION), mouseMove(_mouseMove) {}
};

//akcja spadania
class FALL_ACTION : public ACTION {
public:
	Vector position;																			//pozycja podczas rozpocz�cia spadania														
	Vector shift;																				//orientacja podczas rozpocz�cia spadania
	double time;																				//�aczny czas trwania spadania

	FALL_ACTION(Vector& _position, Vector& _shift) : ACTION(FALL, AIR), position(_position), shift(_shift), time(0) {}

	void UpdateTime(double dt) {																//aktualizacja czasu spadania
		time += dt;
	}
};

//akcja skoku
class JUMP_ACTION : public ACTION {
public:
	Vector position;																			//pozycja startowa akcji skoku
	Vector shift;																				//orientacja podczas rozpocz�cia skoku
	double time;																				//��czny czas trwania skoku

	JUMP_ACTION(Vector& _position, Vector& _shift, double jumpStrength) : ACTION(JUMP, AIR), position(_position), shift(_shift), time(0) {
		shift.y = jumpStrength;
	}

	void UpdateTime(double dt) {																//aktualizcja czasu skoku
		time += dt;
	}
};

//struntura ��cz�ca akcje postaci wraz z sygna�em wej�ciowym
struct ACTION_INPUT {
	ACTION_NAME action;																			//nazwa akcji
	SUB_ACTION_NAME subActionName;																//nazwa kategorii akcji
	int input;																					//sygna� wej�ciowy

																								//KONSTRUKTORY
	ACTION_INPUT() {}
	ACTION_INPUT(ACTION_NAME Action, SUB_ACTION_NAME subAction, int Input) {
		action = Action;
		subActionName = subAction;
		input = Input;
	}
};