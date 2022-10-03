#include "ParticleSystem.h"
#include <iostream>
#include <iomanip>

//#define DEBUG_LOG_ENABLED
#ifdef DEBUG_LOG_ENABLED
#define DEBUG_PRINT(x, ...) printf(x, __VA_ARGS__)
#else
#define DEBUG_PRINT(x)
#endif

// Default Constructor
ParticleSystem::ParticleSystem(){
	DEBUG_PRINT("ParticleSystem::ParticleSystem();\n");
	ParticleSystem(glm::vec3(0.0f), 10);
}

// Overloaded Constructor 
// Accepts a position and the number of particles to be generated
ParticleSystem::ParticleSystem(const glm::vec3 position, unsigned int numParticles){
	DEBUG_PRINT("ParticleSystem::ParticleSystem(const glm::vec3 position, unsigned int numParticles);\n");
	this->position			 = position;
	this->numParticles		 = numParticles;
	this->numParticlesAvail  = numParticles;
	this->indexAvailParticle = 0;
	this->particles.resize(numParticles);
	for (int i = 0; i < numParticles; i++) {
		particles[i].setPosition(position);
	}
}

// Destructor
ParticleSystem::~ParticleSystem() {
	DEBUG_PRINT("ParticleSystem::~ParticleSystem();\n");
	for (int i = 0; i < numParticles; i++) {
		particles[i].~Particle();
	}
}

// Method that grabs a dead Particlle from the pool and make it alive
// accepts Up Vector
void ParticleSystem::AllocateParticle(glm::vec3 upVector){
	DEBUG_PRINT("ParticleSystem::AllocateParticle(munition type);\n");
	// Checks if there are particles available
	if (numParticlesAvail == 0) {
		DEBUG_PRINT("ParticleSystem::AllocateParticle - Error - All particles are alive, can't create a new particle!\n");
		return;
	}
	Particle& p = particles[indexAvailParticle];
	if (p.getAge() >= 0) {
		DEBUG_PRINT("ParticleSystem::AllocateParticle - Error - Oldest particle still alive, can't create a new particle!\n");
		return;
	}

	// Transform the dead particle into a living one with static age of 5s
	p.setVelocity(upVector);
	p.setAge(5.0f);
	
	// Particle allocated, one less particle available
	this->numParticlesAvail--;
	// Checks if index is at the end of the vector, if so index = 0, else index++
	indexAvailParticle == (numParticles-1) ? indexAvailParticle = 0 : indexAvailParticle++;
	return;
}

// Method that grabs a dead Particlle from the pool and make it alive
// accepts Up Vector, Acceleration, Age, Damping and Mass
void ParticleSystem::AllocateParticle(glm::vec3 upVector, glm::vec3 acceleration, float age, float damping, float mass){
	DEBUG_PRINT("ParticleSystem::AllocateParticle(munition type);\n");
	// Checks if there are particles available
	if (numParticlesAvail == 0) {
		DEBUG_PRINT("ParticleSystem::AllocateParticle - Error - All particles are alive, can't create a new particle!\n");
		return;
	}
	// Cheks if particle available at index is alive
	Particle& p = particles[indexAvailParticle];
	if (p.getAge() >= 0) {
		DEBUG_PRINT("ParticleSystem::AllocateParticle - Error - Oldest particle still alive, can't create a new particle!\n");
		return;
	}

	// Transform the dead particle into a living one
	p.setVelocity(upVector);
	p.setAcceleration(acceleration);
	p.setAge(age);
	p.setDamping(damping);
	p.setMass(mass);

	// Particle allocated, one less particle available
	this->numParticlesAvail--;
	// Checks if index is at the end of the vector, if so index = 0, else index++
	indexAvailParticle == (numParticles - 1) ? indexAvailParticle = 0 : indexAvailParticle++;
	return;
}

// Method that grabs a dead Particlle from the pool and make it alive
// accepts Position Up Vector, Acceleration, Age, Damping and Mass
void ParticleSystem::AllocateParticle(glm::vec3 position, glm::vec3 upVector, glm::vec3 acceleration, float age, float damping, float mass){
	DEBUG_PRINT("ParticleSystem::AllocateParticle(munition type);\n");
	// Checks if there are particles available
	if (numParticlesAvail == 0) {
		DEBUG_PRINT("ParticleSystem::AllocateParticle - Error - All particles are alive, can't create a new particle!\n");
		return;
	}
	// Cheks if particle available at index is alive
	Particle& p = particles[indexAvailParticle];
	if (p.getAge() >= 0) {
		DEBUG_PRINT("ParticleSystem::AllocateParticle - Error - Oldest particle still alive, can't create a new particle!\n");
		return;
	}

	// Transform the dead particle into a living one
	p.setPosition(position);
	p.setVelocity(upVector);
	p.setAcceleration(acceleration);
	p.setAge(age);
	p.setDamping(damping);
	p.setMass(mass);

	// Particle allocated, one less particle available
	this->numParticlesAvail--;
	// Checks if index is at the end of the vector, if so index = 0, else index++
	indexAvailParticle == (numParticles - 1) ? indexAvailParticle = 0 : indexAvailParticle++;
	return;
}

// Method that Integrate all living particles
// Accepts float deltaType
void ParticleSystem::Integrate(float dt){
	for (int i = 0; i < numParticles; i++) {
		Particle& p = particles[i];
		// Checks if the particle is alive
		if (p.getAge() > 0) {
			p.Integrate(dt);
			// Checks if the position of the particle isn't the ground
			if (p.getPosition().y <= 0.0f) {
				// Reset the particle if its on the ground
				p.setAge(-1);
				p.setPosition(this->position);
				numParticlesAvail++;
				DEBUG_PRINT("ParticleSystem::Integrate Particle Reseted\n");
			}
		}
		else if (p.getAge() < 0 && p.getAge() != -1) {
			// Reset the particle if its dead
			p.setAge(-1);
			p.setPosition(this->position);
			numParticlesAvail++;
			DEBUG_PRINT("ParticleSystem::Integrate Particle Reseted\n");
		}
	}
}

// Method that Integrate all living particles and checks for Collision
// Accepts float deltaType
bool ParticleSystem::IntegrateAndCheckCollision(float dt, glm::vec3 enemyPosition){
	for (int i = 0; i < numParticles; i++) {
		Particle& p = particles[i];
		// Checks if the particle is alive
		if (p.getAge() > 0) {
			p.Integrate(dt);
			// Checks if the position of the particle is on the ground
			if (p.getPosition().y <= 0.0f) {
				float distanceToTarget = glm::distance(enemyPosition, p.getPosition());
				float enemyRadius = 2.0f;
				// Float beautifier
				std::cout << std::fixed             // fix the number of decimal digits
						  << std::setprecision(2);  // to 2
				// Checks distance to the target
				if (distanceToTarget <= enemyRadius) {
					std::cout << "Hit! Nice Shot!" << std::endl;
					killAllParticles();
					return true;
				} else {
					std::cout << "Miss! You missed the target by " << std::setw(5) << distanceToTarget << " meters!" << std::endl;
				}

				// Reset the particle if its on the ground
				p.setAge(-1);
				p.setPosition(this->position);
				numParticlesAvail++;
				DEBUG_PRINT("ParticleSystem::Integrate Particle Reseted\n");
			}
			// Checks acceleration to determine if its the LASER
			else if (p.getAcceleration().y > -9.8f) {
				float distanceToTarget = glm::distance(enemyPosition, p.getPosition());
				float enemyRadius = 2.0f;
				// Float beautifier
				std::cout << std::fixed             // fix the number of decimal digits
						  << std::setprecision(2);  // to 2
				// Checks distance to the target
				if (distanceToTarget <= enemyRadius) {
					std::cout << "Hit! Nice Shot!" << std::endl;
					killAllParticles();
					return true;
				}
				else {
					std::cout << "The Laser Beam hasn't reached the enemy target yet. Distance to target: " << std::setw(5) << distanceToTarget << " meters!" << std::endl;
				}
			}
		}
		else if(p.getAge() < 0 && p.getAge() != -1){
			// Reset the particle if its dead
			p.setAge(-1);
			p.setPosition(this->position);
			numParticlesAvail++;
			DEBUG_PRINT("ParticleSystem::Integrate Particle Reseted\n");
		}
	}
	return false;
}

// Method that cheks distance between two vectors
float ParticleSystem::getDistanceTwoVectors(glm::vec3 v1, glm::vec3 v2)
{
	float xdist = v1.x - v2.x;
	xdist *= xdist;

	float ydist = v1.y - v2.y;
	ydist *= ydist;

	float zdist = v1.z - v2.z;
	zdist *= zdist;

	return sqrt(xdist + ydist + zdist);
}

// Method that resets all particles
void ParticleSystem::killAllParticles(){
	for (int i = 0; i < numParticles; i++) {
		particles[i].setAge(-1);
	}
	this->numParticlesAvail = this->numParticles;
}

// Getters and Setters
void ParticleSystem::setPosition(glm::vec3 position){
	this->position = position;
	// Also set position of all dead particles to the new position
	for (int i = 0; i < numParticles; i++) {
		Particle& p = particles[i];
		if (p.getAge() < 0)
			p.setPosition(this->position);
	}
}

Particle* ParticleSystem::getParticle(unsigned int index)
{
	return &this->particles[index];
}

unsigned int ParticleSystem::getNumParticles()
{
	return this->numParticles;
}

unsigned int ParticleSystem::getNumParticlesAvail()
{
	return this->numParticlesAvail;
}
