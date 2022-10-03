#include "Particle.h"
#include <iostream>

//#define DEBUG_LOG_ENABLED
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

void Particle::setMunitionType(munition type){
	this->muniType = type;
}

void Particle::setIsClusterArmed(bool clusterArmed){
	this->isClusterArmed = clusterArmed;
}

glm::vec3 Particle::getPosition()
{
	return this->position;
}

glm::vec3 Particle::getVelocity()
{
	return this->velocity;
}

glm::vec3 Particle::getAcceleration()
{
	return this->acceleration;
}

float Particle::getAge()
{
	return this->age;
}

float Particle::getDamping()
{
	return this->damping;
}

float Particle::getMass()
{
	return this->mass;
}

munition Particle::getMuniType()
{
	return this->muniType;
}

bool Particle::getIsClusterArmed()
{
	return this->isClusterArmed;
}
