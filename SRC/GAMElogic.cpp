#include "GAMElogic.h"

//funkcja inicjalizuj�ca logik� gry
void GAMElogic::InitializeGameLogic() {
	InitilizeTimers();															//inicjalizacja timer�w
	InitilizeLogFiles();														//inicjalziacja plik�w log�w
	GAMEINPUT::InitalizeInputSystem();											//inicjalizacja systemu wej�cia
	InitializeOpenGLProperties();												//inicjalziacja podstawowych w�a�ciwo�ci okna OpenGL
	InitializeLights();															//inicjalizacja �r�de� �wiat�a
	InitializeMaterials();														//inicjalziacja materia��w
	PhysicsModule::ModelsRegistration();										//rejestracja dodatkowych modli fizyki			
	WeaponDatabase::Initialize();												//inicjalizacja bazy danych broni
	InitializeMaps();															//inicjalizacja map
	InitializePlayer();															//inicjalizacja postaci gracza
	InitializeBots();															//inicjalizacja bot�w
	InitializeCharacters();														//inicjalizacja modeli
	InitilizeCamera();															//inicjalizacja kamery
	PlayerInput::InitializePlayerInputs();										//inicjalizacja wektora sygna��w wej�ciowych gracza
	CONSOLE::Initialize();														//inicjalizacja 'konsoli' gry
	GUI::Initialize();
}

//ponowana inicjalizacja logiki gry [wykonywana w razie 'zniszczenia' okna gry]
//[u�y� w przypadku zmiany uchwytu HWND okna WinAPI]
void GAMElogic::RefreshGameLogicInitialization() {
	GAMEINPUT::ShutdownInputSystem();											//zwolnienie aktualnego systemu wej�cia [zale�nego od uchwytu okna]
	GAMEINPUT::InitalizeInputSystem();											//inicjalizacja systemu wej�cia

	InitializeOpenGLProperties();												//inicjalizacja podstawowych wa��ciwo�ci okna OpenGL

	//ponowna inicjalizacja stworzonych wcze�niej �r�de� �wiat�a
	for (unsigned int i = 0; i < GameObjects::lights.size(); i++) {
		GameObjects::lights[i].Initialize();
		GameObjects::lights[i].EnableLight();
	}

	InitializeMaterials();														//inicjalizacja materia��w
	CONSOLE::Initialize();														//inicjalizacja 'konsoli' gry
	GUI::Initialize();
}

//przetworzenie pojedynczej klatki gry
void GAMElogic::ProccessFrame() {
	TIMER::QuickStartTimeMeasurment(0);											//rozpocz�cie pomiaru czasu trwania pojedynczej klatki [indeks dla znacznika "FPS" = 0]
		
	PhysicsModule::ProcessActionsAndPhysics();									//przetworzenie akcji gracza i bot�w oraz fizyki obiekt�w

	GameGraphics::ProccessGraphics();											//przetworzenie grafiki

	TIMER::QuickStopTimeMeasurment(0);											//koniec pomiaru czasu trwania pojedynczej klatki [indeks dla znacznika "FPS" = 0]
}

//inicjalizacja kamery w �wiecie gry
void GAMElogic::InitilizeCamera() {
	Camera::Initialize(0.0, 0.0, 0.0, 0.0, 0.0, -100.0, 0.0, 1.0, 0.0);			//inicjalizacja kamery
	//Camera::SetRelativePosition(0.0, 5.0, -8.0);								//ustawienie pozycji kamery wzgl�dem gracza
	Vector size = (GameObjects::players[0].getCollisionBox().maxPoint - GameObjects::players[0].getCollisionBox().midPoint) * 2.0;
	Camera::SetRelativePosition(0.0, 0.8*size.y, 0.25);
	Camera::SetRelativeCenter(0.0, 0.0, 32.0);									//ustawienie pozycji punktu w kirunku kt�rym 'patrzy' kamera wzgl�dem gracza
	
	Vector orientation(0.0, 0.0, 0.0);											
	for (unsigned int i = 0; i < GameObjects::players.size(); i++) {			//przesukiwanie wektora obiekt�w postaci gracza
		if (GameObjects::players[i].IsEnabled()) {								//sprawdzenie czy posta� jest 'odblokowana'
			Vector playerOrientation = GameObjects::players[i].getOrientation();//je�li tak to pobierz orientacj� postaci
			orientation.y = playerOrientation.y;								//przypisanie kamerze orientacji wok� osi Y, takiej samej jak orientacja postaci gracza
			break;
		}
	}

	Vector relativePos = Camera::GetRelativePosition();							//pobranie pozycji relatywnej kamery
	Vector relativeCenter = Camera::GetRelativeCenter();						//pobranie pozycji relatywnej punktu 'wycentrowania' kamery

	//wyliczenie orientacji kamery wok� osi X ze wzoru:
	//orientation.x = atan ( relativePos.y / ( -relativePos.z + relativeCenter.z ) )
	//oraz przeliczenie jej z radian�w na stopnie
	orientation.x = atan2(relativePos.y, -relativePos.z + relativeCenter.z) * 180.0 / 3.1415;

	Camera::SetOrientation(orientation.x, orientation.y, orientation.z);		//ustawienie orientacji kamery
}

//inicjalizacja podstawowych w��sciwo�ci okna OpenGL
void GAMElogic::InitializeOpenGLProperties() {
	glClearColor((float)105 / 255, (float)159 / 255, (float)250 / 255, 1);		//niebieskie t�o
	glColor3f((GLfloat)0.8, (GLfloat)0.8, (GLfloat)0.8);						//kolor modeli podstawowych (bez tekstur)
	glShadeModel(GL_SMOOTH);													//�agodne cieniowanie na modelach
	glEnable(GL_LIGHTING);														//w��czenie o�wietlenia sceny
	glEnable(GL_DEPTH_TEST);													//nierysowanie przes�oni�tych powierzchni
	glEnable(GL_POLYGON_SMOOTH);												//wyg�adzanie powierzchni
	glEnable(GL_CULL_FACE);														//nierysowanie 'tylnich' powierzchni
}

//inicjalizacja o�wietlenia sceny
void GAMElogic::InitializeLights()  {
	//stworzenie testowego �r�d�a �wiat�a
	Light TEST_LIGHT(GL_LIGHT0, lightPosition | ambientLight | diffuseLight);
	TEST_LIGHT.SetAmbientParams((float)0.4, (float)0.4, (float)0.4, (float)1.0);
	TEST_LIGHT.SetDiffuseParams((float)0.4, (float)0.4, (float)0.4, (float)1.0);
	TEST_LIGHT.SetPosition(0.0, 100.0, 5.0);

	TEST_LIGHT.Initialize();													//inicjalziacja �wiat�a
	TEST_LIGHT.EnableLight();													//'w��czenie' �r�d�a �wiat�a

	GameObjects::lights.push_back(TEST_LIGHT);									//dodanie �r�d�a �wiat�a do odpowiedniego wektora
}

//inicjalizacja materia��w [funkcja testowa]
void GAMElogic::InitializeMaterials() {
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
}

//inicjalizacja postaci gracza [klasa Player]
void GAMElogic::InitializePlayer() {
	Vector position = { 4.0,1.0,6.0 };											//pozycja
	Vector orientation = { 0.0,0.0,0.0 };										//orientacja

	for (Map& map : GameObjects::maps) {
		if (map.IsEnabled()) {
			position.y = map.Get_Y_Pos(position);
			break;
		}
	}

	Player PLAYER("PLAYER_MODEL_1.obj", "PLAYER", position, orientation);		//inicajlizacja obiektu gracza
	PLAYER.SetSpeed(15.0);														//ustawienie odpowiedniej warto�ci pr�dko�ci
	PLAYER.SetTurnSensitivity(0.1);												//ustawienie odpowiedniej warto�ci czu�o�ci obrotu
	PLAYER.SetJumpStrength(30.0);
	PLAYER.SetWeight(9.0);
	PLAYER.AddWeapon("GUN_1");
	PLAYER.enableCharacter();													//uruchomienie postaci

	GameObjects::players.push_back(PLAYER);										//dodanie nowej postaci do kontenera przechowuj�cego wszystkie postacie
	
	CharacterRegister::RegisterPlayer(&GameObjects::players[GameObjects::players.size() - 1]);
	BulletCollision::RegisterGun(&(static_cast<Gun&>(*(GameObjects::players[GameObjects::players.size() - 1].GetWeapon()))));
}

//inicjalizacja wszystkich bot�w
void GAMElogic::InitializeBots() {
	Vector position = { 10.0,1.0, 5.0 };
	Vector orientation = { 0.0,-45.0,0.0 };

	srand(static_cast<unsigned>(time(0)));

	for (unsigned int i = 0; i <20; i++) {
		orientation.y = rand() % 180;
		position.x = (rand() % 60)-30;
		position.z = (rand() % 60)-30;
		AddNewBot(position, orientation);
	}

	for(Bot& bot:GameObjects::bots)
		CharacterRegister::RegisterBot(&bot);
}

//inicjalizacja postaci [klasa Character]
void GAMElogic::InitializeCharacters() {

}

//inicjalizacja map [klasa Map]
void GAMElogic::InitializeMaps() {
	Map MAP("MAP3.obj");
	MAP.enableCharacter();

	/*Character TEST1("model5.obj", "TEST1", Vector(0, 2, 25), Vector(0, 90, 0));
	TEST1.enableCharacter();
	Character TEST2("model6.obj", "TEST2", Vector(8, 0, 15), Vector(0, 0, 0));
	TEST2.enableCharacter();
	Character TEST3("model6.obj", "TEST3", Vector(6, 0, 12), Vector(0, 0, 0));
	TEST3.enableCharacter();
	Character TEST4("model6.obj", "TEST4", Vector(25, -2, -30), Vector(0, 45, 0));
	TEST4.enableCharacter();
	Character TEST5("model6.obj", "TEST5", Vector(30, -2, -32), Vector(0, 0, 0));
	TEST5.enableCharacter();
	Character TEST6("model5.obj", "TEST6", Vector(-8, 2, 15), Vector(0, 180, 0));
	TEST6.enableCharacter();
	Character TEST7("model5.obj", "TEST7", Vector(0, 2, 15), Vector(0, 0, 0));
	TEST7.enableCharacter();
	Character TEST8("model7.obj", "TEST8", Vector(-3, 4, 30), Vector(180, 0, 0));
	TEST8.enableCharacter();
	Character TEST9("model7.obj", "TEST9", Vector(5, 1, 0), Vector(0, 0, 0));
	TEST9.enableCharacter();
	Character TEST10("model8.obj", "TEST10", Vector(10, 1, 40), Vector(0, 0, 0));
	TEST10.enableCharacter();
	Character TEST11("model9.obj", "TEST11", Vector(20, 2, 30), Vector(0, 45, 0));
	TEST11.enableCharacter();

	MAP.LoadCharacter(TEST1);
	MAP.LoadCharacter(TEST2);
	MAP.LoadCharacter(TEST3);
	MAP.LoadCharacter(TEST4);
	MAP.LoadCharacter(TEST5);
	MAP.LoadCharacter(TEST6);
	MAP.LoadCharacter(TEST7);
	MAP.LoadCharacter(TEST8);
	MAP.LoadCharacter(TEST9);
	MAP.LoadCharacter(TEST10);
	MAP.LoadCharacter(TEST11);*/

	MAP.Initialize();

	GameObjects::maps.push_back(MAP);

	CharacterRegister::RegisterMap(&GameObjects::maps[GameObjects::maps.size() - 1]);
}

//inicjalizacja plik�w log�w
void GAMElogic::InitilizeLogFiles() {
	LOGFILE::CreateLogFile("FPS", "FRAME_TIME_MEASURMENT.txt");				//inicjalizacja pliku zapisuj�cego czas trwania pojdeynczej klatki gry
	LOGFILE::ClearLogFile("FPS");											//wyczyszcenie pliku
	//LOGFILE::CreateLogFile("SHOOT_TEST", "SHOOT_TEST.txt");
	//LOGFILE::ClearLogFile("SHOOT_TEST");
	//LOGFILE::CreateLogFile("SYNC_TEST", "PHYSICS_SYNC_TEST.txt");
	//LOGFILE::ClearLogFile("SYNC_TEST");
	//LOGFILE::CreateLogFile("MOUSE_TEST", "MOUSE_TEST.txt");
	//LOGFILE::ClearLogFile("MOUSE_TEST");
	//LOGFILE::CreateLogFile("BOT_HIT_TEST","BOT_HIT_TEST.txt");
	//LOGFILE::ClearLogFile("BOT_HIT_TEST");
}

//inicjalizacja timer�w
void GAMElogic::InitilizeTimers() {
	TIMER::GetFrequency();														//pobranie cz�stotliwo�ci performance countera
	TIMER::AddTimeMarker("FPS");												//dodanie zancznika timera dla pomiaru czasu trwwania jednej klatki
	TIMER::AddTimeMarker("Input");
	TIMER::AddTimeMarker("Physics");
	TIMER::AddTimeMarker("Graphics");
}

//dodanie nowego bota
void GAMElogic::AddNewBot(const Vector& position, const Vector& orientation) {
	Vector botPos = position;
	for (Map& map : GameObjects::maps) {
		if (map.IsEnabled()) {
			botPos.y = map.Get_Y_Pos(botPos);
			break;
		}
	}

	Bot newBot("PLAYER_MODEL_1.obj", "BOT_" + std::to_string(GameObjects::bots.size()), botPos, orientation);
	newBot.SetSpeed(10.0);
	newBot.SetWeight(9.0);
	newBot.SetTurnSensitivity(0.1);
	newBot.enableCharacter();
	GameObjects::bots.push_back(newBot);
}