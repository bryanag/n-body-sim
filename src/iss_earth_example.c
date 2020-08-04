#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include "n_body.h"

#define EARTH_MASS 5973600000000000000000000.0
#define EARTH_RADIUS 6378000.0
#define ISS_ALTITUDE 406000
#define ISS_MASS 419725
#define ISS_VELOCITY 7670
#define LINE_DELIM "------------\n"

Body *init_earth();
Body *init_iss();

static int finished = 0;
void interrupt_handler()
{
	finished = 1;
}

int main(int argc, char *argv[])
{
	signal(SIGINT, interrupt_handler);

	int body_count = 2;
	float time_step = 0.001;
	Body **bodies = malloc(sizeof(Body *) * body_count);

	bodies[0] = init_earth();
	bodies[1] = init_iss();

	double time_elapsed = 0;

	while(!finished)
	{
		for(int i = 0; i < body_count; i++)
		{
			increment_v(bodies, body_count, bodies[i], time_step);
		}

		for(int i = 0; i < body_count; i++)
		{
			bodies[i]->pos[0] += bodies[i]->velocity[0] * time_step;
			bodies[i]->pos[1] += bodies[i]->velocity[1] * time_step;
		}

		printf("ISS Position: [%3.6Lf, %3.6Lf]\nISS Velocity: [%Lf, %Lf]\n", 
				bodies[1]->pos[0], bodies[1]->pos[1], bodies[1]->velocity[0], 
				bodies[1]->velocity[1]);

		time_elapsed += time_step;
		double effective_time = time_elapsed/60;
		printf("Time Elapsed: [%f] Minutes\n", effective_time);
		printf(LINE_DELIM);
	}

	free(bodies[0]);
	free(bodies[1]);
	free(bodies);

	return 0;
}

Body *init_earth()
{
	Body *body = malloc(sizeof(Body));
	body->pos[0] = 0;
	body->pos[1] = 0;

	body->mass = EARTH_MASS;
	body->velocity[0] = 0;
	body->velocity[1] = 0;

	return body;
}

Body *init_iss()
{
	Body *body = malloc(sizeof(Body));
	body->pos[0] = ISS_ALTITUDE + EARTH_RADIUS;
	body->pos[1] = 0;

	body->mass = ISS_MASS;
	body->velocity[0] = 0;
	body->velocity[1] = ISS_VELOCITY;

	return body;
}
