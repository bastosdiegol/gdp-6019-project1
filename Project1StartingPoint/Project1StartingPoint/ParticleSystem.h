#pragma once
#include <gdp/Engine.h>
#include <vector>
#include "Particle.h"

class ParticleSystem {
public:
	// Default Constructor
	ParticleSystem();
	// Overloaded Constructor 
	// Accepts a position and the number of particles to be generated
	ParticleSystem(const glm::vec3 position, unsigned int numParticles);
	// Destructor
	~ParticleSystem();


	// Method that grabs a dead Particlle from the pool and make it alive
	// accepts Up Vector
	void AllocateParticle(glm::vec3 upVector);
	// Method that grabs a dead Particlle from the pool and make it alive
	// accepts Up Vector, Acceleration, Age, Damping and Mass
	void AllocateParticle(glm::vec3 upVector, glm::vec3 acceleration, float age, float damping, float mass);
	// Method that grabs a dead Particlle from the pool and make it alive
	// accepts Position Up Vector, Acceleration, Age, Damping and Mass
	void AllocateParticle(glm::vec3 position, glm::vec3 upVector, glm::vec3 acceleration, float age, float damping, float mass);
	// Method that Integrate all living particles
	// Accetps a float deltaType
	void Integrate(float dt);
	// Method that Integrate all living particles and checks for Collision
	// Accepts float deltaType
	bool IntegrateAndCheckCollision(float dt, glm::vec3 enemyPosition);
	// Method that checks if theres projectile collision with the enemy
	bool isEnemyHit(glm::vec3 enemyPosition);
	// Method that outputs the values of each living particle
	void PrintParticleInfo();
	// Method that cheks distance between two vectors
	float getDistanceTwoVectors(glm::vec3 v1, glm::vec3 v2);
	// Method that resets all particles
	void killAllParticles();

	// Getters and Setters
	void setPosition(glm::vec3 position);
	Particle* getParticle(unsigned int index);
	unsigned int getNumParticles();
	unsigned int getNumParticlesAvail();

private:
	// Number of Particles of the System
	unsigned int numParticles;
	// Number of Particles alive
	unsigned int numParticlesAvail;
	// Available Particle Index
	unsigned int indexAvailParticle;
	// Vector of particles
	std::vector<Particle> particles;
	// Position of the System
	glm::vec3 position;
};


