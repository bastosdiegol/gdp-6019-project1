#pragma once

#include <gdp/Engine.h>

class Particle {
	// Private area
public:
	// Default Constructor
	Particle();
	// Destructor
	~Particle();
	// Overloaded Constructor
	Particle(const Particle& particle);
	// Overloaded Copy Operator
	Particle operator=(const Particle& particle);

	// Variables of the Particle
	glm::vec3 position;
	glm::vec3 velocity;
	glm::vec3 acceleration;

	float age;
	float damping;
	float mass;					// f = ma

	// Method to print Particle info on the console
	void PrintInfo();
	// Method to Integrate the Particle on a specified Delta Time
	void Integrate(float dt);
};