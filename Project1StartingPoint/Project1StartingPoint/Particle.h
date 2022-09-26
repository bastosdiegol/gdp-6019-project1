#pragma once

#include <gdp/Engine.h>

class Particle {
	// Private area
public:
	Particle();
	~Particle();
	Particle(const Particle& particle);
	Particle operator=(const Particle& particle);

	glm::vec3 position;
	glm::vec3 velocity;
	glm::vec3 acceleration;

	float age;
	float damping;
	float mass;					// f = ma

	void PrintInfo();
	void Integrate(float dt);
};