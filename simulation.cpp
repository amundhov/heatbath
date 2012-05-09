#include "simulation.h"

#include <math.h>

Simulation::Simulation(int systemLength, double Tmin, double Tmax, int seed):
    systemLength(systemLength)
{
    rng = gsl_rng_alloc(gsl_rng_mt19937);
    gsl_rng_set(rng,seed);

    // Open OUTFILE for writing.
#ifdef SAMPLE_TO_FILE
    sprintf(filename,"out_L_%i_Tmin_%f_Tmax_%f%s.dat", DIMENSION, Tmin, Tmax, SUFFIX);
    filedescriptor = fopen(filename, "w");
#endif

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
        int j=0;
#ifdef PREFILL
        for( j=0; j<systemLength/4; j++ ) {
#endif
        lattice1[i*systemLength+j] = 0;
        lattice2[i*systemLength+j] = 1;
#ifdef PREFILL
        }
#endif
    }
    for( int i=0; i<systemLength; i++ ) {
        double gradient =  (Tmax-Tmin)/(systemLength-1);
        temperature[i] = Tmin + gradient*i;
    }
}

Simulation::~Simulation()
{
	printf("--> Aborted. Cleaning up");
    gsl_rng_free(rng);
#ifdef SAMPLE_TO_FILE
    fclose(filedescriptor);
#endif
}

void Simulation::sample()
{
    // Update difference map d(i,j)
    for ( int i=0; i<systemLength*systemLength; i++ ) {
        difference[i] = (lattice1[i] == lattice2[i]);
    }
    // Update interface I(i)
    Sample sample;
    sample.I = 0;
    sample.Wsquared = 0;
    sample.iteration = iteration;
    for ( int row=0; row<systemLength; row++ ) {
        int column;
        for (column=systemLength-1; column; column-- ) {
            if (!difference[row*systemLength+column]) break;
        }
        interface[row] = column;
        sample.I += column;
    }
    sample.I /= systemLength;
    for ( int i=0; i<systemLength; i++ ) {
        sample.Wsquared += pow(interface[i] - sample.I,2.0d);
    }
    sample.Wsquared /= systemLength;

    // Write sample point to OUTFILE or STDOUT
#ifdef SAMPLE_TO_FILE
    fprintf(filedescriptor,"%f %f %i\n", sample.I, sample.Wsquared, sample.iteration);
    fflush(filedescriptor);
#endif
    printf("%f %f %u\n", sample.I, sample.Wsquared, sample.iteration);


}

void Simulation::truncate()
{
    // Close filehandle and open for writing
#ifdef SAMPLE_TO_FILE
    fclose(filedescriptor);
    filedescriptor = fopen(filename, "w");
#endif
}

void Simulation::evolve(int numberOfIterations)
{
    for (int iter=0; iter<numberOfIterations; iter++ ) {
        unsigned long row    = gsl_rng_uniform_int(rng, systemLength);
        unsigned long column = gsl_rng_uniform_int(rng, systemLength-2)+1; // Edges not to be updated
        double r = gsl_rng_uniform(rng);
        heatBath(lattice1,row,column,r);
        heatBath(lattice2,row,column,r);
    }
    iteration++;
}

void Simulation::heatBath(unsigned char lattice[DIMENSION], unsigned long row, unsigned long column, double r)
{
    double weight[Q];
    int position = row*systemLength+column;

    // Work out spin weights for nodes
    double cummWeight = 0;
    for (int qValue=0; qValue<Q; qValue++ ) {
        int neighbours = 0;
        if (lattice[position-1] == qValue) neighbours++;
        if (lattice[position+1] == qValue) neighbours++;
        if (lattice[indices[position].up] == qValue) neighbours++;
        if (lattice[indices[position].down] == qValue) neighbours++;
        weight[qValue] = exp((double)neighbours/temperature[column]);
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
    /* Find apropriate new spin based on given random uniform r */
    double cumm = weight[0];
    int qValue;
    for( qValue=1; r>cumm; qValue++ ) cumm += weight[qValue];
#ifdef DEBUG
    printf("r == %f , Picked value %i\n", r, qValue);
#endif
    lattice[position] = qValue-1;
}
