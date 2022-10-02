#include "Particle.h"
#include <iostream>

#define DEBUG_LOG_ENABLED
#ifdef DEBUG_LOG_ENABLED
#define DEBUG_PRINT(x, ...) printf(x, __VA_ARGS__)
#else
#define DEBUG_PRINT(x)
#endif

// Default Constructor
Particle::Particle() :	position(0.0f)
					  , velocity(0.0f)
					  , acceleration(0.0f, -9.8f, 0.0f) // Gravity
					  , damping(1.0f)
					  , mass(1.0f)
					  , age(-1.0f){
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

	return Particle(particle);
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
	// Set age to -1 to kill it
	/*if (position.y <= 0.f) {
		age = -1.0f;
	}*/
}

// Getters and Setters
void Particle::setPosition(glm::vec3 position){
	this->position = position;
}

void Particle::setVelocity(glm::vec3 velocity){
	this->velocity = velocity;
}

void Particle::setAcceleration(glm::vec3 acceleration){
	this->acceleration = acceleration;
}

void Particle::setAge(float age){
	this->age = age;
}

void Particle::setDamping(float damping){
	this->damping = damping;
}

void Particle::setMass(float mass){
	this->mass = mass;
}

glm::vec3 Particle::getPosition()
{
	return this->position;
}

float Particle::getAge()
{
	return this->age;
}
