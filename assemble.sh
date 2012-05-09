#!/bin/bash

g++ -DQ=2 -DDIMENSION=200 -DSEED=1e5 -o compute-Q2-L200-SEED1e5-vanilla compute.cpp simulation.cpp -lgsl -lgslcblas
g++ -DQ=2 -DDIMENSION=200 -DSEED=0 -o   compute-Q2-L200-SEED0-vanilla compute.cpp simulation.cpp -lgsl -lgslcblas
g++ -DQ=2 -DDIMENSION=250 -DSEED=1e5 -o compute-Q2-L250-SEED1e5-vanilla compute.cpp simulation.cpp -lgsl -lgslcblas
g++ -DQ=2 -DDIMENSION=250 -DSEED=0 -o compute-Q2-L250-SEED0-vanilla compute.cpp simulation.cpp -lgsl -lgslcblas
g++ -DQ=2 -DDIMENSION=300 -DSEED=1e5 -DPREFILL -o compute-Q2-L300-SEED1e5-prefill compute.cpp simulation.cpp -lgsl -lgslcblas
g++ -DQ=2 -DDIMENSION=300 -DSEED=0 -DPREFILL -o compute-Q2-L300-SEED0-prefill compute.cpp simulation.cpp -lgsl -lgslcblas
g++ -DQ=2 -DDIMENSION=150 -DSEED=0 -o compute-Q2-L150-SEED0-vanilla compute.cpp simulation.cpp -lgsl -lgslcblas
g++ -DQ=2 -DDIMENSION=150 -DSEED=1e5 -o compute-Q2-L150-SEED1e5-vanilla compute.cpp simulation.cpp -lgsl -lgslcblas


g++ -DQ=3 -DDIMENSION=200 -DSEED=1e5 -o compute-Q3-L200-SEED1e5-vanilla compute.cpp simulation.cpp -lgsl -lgslcblas
g++ -DQ=3 -DDIMENSION=200 -DSEED=0 -o   compute-Q3-L200-SEED0-vanilla compute.cpp simulation.cpp -lgsl -lgslcblas
g++ -DQ=3 -DDIMENSION=250 -DSEED=1e5 -o compute-Q3-L250-SEED1e5-vanilla compute.cpp simulation.cpp -lgsl -lgslcblas
g++ -DQ=3 -DDIMENSION=250 -DSEED=0 -o compute-Q3-L250-SEED0-vanilla compute.cpp simulation.cpp -lgsl -lgslcblas
g++ -DQ=3 -DDIMENSION=300 -DSEED=1e5 -DPREFILL -o compute-Q3-L300-SEED1e5-prefill compute.cpp simulation.cpp -lgsl -lgslcblas
g++ -DQ=3 -DDIMENSION=300 -DSEED=0 -DPREFILL -o compute-Q3-L300-SEED0-prefill compute.cpp simulation.cpp -lgsl -lgslcblas
g++ -DQ=3 -DDIMENSION=150 -DSEED=0 -o compute-Q3-L150-SEED0-vanilla compute.cpp simulation.cpp -lgsl -lgslcblas
g++ -DQ=3 -DDIMENSION=150 -DSEED=1e5 -o compute-Q3-L150-SEED1e5-vanilla compute.cpp simulation.cpp -lgsl -lgslcblas
