#!/bin/sh
#
#PBS -N ESC
#PBS -l walltime=60:00
#PBS -l nodes=1:r641:ppn=32
#PBS -q mei

module load gcc/5.3.0

cd HeapSort

rm ESC.*
make clean
make

rm -rf times
mkdir times
mkdir perf
mkdir perf/record
mkdir perf/stat

#SEQ
SIZE=512
while [ $SIZE -lt 2049 ]; do
    NUM=0
    while [ $NUM -lt 15 ]; do
        ./seq_heapsort $SIZE >> times/seq_$SIZE.txt
        let NUM=NUM+1
    done
    perf stat -o perf/stat/seq_$SIZE ./seq_heapsort $SIZE
    perf record -F 99 -g -o perf/record/seq_$SIZE ./seq_heapsort $SIZE
    let SIZE=$SIZE*2
done

#PAR
SIZE=512
while [ $SIZE -lt 2049 ]; do
    OMP_NUM_THREADS=2
    while [ $OMP_NUM_THREADS -lt 33 ]; do
        NUM=0
        while [ $NUM -lt 15 ]; do
            ./par_heapsort $SIZE $OMP_NUM_THREADS 1 >> times/par_${SIZE}_${OMP_NUM_THREADS}_tree.txt
            ./par_heapsort $SIZE $OMP_NUM_THREADS 2 >> times/par_${SIZE}_${OMP_NUM_THREADS}_level.txt
            let NUM=NUM+1
        done
        perf stat -o perf/stat/par_${SIZE}_${OMP_NUM_THREADS}_tree ./par_heapsort $SIZE $OMP_NUM_THREADS 1
        perf stat -o perf/stat/par_${SIZE}_${OMP_NUM_THREADS}_level ./par_heapsort $SIZE $OMP_NUM_THREADS 2
        perf record -F 99 -g -o perf/record/par_${SIZE}_${OMP_NUM_THREADS}_tree ./par_heapsort $SIZE $OMP_NUM_THREADS 1
        perf record -F 99 -g -o perf/record/par_${SIZE}_${OMP_NUM_THREADS}_level ./par_heapsort $SIZE $OMP_NUM_THREADS 2
        let OMP_NUM_THREADS=$OMP_NUM_THREADS*2
    done
    let SIZE=$SIZE*2
done
