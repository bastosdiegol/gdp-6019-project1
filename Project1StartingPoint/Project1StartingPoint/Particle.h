#pragma once
#include <gdp/Engine.h>

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

	// Method to print Particle info on the console
	void PrintInfo();
	// Method to Integrate the Particle on a specified Delta Time
	void Integrate(float dt);

	//Getters and Setters
	void setPosition(glm::vec3 position);
	void setVelocity(glm::vec3 velocity);
	void setAcceleration(glm::vec3 acceleration);
	void setAge(float age);
	void setDamping(float damping);
	void setMass(float mass);
	// ---
	glm::vec3 getPosition();
	float getAge();

protected:
	// Variables of the Particle
	glm::vec3 position;
	glm::vec3 velocity;
	glm::vec3 acceleration;

	float age;		// ttl
	float damping;
	float mass;		// f = ma
};