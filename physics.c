#include "physics.h"
#include <math.h>

#define GRAVITY 0.00000000006674

double grav_force(Body *body_a, Body *body_b)
{
	double radius = sqrt(pow((body_b->pos[0] - body_a->pos[0]), 2.0) 
		   	+ pow((body_b->pos[1] - body_a->pos[1]), 2.0));

	double force = GRAVITY * body_a->mass * body_b->mass / pow(radius, 2.0);
	return force;
}

double increment_v(Body **bodies, int body_count, Body *body, double time_step)
{
	for(int i = 0; i < body_count; i++)
	{
		if(body != bodies[i])
		{
			double radius_vector[2] = {bodies[i]->pos[0] - body->pos[0], 
				bodies[i]->pos[1] - body->pos[1]};

			double radius = sqrt(pow((bodies[i]->pos[0] - body->pos[0]), 2.0) 
					+ pow((bodies[i]->pos[1] - body->pos[1]), 2.0));

			double g_unit_vector[2] = {radius_vector[0] / radius, 
				radius_vector[1] / radius};

			body->velocity[0] += (grav_force(bodies[i], body) * time_step / 
					body->mass) * g_unit_vector[0];
			body->velocity[1] += (grav_force(bodies[i], body) * time_step / 
					body->mass) * g_unit_vector[1];
		}
	}

	return 0;
}
