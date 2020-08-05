#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include "physics.h"

#define LINE_DELIM "------------\n"

Body *init_body(char *body_data);

static int finished = 0;
void interrupt_handler()
{
	finished = 1;
}

int main(int argc, char *argv[])
{
	signal(SIGINT, interrupt_handler);

	if(argc != 2)
	{
		printf("Usage: ./n-body-sim bodies-file\n");
		return 1;
	}

	FILE *stream;
	char *line = NULL;
	size_t len = 0;

	stream = fopen(argv[1], "r");
	if(stream == NULL)
	{
		printf("File not found");
		return 1;
	}

	int max_bodies = 25;
	Body **bodies = malloc(sizeof(Body *) * max_bodies);

	int body_count = 0;
	while(getline(&line, &len, stream) != -1)
	{
		if(body_count >= max_bodies - 1)
		{
			max_bodies *= 2;	
			bodies = realloc(bodies, max_bodies);
		}

		bodies[body_count] = init_body(line);	
		body_count++;
	}
	free(line);
	fclose(stream);

	float time_step = 0.001;
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

		time_elapsed += time_step;
		double effective_time = time_elapsed/60;

		for(int i = 0; i < body_count; i++)
		{
			printf("%s Position: [%3.6Lf, %3.6Lf]\n%s Velocity: [%Lf, %Lf]\n", 
					bodies[i]->name, bodies[i]->pos[0], bodies[i]->pos[1], 
					bodies[i]->name, bodies[i]->velocity[0], 
					bodies[i]->velocity[1]);
		}
		printf("Time Elapsed: [%f] Minutes\n", effective_time);
		printf(LINE_DELIM);
	}

	for(int i = 0; i < body_count; i++)
	{
		free(bodies[i]->name);
		free(bodies[i]);
	}
	free(bodies);

	return 0;
}

Body *init_body(char *body_data)
{
	Body *body = malloc(sizeof(Body));

	char *token = strtok(body_data, " ");
	body->name = malloc(strlen(token));
	strcpy(body->name, token);

	token = strtok(NULL, " ");
	body->pos[0] = atof(token);

	token = strtok(NULL, " ");
	body->pos[1] = atof(token);

	token = strtok(NULL, " ");
	body->mass = atof(token);

	token = strtok(NULL, " ");
	body->velocity[0] = atof(token);

	token = strtok(NULL, " ");
	body->velocity[1] = atof(token);

	return body;
}
