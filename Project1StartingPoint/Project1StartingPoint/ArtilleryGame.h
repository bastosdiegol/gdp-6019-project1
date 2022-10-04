#pragma once

#include <gdp/Engine.h>
#include <string>
#include "ParticleSystem.h"

using namespace gdp; 

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

	// Instance of Particle System
	ParticleSystem*				particleSystem;
	// Up vector for the cannon aim
	glm::vec3					aimVec;
	// Delta Time for Integrations
	const float					DELTA_TIME = 0.005;
	// Current selected munition
	munition					selectedMuni;
	// Variable to check if enemy is hit and game is over
	bool						isGameOver;
	// Variable to check if enemy is hit and its time for explosion effect
	bool						isExplosionTime = false;
	// Total number of particles used for bullets
	const unsigned int			MAX_BULLETS			= 50;
	// Total number of particles used on the explosion - Cannot be higer then MAX_BULLETS
	const int					EXPLOSION_PARTICLES = 50;
	// Timer to check time elapsed during explosion
	float						EXPLOSION_TIMER		= 0.0f;
	// Expected life cycle duration of explosion particles
	const float					EXPLOSION_DURATION	= 3.0f;

	// Function that allocates a particle and fire it as projectile
	void FireProjectile();
	// Function that creates an explosion using the Particle System
	void CreateExplosion(glm::vec3 position);
	// Outputs lots of gameplay info
	void newGameInfo();
};