

gcc sumSimple.c -o vectorsum  -lm
# possible input: 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
./vectorsum 3 4 5 6 7 8 9 10 11 12 13 14 15

gcc -o vectorsumomp -fopenmp sumOmp.c -lm -O3
OMP_NUM_THREADS=3 ./vectorsumomp 3 4 5 6 7 8 9 10 11 12 13 14 15