#include <stdlib.h>
#include <stdio.h>
#include "n_body.h"

#define EARTH_MASS 5973600000000000000000000.0
#define EARTH_RADIUS 6378000.0
#define ISS_ALTITUDE 406000
#define LINE_DELIM "------------\n"

int main(int argc, char *argv[])
{
	int particle_count = 2;
	float time_step = 0.001;
	Particle * particles = malloc(sizeof(Particle) * particle_count);

	for(int i = 0; i < particle_count; i++) 
	{
		particles[i].position[0] = i * (ISS_ALTITUDE + EARTH_RADIUS);
		particles[i].position[1] = 0;
		if(i == 0)
		{
			particles[i].mass = EARTH_MASS;
			particles[i].velocity[0] = 0;
			particles[i].velocity[1] = 0;
		}
		else
		{
			particles[i].mass = 419725;
			particles[i].velocity[0] = 0;
			particles[i].velocity[1] = 7670;
		}
	}
	double time_elapsed = 0;

	while(1)
	{
		for(int i = 0; i < particle_count; i++)
		{
			increment_v(particles, particle_count, &particles[i], time_step);
		}

		for(int i = 0; i < particle_count; i++)
		{
			particles[i].position[0] += particles[i].velocity[0] * time_step;
			particles[i].position[1] += particles[i].velocity[1] * time_step;

		}
		printf("ISS Position: [%3.6Lf, %3.6Lf]\nISS Velocity: [%Lf, %Lf]\n", particles[1].position[0], particles[1].position[1], particles[1].velocity[0], particles[1].velocity[1]);
		time_elapsed += time_step;
		double effective_time = time_elapsed/60;
		printf("Time Elapsed: [%f] Minutes\n", effective_time);
		printf(LINE_DELIM);
	}

	return 0;
}
