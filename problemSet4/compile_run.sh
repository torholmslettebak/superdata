source /opt/intel/bin/iccvars.sh intel64
source /opt/intel/bin/compilervars.sh intel64
#gcc sumSimple.c -o vectorsum  -lm
# possible input: 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
#./vectorsum 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 

#icc sumSimple.c -o vectorsum  -lm -02
#./vectorsum 6

icc -O3 -o vectorsumomp -fopenmp sumOmp.c -lm
export OMP_NUM_THREADS=1
./vectorsumomp 14

#icc -o vectorsumomp -fopenmp sumOmp.c -lm -O2
export OMP_NUM_THREADS=2
./vectorsumomp 14

#icc -o vectorsumomp -fopenmp sumOmp.c -lm -O2
export OMP_NUM_THREADS=4
./vectorsumomp 14