#include <stdio.h>
#include <math.h>
#include <stdlib.h>

/* Take in filename and starting sample as arguments.
   Compute average of <I> and <W^2>                   */

int main(int argc, char* argv[])
{
	int iteration;
	int firstSample;
	sscanf(argv[2],"%u", &firstSample);
	float I,Wsquared;
	double iterations;
	double cummI = 0;
	double cummW = 0;
	if (argc < 3) {
		   printf("Usage: %s filename firstSample\n", argv[0]);
		   exit(0);
	}
	printf("%s",argv[0]);
	FILE *file;
	file = fopen(argv[1], "r");
	if (!file) exit(0);
	while(fscanf(file,"%f %f %u", &I, &Wsquared, &iteration) == 3)
	{
		if (iteration < firstSample) continue;
		cummI += I;
		cummW += sqrt(Wsquared);
	}
	iterations = iteration-firstSample+1;
	printf("%f %f %f\n", cummI/iteration, cummW/iteration, iterations);

	return 0;
}
