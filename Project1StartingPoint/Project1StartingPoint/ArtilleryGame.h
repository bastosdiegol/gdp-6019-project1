#pragma once

#include <gdp/Engine.h>
#include <string>
#include "ParticleSystem.h"

using namespace gdp; 

typedef unsigned int munition;
#define MORTAR	0
#define TURRET	1
#define MISSILE	2
#define LASER	3
#define CLUSTER	4

class ArtilleryGame {
public:
	ArtilleryGame();
	~ArtilleryGame();

	void Initialize();
	void Destroy();

	void StartNewGame();
	void GameUpdate();
	void DisplayTextToUser(const std::string& text);

private:
	GameObject* CreateGameObjectByType(const std::string& type);

	GameObject*					m_PlayerTank;
	GameObject*					m_EnemyTank;
	std::vector<GameObject*>	m_Bullet;
	std::vector<GameObject*>	m_ExplosionParticles;

	ParticleSystem*				particleSystem;
	glm::vec3					aimVec;
	munition					selectedMuni;
	bool						isGameOver;
	const unsigned int			MAX_BULLETS = 200;
	const int					EXPLOSION_PARTICLES = 100;

	void FireProjectile();
	void CreateExplosion(glm::vec3 position);
};

// Utility function for a random range of two floats
float RandFloat(float min, float max);