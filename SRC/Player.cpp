#include "Player.h"

//konstruktor pobieraj�cy jedynie nazw� pliku przechowuj�cego model postaci [reszcie parametr�w przypisuje si� warto�ci domy�lne]
Player::Player(const std::string& filename) : DynamicCharacter(filename) {									//wywo�anie odpowiedniego konstruktora klasy Character
	//wype�nienie wektora akcja - wej�cie warto�ciami domy�lnymi
	//------------------------------KLAWIATURA------------------------------
	action_keyboard_relations.push_back(ACTION_INPUT(MOVE_LEFT, MOVEMENT, INPUTCONST::A));
	action_keyboard_relations.push_back(ACTION_INPUT(MOVE_RIGHT, MOVEMENT, INPUTCONST::D));
	action_keyboard_relations.push_back(ACTION_INPUT(MOVE_FORWARD, MOVEMENT, INPUTCONST::W));
	action_keyboard_relations.push_back(ACTION_INPUT(MOVE_BACKWARD, MOVEMENT, INPUTCONST::S));
	action_keyboard_relations.push_back(ACTION_INPUT(JUMP, AIR, INPUTCONST::SPACE));
	action_keyboard_relations.push_back(ACTION_INPUT(RELOAD, OTHER, INPUTCONST::R));
	//---------------------------------MYSZ---------------------------------
	action_mouse_relations.push_back(ACTION_INPUT(TURN_RIGHT, ORIENTATION, INPUTCONST::MOUSE_RIGHT));
	action_mouse_relations.push_back(ACTION_INPUT(TURN_LEFT, ORIENTATION, INPUTCONST::MOUSE_LEFT));
	action_mouse_relations.push_back(ACTION_INPUT(LOOK_UP, ORIENTATION, INPUTCONST::MOUSE_UP));
	action_mouse_relations.push_back(ACTION_INPUT(LOOK_DOWN, ORIENTATION, INPUTCONST::MOUSE_DOWN));
	action_mouse_relations.push_back(ACTION_INPUT(SHOOT, OTHER, INPUTCONST::MOUSE_LEFT_BUT));

	lookAngle = Camera::GetOrientation().x;
}

//konstruktor pobieraj�cy nazw� pliku, nazw�, pozycj� oraz orientacj� postaci
Player::Player(const std::string& filename, const std::string& Name, const Vector& Position, const Vector& Orientation) :
	DynamicCharacter(filename, Name, Position, Orientation) {									//wywo�anie odpwiedniego konstrukotra klasy DynamicCharacter
	//wype�nienie wekotra akcja - wej�cie warto�ciami domy�lnymi
	//------------------------------KLAWIATURA------------------------------
	action_keyboard_relations.push_back(ACTION_INPUT(MOVE_LEFT, MOVEMENT, INPUTCONST::A));
	action_keyboard_relations.push_back(ACTION_INPUT(MOVE_RIGHT, MOVEMENT, INPUTCONST::D));
	action_keyboard_relations.push_back(ACTION_INPUT(MOVE_FORWARD, MOVEMENT, INPUTCONST::W));
	action_keyboard_relations.push_back(ACTION_INPUT(MOVE_BACKWARD, MOVEMENT, INPUTCONST::S));
	action_keyboard_relations.push_back(ACTION_INPUT(JUMP, AIR, INPUTCONST::SPACE));
	action_keyboard_relations.push_back(ACTION_INPUT(RELOAD, OTHER, INPUTCONST::R));
	//---------------------------------MYSZ---------------------------------
	action_mouse_relations.push_back(ACTION_INPUT(TURN_RIGHT, ORIENTATION, INPUTCONST::MOUSE_RIGHT));
	action_mouse_relations.push_back(ACTION_INPUT(TURN_LEFT, ORIENTATION, INPUTCONST::MOUSE_LEFT));
	action_mouse_relations.push_back(ACTION_INPUT(LOOK_UP, ORIENTATION, INPUTCONST::MOUSE_UP));
	action_mouse_relations.push_back(ACTION_INPUT(LOOK_DOWN, ORIENTATION, INPUTCONST::MOUSE_DOWN));
	action_mouse_relations.push_back(ACTION_INPUT(SHOOT, OTHER, INPUTCONST::MOUSE_LEFT_BUT));

	lookAngle = Camera::GetOrientation().x;
}

//dodanie broni dla postaci
void Player::AddWeapon(const std::string& weaponName) {
	//iniclaizacja sprytnego wska�nika broni
	weapon = WeaponPtr(new Gun(weaponName, name, collisionBox.midPoint, position, orientation));														
	weapon->enableCharacter();															//odblokowanie obiektu broni
}

//dodatkowe akcje postaci gracza
void Player::PerformAdditionalAction(ActionPtr Action) {
	double t = PHYSICSMODULE::targetFrameTime;											//predefiniowana sta�a warto�� trwania jednej iteracji symulacji fizycznych
	switch (Action->name) {
		case SHOOT: {																		//STRZA�
			if (weapon!=nullptr && weapon->IsEnabled()) {														//je�li bro� jest odblokowana
				Gun& playerGun = static_cast<Gun&>(*weapon);								
				playerGun.Shoot();															//wykonanie strza�u
				break;
			}
		}

		case RELOAD: {
			if (weapon!=nullptr && weapon->IsEnabled()) {
				Gun& playerGun = static_cast<Gun&>(*weapon);
				playerGun.AddAction(ACTION(RELOAD, OTHER));
				break;
			}
		}

		default:
			break;
	}
}

//funkcja sprawdzaj�ca czy dany sygna� wej�ciowy 'val' z klawiatury znajduje si� w wekotrze relacji akcja - sygna� wej�ciowy z klawiatury
bool Player::CheckKeyboardInputVal(int val) {
	for (unsigned int i = 0; i < action_keyboard_relations.size(); i++) {
		if (action_keyboard_relations[i].input == val)									//je�li dany sygna� wej�ciowy ['val'] znajduje si� w wekotrze relacji zwr�� warto�� TRUE
			return true;
	}
	return false;																		//w przeciwnym wypadku zwr�� FALSE
}

//dodanie akcji zwi�zanej z danym sygna�em wej�ciowym 'inputVal' z klawiatury do wektora akcji do wykonania przez posta� gracza
void Player::AddKeyboardAction(int inputVal) {
	for (unsigned int i = 0; i < action_keyboard_relations.size(); i++) {
		if (action_keyboard_relations[i].input == inputVal) {							//je�li dany sygna� wej�ciowy ['inputVal'] znajduje si� w wektorze relacji
			switch (action_keyboard_relations[i].subActionName) {
			case MOVEMENT: {
					ActionPtr ptr(new MOVE_ACTION(action_keyboard_relations[i].action));
					actions.push_back(ptr);
					break;
				}
			case AIR: {
					if (action_keyboard_relations[i].action == JUMP) {
						if (!(actions.size()>0 && actions[0]->subActionName == AIR)) {
							Vector midPt = collisionBox.midPoint;
							position.y += midPt.y / 4.0;
							ActionPtr ptr(new JUMP_ACTION(position, position - previousPosition, jumpStrength));
							actions.push_back(ptr);
							if (actions.size() > 0) {
								ActionPtr tmp = actions[0];
								actions[0] = actions[actions.size() - 1];
								actions[actions.size() - 1] = tmp;
							}
						}
					}
					break;
				}
			case OTHER: {
					ActionPtr ptr(new ACTION(action_keyboard_relations[i].action,action_keyboard_relations[i].subActionName));
					actions.push_back(ptr);
					break;
				}
			}
			break;
		}
	}
}

//funkcja sprawdzaj�ca czy dany sygna� wej�ciowy 'val' z klawiatury znajduje si� w wektorze relacji akcja - sygna� wej�ciowy z myszy
bool Player::CheckMouseInputVal(int val) {
	for (unsigned int i = 0; i < action_mouse_relations.size(); i++) {					//je�li dany sygna� wej�ciowy ['val'] znajduje si� w wektorze relacji zwr�� warto�� TRUE
		if (action_mouse_relations[i].input == val)				
			return true;
	}
	return false;																		//w preciwnym wypadku zwr�� FALSE
}

//dodanie akcji zwi�zanej z danym sygna�em wej�ciowym 'inputVal' z myszy do wekotra akcji do wykonania przez posta� gracza
//parametr MouseMove okre�la warto�� przemieszczenia myszy [parametr MousMove zapisywany jest jako warto�� param[0] struktury ACTION]
void Player::AddMouseAction(int inputVal,int MouseMove) {
	for (unsigned int i = 0; i < action_mouse_relations.size(); i++) {
		if (action_mouse_relations[i].input == inputVal) {
			switch (action_mouse_relations[i].subActionName) {
			case ORIENTATION: {
					ActionPtr ptr(new LOOK_ACTION(action_mouse_relations[i].action, MouseMove));
					actions.push_back(ptr);
					break;
				}
			case OTHER: {
					ActionPtr ptr(new ACTION(action_mouse_relations[i].action, action_mouse_relations[i].subActionName));
					actions.push_back(ptr);
					break;
				}
			}

			break;
		}
	}
}

//aktualizacja pozycji postaci
void Player::UpdatePosition() {
	DynamicCharacter::UpdatePosition();													//uaktualnienie pozycji postaci						
	if (weapon != nullptr)
		weapon->SetNextPosition(position);													//uaktualnienie pozycji broni postaci
}

//aktualizacja orientacji postaci
void Player::UpdateOrientation() {
	DynamicCharacter::UpdateOrientation();												//uaktualnienie orientacji postaci
	if (weapon != nullptr) {																//uaktualnienie orientacji broni
		Vector weaponOrient = orientation;
		weaponOrient.x = -lookAngle;
		weapon->setOrientation(weaponOrient);
	}
}

void Player::Update() {
	UpdatePosition();
	UpdateOrientation();

	if (weapon != nullptr) {
		weapon->Update();
	}
}

//narysowanie modelu
void Player::DrawModel() {
	OBJmodel::DrawModel();
	if (weapon != NULL)
		weapon->DrawModel();
};