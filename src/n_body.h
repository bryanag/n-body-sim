#ifndef N_BODY_H_
#define N_BODY_H_

typedef struct Particle Particle;
struct Particle
{       
	long double mass;
	long double velocity[2];
	long double position[2];
};


double gravitational_force(Particle * particle_one, Particle * particle_two);
double increment_v(Particle * particles, int particle_count, Particle * particle, double time_step);

#endif
