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
} Sample;

class Simulation
{
public:
    Simulation(int length, double Tmin, double Tmax, int seed=0);
    ~Simulation();

    void evolve(int numberOfIterations);
    void sample();   // Writes sample to OUTFILE
    void truncate(); // Truncates OUTFILE

    unsigned char lattice1[DIMENSION*DIMENSION];
    unsigned char lattice2[DIMENSION*DIMENSION];
    unsigned char difference[DIMENSION*DIMENSION];
    NodeIndex indices[DIMENSION*DIMENSION];
    double temperature[DIMENSION];
    unsigned long int interface[DIMENSION];

private:
    void heatBath(unsigned char *lattice, unsigned long row, unsigned long column, double r);
    gsl_rng *rng;
    int systemLength;
    FILE *filedescriptor;
    char filename[100];
    unsigned long long int iteration;

};

#endif // SIMULATION_H
