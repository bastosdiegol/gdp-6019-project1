#include <iostream>			// cout
#include <random>
#include <ctime>
#include <Windows.h>

#include "ArtilleryGame.h"
#include "AssetInfo.h"

//#define DEBUG_LOG_ENABLED
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
unsigned int ExplosionMaterialId;


// TODO:
// #include "YourPhysicsClass.h"

/// <summary>
/// Default constructor
/// Set all class variables to the desired default state
/// </summary>
ArtilleryGame::ArtilleryGame()
	: m_PlayerTank(nullptr)
	, m_EnemyTank(nullptr)
	, m_Bullet(0) 
	, particleSystem(nullptr)
	, aimVec(glm::vec3(0.0f))
	, selectedMuni(MORTAR)
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

	srand(time(0));
	m_PlayerTank->Position = glm::vec3(RandFloat(-20.0f, 20.0f), 0, RandFloat(-20.0f, 20.0f));
	m_EnemyTank->Position  = glm::vec3(RandFloat(-20.0f, 20.0f), 0, RandFloat(-20.0f, 20.0f));
	//m_Bullet->Position     = glm::vec3(10, 2, 0);
	//m_Bullet->Position     = m_PlayerTank->Position;

	// Creating of N bullets to be used
	// Setting the position of all bullets to the PlayerTank position to set them hidden while not used
	particleSystem = new ParticleSystem(m_PlayerTank->Position, MAX_BULLETS);
	m_Bullet.resize(MAX_BULLETS);
	for (int i = 0; i < MAX_BULLETS; i++) {
		m_Bullet[i] = CreateGameObjectByType("Bullet");
		m_Bullet[i]->Position = m_PlayerTank->Position;
	}
	// Creating of N particles to be used on the explosion
	// Setting the position of all bullets to the EnemyTank position to set them hidden while not used
	m_ExplosionParticles.resize(EXPLOSION_PARTICLES);
	for (int i = 0; i < EXPLOSION_PARTICLES; i++) {
		m_ExplosionParticles[i] = CreateGameObjectByType("ExplosionParticle");
		m_ExplosionParticles[i]->Position = m_EnemyTank->Position;
	}
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
	delete particleSystem;
	for (int i = 0; i < MAX_BULLETS; i++) {
		delete m_Bullet[i];
	}
	for (int i = 0; i < EXPLOSION_PARTICLES; i++) {
		delete m_ExplosionParticles[i];
	}
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
	m_PlayerTank->Position	= glm::vec3(RandFloat(-20.0f, 20.0f), 0, RandFloat(-20.0f, 20.0f));
	m_EnemyTank->Position	= glm::vec3(RandFloat(-20.0f, 20.0f), 0, RandFloat(-20.0f, 20.0f));
	aimVec					= glm::vec3(0.0f);				// Resets the aim
	isGameOver				= false;						// Resets the game
	isExplosionTime			= false;						// Resets the explosion
	EXPLOSION_TIMER			= 0.0f;							// Resets the explosion timer
	particleSystem->setPosition(m_PlayerTank->Position);	// Resets all hidden bullets
	for (int i = 0; i < MAX_BULLETS; i++) {
		m_Bullet[i]->Position = m_PlayerTank->Position;
	}
	for (int i = 0; i < EXPLOSION_PARTICLES; i++) {			// Resets all hidden explosion debries
		m_ExplosionParticles[i]->Position = m_EnemyTank->Position;
	}
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
	if (GDP_IsKeyPressed('a') || GDP_IsKeyPressed('A') || GDP_IsKeyHeldDown('a') || GDP_IsKeyHeldDown('A'))
		aimVec += glm::vec3(0.01f, 0.0f, 0.0f);
	if (GDP_IsKeyPressed('d') || GDP_IsKeyPressed('D') || GDP_IsKeyHeldDown('d') || GDP_IsKeyHeldDown('D'))
		aimVec += glm::vec3(-0.01f, 0.0f, 0.0f);
	if (GDP_IsKeyPressed('w') || GDP_IsKeyPressed('W') || GDP_IsKeyHeldDown('w') || GDP_IsKeyHeldDown('W'))
		aimVec += glm::vec3(0.0f, 0.0f, 0.01f);
	if (GDP_IsKeyPressed('s') || GDP_IsKeyPressed('S') || GDP_IsKeyHeldDown('s') || GDP_IsKeyHeldDown('S'))
		aimVec += glm::vec3(0.0f, 0.0f, -0.01f);
	if (GDP_IsKeyPressed('q') || GDP_IsKeyPressed('Q') || GDP_IsKeyHeldDown('q') || GDP_IsKeyHeldDown('Q'))
		aimVec += glm::vec3(0.0f, -0.01f, 0.0f);
	if (GDP_IsKeyPressed('e') || GDP_IsKeyPressed('E') || GDP_IsKeyHeldDown('e') || GDP_IsKeyHeldDown('E'))
		aimVec += glm::vec3(0.0f, 0.01f, 0.0f);
	if (GDP_IsKeyPressed('1'))
		selectedMuni = MORTAR;
	if (GDP_IsKeyPressed('2'))
		selectedMuni = TURRET;
	if (GDP_IsKeyPressed('3'))
		selectedMuni = MISSILE;
	if (GDP_IsKeyPressed('4'))
		selectedMuni = LASER;
	if (GDP_IsKeyPressed('5'))
		selectedMuni = CLUSTER;
	if (GDP_IsKeyPressed(32) || (GDP_IsKeyHeldDown(32) && selectedMuni == TURRET) && !isGameOver)
		this->FireProjectile();
	if (GDP_IsKeyPressed('n') || GDP_IsKeyPressed('N'))
		this->StartNewGame();
	
	if(!isGameOver) {
		// Calling the physics system to update all living particles
		isGameOver = particleSystem->IntegrateAndCheckCollision(0.01f, m_EnemyTank->Position);
		if (isGameOver) {
			std::cout << "Enemy defeated! Press (N) for a new game!" << std::endl;
			CreateExplosion(m_EnemyTank->Position);
			m_EnemyTank->Position = glm::vec3(99.9f);
			isExplosionTime = true;
		}
		// Iteration to reflect the updated particles position on the objects drawn in screen
		for (int i = 0; i < particleSystem->getNumParticles(); i++) {
			Particle* p = particleSystem->getParticle(i);
			m_Bullet[i]->Position = p->getPosition();
		}
	}
	if (isExplosionTime && EXPLOSION_TIMER < EXPLOSION_DURATION) {
		particleSystem->Integrate(0.01f);
		EXPLOSION_TIMER += 0.01f;
		// Iteration to reflect the updated explosion particles position on the objects drawn in screen
		for (int i = 0; i < EXPLOSION_PARTICLES; i++) {
			Particle* p = particleSystem->getParticle(i);
			m_ExplosionParticles[i]->Position = p->getPosition();
		}
	}
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
	if (type.compare("ExplosionParticle") == 0) {
		DEBUG_PRINT("Create Explosion Particle!\n");
		GameObject* go = GDP_CreateGameObject();
		go->Renderer.ShaderId = 1;
		go->Renderer.MeshId = ProjectileModelId;
		go->Renderer.MaterialId = ExplosionMaterialId;
		go->Position = glm::vec3(0, 0, 0);
		return go;
	}

	// Invalid game object type, return nullptr
	return nullptr;
}

// Function that allocates a particle and fire it as projectile
void ArtilleryGame::FireProjectile() {
	// Undefined Bullet Type Up Vector
	// For each type of Bullet we are going to define a specific up vector
	float defaultAge	 = 5.0f;
	float defaultDamping =  1.0f;
	float defaultMass	 =	1.0f;
	// Gravity Acceleration
	glm::vec3 gravity(0.0f, -9.8f, 0.0f);
	// Normalizes the aimVector and checks if its 0.0f
	glm::vec3 aimedUpVector = aimVec;
	//if (aimVec == glm::vec3(0.0f))
	//	aimedUpVector = glm::vec3(0.0f);
	//else
	//	aimedUpVector = glm::normalize(aimVec);

	switch (selectedMuni) {
		// Each case will SUM the Munition Type Up Vector with the Normalized vector resulted from Aiming
		// Then it will allocate a particle passing this new Up Vector modified by the aim, an age, damping and mass
	case MORTAR:
		aimedUpVector += glm::vec3(10.0f, 10.0f, 0.0f);
		particleSystem->AllocateParticle(aimedUpVector, gravity, defaultAge, defaultDamping, defaultMass);
		break;
	case TURRET:
		aimedUpVector += glm::vec3(5.0f, 5.0f, 0.0f);
		particleSystem->AllocateParticle(aimedUpVector, gravity, defaultAge, defaultDamping, defaultMass);
		break;
	case MISSILE:
		aimedUpVector += glm::vec3(20.0f, 20.0f, 0.0f);
		particleSystem->AllocateParticle(aimedUpVector, gravity, defaultAge, defaultDamping, defaultMass);
		break;
	case LASER:
		aimedUpVector += glm::vec3(5.0f, 0.01f, 0.0f);
		particleSystem->AllocateParticle(aimedUpVector, aimedUpVector, defaultAge, defaultDamping, defaultMass);
		break;
	case CLUSTER:
		aimedUpVector += glm::vec3(10.0f, 10.0f, 0.0f);
		particleSystem->AllocateParticle(aimedUpVector, gravity, defaultAge, defaultDamping, defaultMass);
		break;
	}	
}

// Function that creates an explosion using the Particle System
void ArtilleryGame::CreateExplosion(glm::vec3 position){
	// Collection of min and max values to be used on the creation of the explosion
	float defaultDamping = 1.0f;
	float defaultMass = 1.0f;
	float xmax = 2;
	float xmin = -2;
	float ymax = 2;
	float ymin = -2;
	float zmax = 2;
	float zmin = -2;
	glm::vec3 gravity(-9.8f);

	// Creates all particles to be used on the explosion
	for (int i = 0; i < EXPLOSION_PARTICLES; i++) {
		particleSystem->AllocateParticle(position
										, glm::vec3(RandFloat(xmax, xmin), RandFloat(ymax, ymin), RandFloat(zmax, zmin))
										, gravity
										, EXPLOSION_DURATION
										, defaultDamping
										, defaultMass);
	}
}

// Utility function for a random range of two floats
float RandFloat(float min, float max) {
	if (max == min)
		return 0.f;

	int diff = (max - min) * 1000;
	return min + (rand() % diff) / 1000.0f;
}