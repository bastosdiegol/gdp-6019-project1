#pragma once
#include <gdp/Engine.h>

typedef unsigned int munition;
#define MORTAR	0
#define TURRET	1
#define MISSILE	2
#define LASER	3
#define CLUSTER	4

class Particle {
public:
	// Default Constructor
	Particle();
	// Overloaded Constructor 
	// Accepts a particle
	Particle(const Particle& particle);
	// Destructor
	~Particle();

	// Overloaded Copy Operator
	Particle operator=(const Particle& particle);

	// Method to Integrate the Particle on a specified Delta Time
	void Integrate(float dt);

	// Getters and Setters
	void setPosition(glm::vec3 position);
	void setVelocity(glm::vec3 velocity);
	void setAcceleration(glm::vec3 acceleration);
	void setAge(float age);
	void setDamping(float damping);
	void setMass(float mass);
	void setMunitionType(munition type);
	void setIsClusterArmed(bool clusterArmed);
	// ---
	glm::vec3 getPosition();
	glm::vec3 getVelocity();
	glm::vec3 getAcceleration();
	float getAge();
	float getDamping();
	float getMass();
	munition getMuniType();
	bool getIsClusterArmed();

protected:
	// Variables of the Particle
	glm::vec3 position;
	glm::vec3 velocity;
	glm::vec3 acceleration;

	float	 age;		// ttl
	float	 damping;
	float	 mass;		// f = ma
	munition muniType;	// Type of the particle
	bool	 isClusterArmed = true; // This isn't the best pratice, ideal would be an extended class for CLUSTER munition
};