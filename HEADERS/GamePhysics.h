#pragma once
#include <thread>
#include "GameObjects.h"
#include "CollisionDetection.h"
#include "GamePhysicsStruct.h"

#include "PlayerInput.h"
#include "BotsActions.h"

//------------------------------------------------------------------------------------------------
//-------------------------------------------FIZYKA GRY-------------------------------------------
//--------------------klasa odpowiadaj�ca za przetwarzanie 'fizyki' gry m.in.:--------------------
//-----------------------------------WYKONYWANIE AKCJI POSTACI------------------------------------
//------------------------------------------------------------------------------------------------

class GamePhysics {
	GamePhysics() {}																							//prywatny konstruktor domy�lny [singleton]
 
	static void PlayerActions();																				//przetwarzanie akcji gracza

	static void UpdatePlayerCollisionBox();																		//aktualizacja bry�y kolizji gracza

	static void CheckCollisions();																				//sprawdzenie kolizji

	static void CheckPlayersCollisions();																		//sprawdzenie kolizji dla postaci gracza z obiektami aktualnej mapy
	static void CheckBotsCollisions();																			//sprawdzenie kolziji dla bot�w z obiektami aktualnej mapy

	//-------------------------------------------------------------CheckCharacterCollisions()--------------------------------------------------------------
	static GAMEPHYSICS::CollisionStatus CheckCharacterCollisions(Map& map, DynamicCharacter& character);		//sprawdzenie kolizji dla danej postaci
	//static GAMEPHYSICS::AllCollisionsTypesVec LoadAllCollisionTypesVec(Map& map, DynamicCharacter& character, GAMEPHYSICS::specialNormals standardColVec)
	static GAMEPHYSICS::specialNormals LoadCharacterCollisionNormals(Map& map, DynamicCharacter& character);	//pobranie normalnych z obiektami z kt�rymi zasz�a kolizja
	static GAMEPHYSICS::ColContain_AllColTypeVec CreateDotProductVectors(Map& map, DynamicCharacter& character, 
		GAMEPHYSICS::specialNormals& normals);																	//rozdzielenie wekotra normalnych kolizji na podstawie iloczynu skalarnego z [0,1,0]
	static void SortVector(GAMEPHYSICS::specialNormals& colVec);												//posortowanie wektora normalnych ze wzgl�du na param. 'linesCrossed'
	static void NoCollisionState(DynamicCharacter& character, Map& map, double yMapVal, 
		const GAMEPHYSICS::CollisionVectorCheck& mapBoundriesCol);												//funkcja stanu dla braku kolizji
	static GAMEPHYSICS::CollisionVectorCheck StandardColState(GAMEPHYSICS::specialNormals& standardCol, DynamicCharacter& character);	//obliczenie nowej pozycji dla standardowej kolizji
	static GAMEPHYSICS::CollisionVectorCheck NegativeColState(GAMEPHYSICS::specialNormals& negativeCol, DynamicCharacter& character);	//obliczenie nowej pozycji dla 'negatywnej' kolziji
	static GAMEPHYSICS::CollisionVectorCheck GroundColState(GAMEPHYSICS::specialNormals& groundCol, DynamicCharacter& character);		//obliczenie nowej pozycji dla pozycji z obiektem pod�o�a
	static Vector AdjustNextPos(const GAMEPHYSICS::ColContain_AllColTypeVec& allColstruct, DynamicCharacter& character, Map& map, double yMapVal);														//dosotosowanie obliczonego wektora nowej pozycji ze wzgl�du na obecne kolizje
	static Vector AdjustNextPos_AdjustGroundCollisionAndFallAction(DynamicCharacter& character, const Vector& adjustedNextPos,
		double yMapVal, const GAMEPHYSICS::ColContain_AllColTypeVec& allColstruct);								//dostosowanie obliczonego wektora nowej pozycji ze wzgl�du na kolzij� z pod�o�em
																												//i akcji spadania gracza
	static GAMEPHYSICS::CollisionVectorCheck CheckMapBoundries(Map& map, DynamicCharacter& character);			//sprawdzenie czy posta� nie wyjdzie poza granice mapy
	static GAMEPHYSICS::CollisionStatus LoadCollisionStatusRetVal(const GAMEPHYSICS::ColContain_AllColTypeVec& allColStruct);			//za�adowanie statusu zwracanego dla badanej kolizji

public:
	static void ProccessPhysics();																				//przetwarzanie 'fizyki' �wiata gry

};