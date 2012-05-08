#ifndef SIMULATION_H
#define SIMULATION_H

#include <gsl/gsl_rng.h>
#include <stdio.h>

#include "parameters.h"

typedef struct { unsigned int up;
                 unsigned int down;
} NodeIndex;

typedef struct { double I;
                 double Wsquared;
                 unsigned long int iteration;
} sample;

class Simulation
{
public:
    Simulation(int length, double Tmin, double Tmax, int seed=0);

    void evolve(int numberOfIterations);
    void sample();   // Writes sample to OUTFILE
    void truncate(); // Truncates OUTFILE

    unsigned char *lattice1;
    unsigned char *lattice2;
    NodeIndex *indices;
    double *temperature;

private:
    void heatBath(unsigned char *lattice);
    gsl_rng *rng;
    int systemLength;
    FILE *filedescriptor;
    char filename[100];

};

#endif // SIMULATION_H
