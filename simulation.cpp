#include "simulation.h"

#include <math.h>


Simulation::Simulation(int systemLength, double Tmin, double Tmax, int seed):
    systemLength(systemLength)
{
    lattice1 = new unsigned char[systemLength*systemLength];
    lattice2 = new unsigned char[systemLength*systemLength];
    indices = new NodeIndex[systemLength*systemLength];
    temperature = new double[systemLength];
    rng = gsl_rng_alloc(gsl_rng_mt19937);
    gsl_rng_set(rng,seed);

    // Open OUTFILE for appending.
    sprintf(filename,"out_L_%i_Tmin_%f_Tmax_%f%s.dat", dimension, Tmin, Tmax, SUFFIX);
    filedescriptor = fopen(filename, "a");

    for( int i=0; i<systemLength*systemLength; i++ ) {
        /* GSL generates an integer in the range [0,Q-1] with uniform probability */
        unsigned long spin = gsl_rng_uniform_int(rng,Q);
        lattice1[i] = spin;
        lattice2[i] = spin;
    }
    for( int row=0; row<systemLength; row++ ) {
        for( int column=0; column<systemLength; column++ ) {
            unsigned int pos = row*systemLength+column+1;
            /* Precalculate indices needed for periodic boundary conditions */
            indices[pos].up = ( row == (systemLength-1) ? pos - systemLength*(systemLength-1) : pos + systemLength);
            indices[pos].down = ( row == 0 ? pos + systemLength*(systemLength-1) : pos - systemLength);
        }
    }
    for( int i=0; i<systemLength; i++ ) {
        lattice1[i*systemLength] = 0;
        lattice2[i*systemLength] = 1;
    }
    for( int i=0; i<systemLength; i++ ) {
        double gradient =  (Tmax-Tmin)/(systemLength-1);
        temperature[i] = Tmin + gradient*i;
    }
}

void Simulation::sample()
{
    fprintf(filedescriptor, "Foo!!\n");
    // Update difference map d(i,j)

    // Update interface I(i)

    // Write sample point to OUTFILE

}

void Simulation::truncate()
{
    // Close filehandle and open for writing
    fclose(filedescriptor);
    filedescriptor = fopen(filename, "w");
}

void Simulation::evolve(int numberOfIterations)
{
    double weight[Q];
    int position;
    for (int iter=0; iter<numberOfIterations; iter++ ) {

        // Pick random node
        unsigned long row    = gsl_rng_uniform_int(rng, systemLength);
        unsigned long column = gsl_rng_uniform_int(rng, systemLength-2); // Edges not selectable
        position = row*systemLength+column+1;

        // Work out spin weights for nodes
        double cummWeight = 0;
        for (int qValue=0; qValue<Q; qValue++ ) {
            int neighbours = 0;
            if (lattice1[position-1] == qValue) neighbours++;
            if (lattice1[position+1] == qValue) neighbours++;
            if (lattice1[indices[position].up] == qValue) neighbours++;
            if (lattice1[indices[position].down] == qValue) neighbours++;
            weight[qValue] = exp((double)neighbours/temperature[systemLength-column]);
            cummWeight += weight[qValue];
        }
#ifdef DEBUG
        printf(" Probabilities \n");
#endif
        // Normalize weights
        for (int qValue=0; qValue<Q; qValue++ ) {
            weight[qValue] /= cummWeight;
#ifdef DEBUG
            printf("%f\n", weight[qValue]);
#endif
        }
        // Draw a number in the range [0,1] and assign apropriate spin value
        double r = gsl_rng_uniform(rng);
        double cumm = weight[0];
        int qValue;
        for( qValue=1; r>cumm; qValue++ ) cumm += weight[qValue];
#ifdef DEBUG
        printf("r == %f , Picked value %i\n", r, qValue);
#endif
        lattice1[position] = qValue-1;
    }
}

void Simulation::heatBath(unsigned char *lattice)
{
    double weight[Q];
    int position;
    // Pick random node
    unsigned long row    = gsl_rng_uniform_int(rng, systemLength);
    unsigned long column = gsl_rng_uniform_int(rng, systemLength-2); // Edges not selectable
    position = row*systemLength+column+1;

    // Work out spin weights for nodes
    double cummWeight = 0;
    for (int qValue=0; qValue<Q; qValue++ ) {
        int neighbours = 0;
        if (lattice1[position-1] == qValue) neighbours++;
        if (lattice1[position+1] == qValue) neighbours++;
        if (lattice1[indices[position].up] == qValue) neighbours++;
        if (lattice1[indices[position].down] == qValue) neighbours++;
        weight[qValue] = exp((double)neighbours/temperature[systemLength-column]);
        cummWeight += weight[qValue];
    }
#ifdef DEBUG
    printf(" Probabilities \n");
#endif
    // Normalize weights
    for (int qValue=0; qValue<Q; qValue++ ) {
        weight[qValue] /= cummWeight;
#ifdef DEBUG
            printf("%f\n", weight[qValue]);
#endif
    }
    // Draw a number in the range [0,1] and assign apropriate spin value
    double r = gsl_rng_uniform(rng);
    double cumm = weight[0];
    int qValue;
    for( qValue=1; r>cumm; qValue++ ) cumm += weight[qValue];
#ifdef DEBUG
    printf("r == %f , Picked value %i\n", r, qValue);
#endif
    lattice1[position] = qValue-1;
}
