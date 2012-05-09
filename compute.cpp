#include "parameters.h"
#include "simulation.h"

#include <stdio.h>
#include <string.h>
#include <signal.h>

#ifndef TMIN
#define TMIN 0.4
#endif

#ifndef TMAX
#define TMAX 1.8
#endif

//char command='\0';
Simulation sim(DIMENSION, TMIN, TMAX);
volatile sig_atomic_t abortRun =  0;

void termination_handler(int signum)
{
	abortRun=1;
}

void register_termination_handler()
{
	struct sigaction new_action, old_action;
	new_action.sa_handler = termination_handler;
	sigemptyset(&new_action.sa_mask);
    sigaction(SIGINT, NULL, &old_action);
    if (old_action.sa_handler != SIG_IGN) sigaction(SIGINT, &new_action, NULL);
    sigaction(SIGHUP, NULL, &old_action);
    if (old_action.sa_handler != SIG_IGN) sigaction(SIGHUP, &new_action, NULL);
    sigaction(SIGTERM, NULL, &old_action);
    if (old_action.sa_handler != SIG_IGN) sigaction(SIGTERM, &new_action, NULL);
}

int main(int argc, char* argv[])
{
	register_termination_handler();
    sim.evolve(PRE_ITERATIONS);
	printf("---> %i preiterations done.\n", PRE_ITERATIONS);
	while(!abortRun) {
		sim.evolve(ITERATIONS_PER_SAMPLE);
		sim.sample();
	}
	printf("TERMINATING");
}
