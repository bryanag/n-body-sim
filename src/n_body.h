#ifndef N_BODY_H_
#define N_BODY_H_

typedef struct Body Body;
struct Body
{       
	long double mass;
	long double velocity[2];
	long double pos[2];
};


double grav_force(Body *body_a, Body *body_b);
double increment_v(Body **bodies, int body_count, Body *body, double t_step);

#endif
