#ifndef PARAMETERS_H
#define PARAMETERS_H

#define window_dimension 540
#define ITERATIONS_PER_SAMPLE 10000000
#define PRE_ITERATIONS 0

#ifndef Q
#define Q 2
#endif
#ifndef DIMENSION
#define DIMENSION 300
#endif

#ifdef PREFILL
#define SUFFIX "_prefill"
#else
#define SUFFIX ""
#endif

#define SAMPLE_TO_FILE


#endif // PARAMETERS_H
