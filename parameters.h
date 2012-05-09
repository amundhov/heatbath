#ifndef PARAMETERS_H
#define PARAMETERS_H

#define window_dimension 540
#define ITERATIONS_PER_SAMPLE 1000000
#define PRE_ITERATIONS 0

#ifndef Q
#define Q 3
#endif
#ifndef DIMENSION
#define DIMENSION 100
#endif

#ifdef PREFILL
#define SUFFIX "_prefill"
#else
#define SUFFIX ""
#endif

#define SEED 0

#define SAMPLE_TO_FILE


#endif // PARAMETERS_H
