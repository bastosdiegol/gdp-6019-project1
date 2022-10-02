#include "ParticleSystem.h"

#define DEBUG_LOG_ENABLED
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
// accepts Up Vector,  Age, Damping and Mass
void ParticleSystem::AllocateParticle(glm::vec3 upVector, float age, float damping, float mass){
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
	p.setAge(age);
	p.setDamping(damping);
	p.setMass(mass);

	// Particle allocated, one less particle available
	this->numParticlesAvail--;
	// Checks if index is at the end of the vector, if so index = 0, else index++
	indexAvailParticle == (numParticles - 1) ? indexAvailParticle = 0 : indexAvailParticle++;
	return;
}

void ParticleSystem::Integrate(float dt){
	for (int i = 0; i < numParticles; i++) {
		Particle& p = particles[i];
		// Checks if the position of the particle isn't the ground
		if (p.getPosition().y < 0.0f) {
			// Reset the particle if its on the ground
			p.setAge(-1);
			p.setPosition(this->position);
			numParticlesAvail++;
			DEBUG_PRINT("ParticleSystem::Integrate Particle Reseted\n");
		}
		// Checks if the particle is alive
		if (p.getAge() > 0) {
			p.Integrate(dt);
		}
		else if(p.getAge() < 0 && p.getAge() != -1){
			// Reset the particle if its dead
			p.setAge(-1);
			p.setPosition(this->position);
			numParticlesAvail++;
			DEBUG_PRINT("ParticleSystem::Integrate Particle Reseted\n");
		}
	}
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
