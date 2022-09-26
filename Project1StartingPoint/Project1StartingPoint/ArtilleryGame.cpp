#include <iostream>			// cout
#include <random>
#include <ctime>
#include <Windows.h>

#include "ArtilleryGame.h"
#include "AssetInfo.h"

#define DEBUG_LOG_ENABLED
#ifdef DEBUG_LOG_ENABLED
#define DEBUG_PRINT(x, ...) printf(x, __VA_ARGS__)
#else
#define DEBUG_PRINT(x)
#endif

// Ids preloaded in the main.cpp to be referenced when
// creating specific game objects for your game.
// - EnemyTank, PlayerTank, and Bullet
unsigned int TankModelId;
unsigned int ProjectileModelId;
unsigned int PlayerMaterialId;
unsigned int EnemyMaterialId;
unsigned int BulletMaterialId;

// TODO:
// #include "YourPhysicsClass.h"

/// <summary>
/// Default constructor
/// Set all class variables to the desired default state
/// </summary>
ArtilleryGame::ArtilleryGame()
	: m_PlayerTank(nullptr)
	, m_EnemyTank(nullptr)
	, m_Bullet(nullptr) 
{
	DEBUG_PRINT("ArtilleryGame::ArtilleryGame\n");
	// DO NOTHING!!!!!!!!
}

/// <summary>
/// Default destructor
/// </summary>
ArtilleryGame::~ArtilleryGame()
{
	DEBUG_PRINT("ArtilleryGame::~ArtilleryGame\n");
	// DO NOTHING!!!!!!!!
}
/// <summary>
/// Create everything needed for your game here
/// such as memory allocation calls
/// </summary>
void ArtilleryGame::Initialize()
{
	DEBUG_PRINT("ArtilleryGame::Initialize\n");
	// TODO:
	// - Create a Player Tank GameObject
	// - Create an Enemy Tank GameObject
	// - Create projectile(s)
	m_PlayerTank = CreateGameObjectByType("Player");
	m_EnemyTank = CreateGameObjectByType("Enemy");
	m_Bullet = CreateGameObjectByType("Bullet");

	srand(time(0));
	m_PlayerTank->Position = glm::vec3(RandFloat(-20.0f, 20.0f), 0, RandFloat(-20.0f, 20.0f));
	m_EnemyTank->Position  = glm::vec3(RandFloat(-20.0f, 20.0f), 0, RandFloat(-20.0f, 20.0f));
	//m_Bullet->Position     = glm::vec3(10, 2, 0);
	m_Bullet->Position     = m_PlayerTank->Position;
}

/// <summary>
/// Handle everything that needs to be destroyed
/// such as memory de-allocation.
/// </summary>
void ArtilleryGame::Destroy()
{
	DEBUG_PRINT("ArtilleryGame::Destroy\n");
	// TODO:
	delete m_PlayerTank;
	delete m_EnemyTank;
	delete m_Bullet;
}

/// <summary>
/// StartNewGame
/// 1. Randomly place the enemy tank at a random valid location 
///    on the map
/// 2. Randomly place the player tank at a random valid location
///    on the map
/// 3. Reset the bullet(s)
/// </summary>
void ArtilleryGame::StartNewGame()
{
	DEBUG_PRINT("ArtilleryGame::StartNewGame\n");
	// TODO:
	m_PlayerTank->Position = glm::vec3(RandFloat(-20.0f, 20.0f), 0, RandFloat(-20.0f, 20.0f));
	m_EnemyTank->Position = glm::vec3(RandFloat(-20.0f, 20.0f), 0, RandFloat(-20.0f, 20.0f));
	m_Bullet->Position = m_PlayerTank->Position;
	//MessageBox(NULL, (LPCWSTR)L"New Game Begun! Good Luck!", (LPCWSTR)L"New Game", MB_OK | MB_ICONINFORMATION);

}

/// <summary>
/// Update all bullets here
/// - Call your Physics class to update all projectiles
/// Check for bullet collision (position.y <= 0, hit ground)
/// Check for User input:
/// >>> GDP_IsKeyPressed, GDP_IsKeyHeldDown <-- Case Sensitive
/// >>> example: if (GDP_IsKeyPressed('n') || GDP_IsKeyPressed('N'))
/// - Input for changing the bullet direction	(wasd, etc)
/// - Input to change the projectile type		(1,2,3,4,5)
/// - Input to fire a projectile				(space)
/// - Input to start a new game					(n)
/// </summary>
void ArtilleryGame::GameUpdate()
{
	DEBUG_PRINT("ArtilleryGame::GameUpdate\n");

	// TODO:
	// Typically moved to a UserInput Section
	//if (GDP_IsKeyHeldDown('a'))
	//	m_PlayerTank.Position->ApplyForce(Vector3(1, 0, 0));
	//if (GDP_IsKeyHeldDown('d'))
	//	m_PlayerTank.Position->ApplyForce(Vector3(-1, 0, 0));
	//if (GDP_IsKeyHeldDown('w'))
	//	m_PlayerTank.Position->ApplyForce(Vector3(0, 0, 1));
	//if (GDP_IsKeyHeldDown('s'))
	//	m_PlayerTank.Position->ApplyForce(Vector3(0, 0, -1));
	if (GDP_IsKeyPressed('n') || GDP_IsKeyPressed('N'))
		this->StartNewGame();

}

/// <summary>
/// Print provided text to the console for the user
/// </summary>
/// <param name="text"></param>
void ArtilleryGame::DisplayTextToUser(const std::string& text)
{
	std::cout << text << "\n";
}

GameObject* ArtilleryGame::CreateGameObjectByType(const std::string& type)
{
	DEBUG_PRINT("ArtilleryGame::CreateGameObjectByType(%s)\n", type.c_str());

	if (type.compare("Player") == 0) {
		DEBUG_PRINT("Create player!\n");
		GameObject* go = GDP_CreateGameObject();
		go->Renderer.ShaderId = 1;
		go->Renderer.MeshId = TankModelId;
		go->Renderer.MaterialId = PlayerMaterialId;
		return go;
	}
	if (type.compare("Enemy") == 0) {
		DEBUG_PRINT("Create Enemy!\n");
		GameObject* go = GDP_CreateGameObject();
		go->Renderer.ShaderId = 1;
		go->Renderer.MeshId = TankModelId;
		go->Renderer.MaterialId = EnemyMaterialId;
		return go;
	}
	if (type.compare("Bullet") == 0) {
		DEBUG_PRINT("Create Bullet!\n");
		GameObject* go = GDP_CreateGameObject();
		go->Renderer.ShaderId = 1;
		go->Renderer.MeshId = ProjectileModelId;
		go->Renderer.MaterialId = BulletMaterialId;
		go->Position = glm::vec3(0, 0, 0);
		return go;
	}

	// Invalid game object type, return nullptr
	return nullptr;
}

// Utility function for a random range of two floats
float RandFloat(float min, float max) {
	if (max == min)
		return 0.f;

	int diff = (max - min) * 1000;
	return min + (rand() % diff) / 1000.0f;
}