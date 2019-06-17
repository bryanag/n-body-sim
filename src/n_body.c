#include "n_body.h"
#include <math.h>

#define GRAVITY 0.00000000006674

double gravitational_force(Particle * particle_one, Particle * particle_two)
{
	double radius = sqrt(pow((particle_two->position[0] - particle_one->position[0]), 2.0) + pow((particle_two->position[1] - particle_one->position[1]), 2.0));
	double force = GRAVITY * particle_one->mass * particle_two->mass / pow(radius, 2.0);
	return force;
}

double increment_v(Particle * particles, int particle_count, Particle * particle, double time_step)
{
	for(int i = 0; i < particle_count; i++)
	{
		if(particle != &particles[i])
		{
			double radius_vector[2] = {particles[i].position[0] - particle->position[0], particles[i].position[1] - particle->position[1]};
			double radius = sqrt(pow((particles[i].position[0] - particle->position[0]), 2.0) + pow((particles[i].position[1] - particle->position[1]), 2.0));
			double g_unit_vector[2] = {radius_vector[0] / radius, radius_vector[1] / radius};

			particle->velocity[0] += (gravitational_force(&particles[i], particle) * time_step / particle->mass) * g_unit_vector[0];
			particle->velocity[1] += (gravitational_force(&particles[i], particle) * time_step / particle->mass) * g_unit_vector[1];
		}
	}

	return 0;
}

