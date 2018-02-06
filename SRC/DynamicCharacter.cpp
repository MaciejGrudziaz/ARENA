#include "DynamicCharacter.h"

DynamicCharacter::DynamicCharacter(const std::string& filename):Character(filename) {
	SetDefaultValues();
}

DynamicCharacter::DynamicCharacter(const std::string& filename, const std::string& Name, const Vector& Position, const Vector& Orientation):
	Character(filename,Name,Position,Orientation){
	SetDefaultValues();
}

//ustawienie domy�lnych warto�ci dla sk�adowych klasy
void DynamicCharacter::SetDefaultValues() {
	position.y += collisionBox.midPoint.y;
	speed = 1.0;
	turnSensitivity = 1.0;
	previousPosition = position;
	nextPosition = position;
	previousOrientation = orientation;
	weight = 1;
	jumpStrength = 25.0;
	lookAngle = 0.0;
}

//dodanie akcji
void DynamicCharacter::AddAction(ACTION& action) {
	switch (action.subActionName) {
	case AIR:																				//je�li akcja pochodzi z subklasy 'AIR'
		if (action.name == FALL) {															//je�li jest to akcja spadania
			if (!(actions.size() > 0 && actions[0]->subActionName == AIR)) {				//je�li nie ma aktualnie akcji spadania obecnej dla postaci
				ActionPtr ptr(new FALL_ACTION(static_cast<FALL_ACTION&>(action).position, static_cast<FALL_ACTION&>(action).shift));
				actions.push_back(ptr);														//stw�rz tak� akcj� i dodaj j� do wektora akcji

				if (actions.size() > 1) {													//umie�� nowostworzon� akcj� spadania na pocz�tku wektora akcji
					ActionPtr tmp = actions[0];
					actions[0] = actions[actions.size() - 1];
					actions[actions.size() - 1] = tmp;
				}
			}
		}
		break;
	case ORIENTATION: {																		//je�li akcja pochodzi z subklay 'ORIENTATION'
		ActionPtr ptr(new LOOK_ACTION(static_cast<LOOK_ACTION&>(action).name, static_cast<LOOK_ACTION&>(action).mouseMove));
		actions.push_back(ptr);																//wykonaj rzutowanie akcji w g�r� hierarchi i dodaj j� do wektora wszystkich akcji
		}
		break;

	default:																				//domy�lnie
		ActionPtr ptr(new ACTION(action));													//dodaj akcj� do wektora akcji
		actions.push_back(ptr);
		break;
	}
}

//sprawdzenie czy w wekotrze akcji zanjduj� si� akcje do wykonania
bool DynamicCharacter::ActionsAvailable() {
	if (actions.size() > 0) return true;
	else return false;
}

//sprawdzenie czy w wektorze akcji znajduje si� akcja z subklasy 'AIR'
bool DynamicCharacter::CheckAirAction() {
	if (actions.size() > 0) {
		if (actions[0]->subActionName == AIR)
			return true;
		else return false;
	}
	else return false;
}

//usuni�cie, jesli istneije akcji z subklay 'AIR'
bool DynamicCharacter::RemoveAirAction() {
	if (actions.size() > 0) {
		if (actions[0]->subActionName == AIR) {
			actions.erase(actions.begin());
			return true;
		}
		else return false;
	}
	else return false;
}

//wykonanie wszystkich akcji umieszczonych w wektorze
void DynamicCharacter::PerformAllActions() {
	if (actions.size() > 0) {
		unsigned moveCount = 0;
		if (actions.size() >= 2) {																//sprawdzenie czy istniej� wi�cej ni� dwie akcje przemieszczenia do wykonania
			for (ActionPtr ptr : actions) {
				if (ptr->subActionName == MOVEMENT)
					moveCount++;
			}
		}

		double playerSpeed = speed;
		if (moveCount >= 2)																		//je�li tak zmniejsz pr�dko�� postaci o po�ow�
			speed /= 2.0;

		if (actions[0]->subActionName == AIR) {													//je�li istnieje akcja z subklasy 'AIR'
			for (ActionPtr ptr : actions) {
				if (ptr->subActionName != MOVEMENT)												//nie wykonuj akcji zwi�zanych z ruchem
					PerformAction(ptr);
			}
			actions.erase(actions.begin() + 1, actions.end());									//po wykonaniu wszystkich akci usu� je z wektora opr�cz akcji z subklasy 'AIR'
		}
		else {
			for (ActionPtr ptr : actions) {														//je�li nie istnieje akcja z subklasy 'AIR'
				PerformAction(ptr);																//wykonaj wszystkie akcje
			}
			actions.clear();																	//wyczy�� ca�y wektor akcji
		}

		speed = playerSpeed;																	//przywr�� pierwotn� warto�� pr�dko�ci postaci
	}
}

//aktualizacja macierzy przekszta�ce� postaci
void DynamicCharacter::UpdateTransformMatrix() {
	Vector angle(orientation); angle = angle / 360.0 * 2.0 * 3.1415;						//zamiana warto�ci k�t�w obrotu wok� danych osi na radiany
	//wyzanczenie kwaternion�w dla ka�dej osi obrotu
	Quaternion q_x(cos(angle.x / 2.0), Vector(1, 0, 0)*sin(angle.x / 2.0));
	Quaternion q_y(cos(angle.y / 2.0), Vector(0, 1, 0)*sin(angle.y / 2.0));
	Quaternion q_z(cos(angle.z / 2.0), Vector(0, 0, 1)*sin(angle.z / 2.0));
	//z�o�enie wszystkich obrot�w i wyznaczenie kwaternionu orientacji
	Quaternion Q = q_z.CrossProduct(q_y);
	Q.CrossProduct(q_x);

	transform = Q.CreateMatrix();															//wyznacznie macierzy jednorodnej z kwaternionu orientacji

	for (unsigned int i = 0; i < 3; i++)
		transform[i][3] = position[i];														//dodanie do macierzy jednorodnej wektor przesuni�cia
}

//----------------------------------------------------WYKONANIE AKCJI----------------------------------------------------
//---------------------------------------funkcja wykonuj�ca dan� akcj� ['Action']----------------------------------------
//----------wszystkie akcje zdefiniowane w typie wyliczeniowym ACTION_NAME musz� by� zdefiniowane w tej funkcji----------
void DynamicCharacter::PerformAction(ActionPtr Action) {
	double t = PHYSICSMODULE::targetFrameTime /1000000.0;									//predefiniowana sta�a warto�� trwania jednej iteracji symulacji fizycznych
	double angle = orientation.y / 360.0 * 2.0 * 3.1415;									//warto�� k�ta obrotu postaci wok� osi y [w radianach]
																							//2.0 * 3.1415 -> 2 * PI
	double G = GamePhysicsConst::GetInstance()->GetG();
	
	switch (Action->name) {

	case MOVE_RIGHT: {																		//przemieszczenie w prawo
																							//previousPosition = position;
		double s = speed*t;																	//s - warto�� przemieszczenia, speed - pr�dko�� postaci, t/1000000.0 - czas trwania poprzedniej klatki w sek.
		nextPosition.x -= s*cos(-angle);
		nextPosition.z -= s*sin(-angle);
	}
					 break;

	case MOVE_LEFT: {																		//przemieszczenie w lewo
																							//previousPosition = position;
		double s = speed*t;																	//s - warto�� przemieszczenia, speed - pr�dko�� postaci, t/1000000.0 - czas trwania poprzedniej klatki w sek.
		nextPosition.x += s*cos(-angle);
		nextPosition.z += s*sin(-angle);
	}
					break;

	case MOVE_FORWARD: {																	//przemieszczenie do przodu
																							//previousPosition = position;
		double s = speed*t;																	//s - warto�� przemieszczenia, speed - pr�dko�� postaci, t/1000000.0 - czas trwania poprzedniej kaltki w sek.
		nextPosition.x -= s*sin(-angle);
		nextPosition.z += s*cos(-angle);
	}
					   break;

	case MOVE_BACKWARD: {																	//przemieszczenie do ty�u
																							//previousPosition = position;
		double s = speed*t;																	//s - warto�� przemieszczenia, speed - pr�dko�� postaci, t/1000000.0 - czas trwania poprzedniej klatki w sek.
		nextPosition.x += s*sin(-angle);
		nextPosition.z -= s*cos(-angle);
	}
						break;

	case TURN_RIGHT: {																		//obr�t w prawo
		LOOK_ACTION& look = static_cast<LOOK_ACTION&>(*Action);
		previousOrientation = orientation;
		double yRot = look.mouseMove * t * turnSensitivity * 360.0;							//yRot - k�t obrotu, Action.param[0] - warto�� przemieszczenia myszy w poprzedniej klatce
																							//t/1000000.0 - czas trwania poprzedniej klatki w sek., turnSensitivity - czu�o�� obrotu postaci
		orientation.y -= yRot;																//ustawienie nowej warto�ci orientacji postaci gracza w osi Y
		if (orientation.y < 0)																//sprawdzenie czy warto�� orientacji przekroczy�a zakres
			orientation.y = 360.0;
	}
					 break;

	case TURN_LEFT: {																		//obr�t w lewo
		LOOK_ACTION& look = static_cast<LOOK_ACTION&>(*Action);
		previousOrientation = orientation;
		double yRot = look.mouseMove * t * turnSensitivity * 360.0;							//yRot - k�t obrotu w osi Y, Action.param[0] - warto�� przemieszczenia myszy w poprzedniej klatce w osi X
																							//t/1000000.0 - czas trwania poprzedniej klatki w sek., turnSensitivity - czu�o�� obrotu postaci
		orientation.y += yRot;																//ustawienie nowej warto�ci orientacji postaci w osi Y
		if (orientation.y > 360.0)															//sprawdzenie czy warto�� orientacji przekroczy�a zakres
			orientation.y = 0.0;
	}
					break;

	case LOOK_UP: {																			//spojrzenie w g�r�
		LOOK_ACTION& look = static_cast<LOOK_ACTION&>(*Action);
		double xRot = look.mouseMove  * t * turnSensitivity * 360.0;						//xRot - k�t obrotu w osi X, Action.param[0] - warto�� przemieszczenia myszy w poprzedniej klatce w osi Y
																							//t/1000000.0 - czas trwania poprzedniej klatki w sek., turnSensitivity - czu�o�� obrotu postaci
		lookAngle -= xRot;
		if (lookAngle < -90.0) lookAngle = -90.0;
	}
				  break;

	case LOOK_DOWN: {																		//spojrzenie w d�
		LOOK_ACTION& look = static_cast<LOOK_ACTION&>(*Action);
		double xRot = look.mouseMove * t * turnSensitivity*360.0;							//xRot - k�t obrotu w osi X, Action.param[0] - warto�� przemieszczenia myszy w poprzedniej klatce w osi Y
																							//t/1000000.0 - czas trwania poprzedniej klatki w sek., turnSensitivity - czu�o�� obrotu postaci
		lookAngle += xRot;
		if (lookAngle > 90) lookAngle = 90.0;
	}
					break;

	case FALL: {																			//spadanie
		FALL_ACTION& fall = static_cast<FALL_ACTION&>(*Action);								//rzutowanie w g�r� hierarchii w celu uzyskania w�a�ciwgo obiektu akcji
		fall.time += t;																		//aktualizacja czasu spadania
		nextPosition.x += fall.shift.x;														//obliczenie nast�pnej pozycji postaci
		nextPosition.z += fall.shift.z;
		nextPosition.y = fall.position.y - 0.5*G*(fall.time*fall.time) * weight;
	}
			   break;

	case JUMP: {																			//skok
		JUMP_ACTION& jump = static_cast<JUMP_ACTION&>(*Action);								//rzutowanie w g�r� hierarchii w celu uzyskania w�a�ciwego obiektu akcji
		jump.time += t;																		//aktualizacja czasu skoku
		nextPosition.x += jump.shift.x / 1.33;												//obliczenie nast�pnej pozycji postaci
		nextPosition.z += jump.shift.z / 1.33;
		nextPosition.y = jump.position.y + jump.shift.y*jump.time - 0.5*G*(jump.time*jump.time)*weight;
	}
			   break;

	default:																				//warto�� domy�lna
		PerformAdditionalAction(Action);													//wykonanie akcji niestandardowej
		break;
	}
}

//dostosowanie akcji przemieszczenia
void DynamicCharacter::AdjustMoveAction(Vector k) {
	nextPosition = position + k;
}

//aktualizacja pozycji postaci
void DynamicCharacter::UpdatePosition() {
	previousPosition = position;
	position = nextPosition;
	nextPosition = position;
}

//aktualizacja orientacji postaci
void DynamicCharacter::UpdateOrientation() {
	previousOrientation = orientation;
}

void DynamicCharacter::Update() {
	UpdatePosition();
	UpdateOrientation();
}
