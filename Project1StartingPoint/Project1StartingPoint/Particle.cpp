#include "Particle.h"
#include <iostream>

#define DEBUG_LOG_ENABLED
#ifdef DEBUG_LOG_ENABLED
#define DEBUG_PRINT(x, ...) printf(x, __VA_ARGS__)
#else
#define DEBUG_PRINT(x)
#endif

// Default Constructor
Particle::Particle()
	: position(0.0f)
	, velocity(0.0f)
	, acceleration(0.0f)
	, damping(1.0f)
	, mass(1.0f)
	, age(-1.0f)
{
	DEBUG_PRINT("Particle::Particle();\n");
}

// Destructor
Particle::~Particle() {
	DEBUG_PRINT("Particle::~Particle();\n");
}

// Overloaded Constructor
Particle::Particle(const Particle& particle) {
	DEBUG_PRINT("Particle::Particle(const Particle& particle);\n");
	this->position		= particle.position;
	this->velocity		= particle.velocity;
	this->acceleration	= particle.acceleration;
	this->damping		= particle.damping;
	this->mass			= particle.mass;
	this->age			= particle.age;
}

// Overloaded Copy Operator
Particle Particle::operator=(const Particle& particle) {
	DEBUG_PRINT("Particle::operator=();\n");

	return Particle();
}

// Method to print Particle info on the console
void Particle::PrintInfo() {

	DEBUG_PRINT("-----------------\n");
	DEBUG_PRINT("Velocity(%f, %f, %f)\n", velocity.x, velocity.y, velocity.z);
	DEBUG_PRINT("Position(%f, %f, %f)\n", position.x, position.y, position.z);

}

// Method to Integrate the Particle on a specified Delta Time
void Particle::Integrate(float dt) {
	//velocity = velocity + acceleration * dt;
	//velocity *= damping;
	//position = position + velocity * dt;
	velocity = velocity + (acceleration * dt);
	velocity *= damping;
	position = position + (velocity * dt);

	// Aging the Particle
	age -= dt;

	// In case the particle hit the ground
	// Set age to 0 to kill it
	if (position.y <= 0.f) {
		age = 0.f;
	}
}
