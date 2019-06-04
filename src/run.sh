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

#SEQ
SIZE=512
while [ $SIZE -lt 2049 ]; do
    NUM=0
    while [ $NUM -lt 15 ]; do
        ./seq_heapsort $SIZE >> times/seq_$SIZE.txt
        let NUM=NUM+1
    done
    let SIZE=$SIZE*2
done

#PAR
SIZE=512
while [ $SIZE -lt 2049 ]; do
    OMP_NUM_THREADS=2
    while [ $OMP_NUM_THREADS -lt 33 ]; do
        NUM=0
        while [ $NUM -lt 15 ]; do
            ./par_heapsort $SIZE $OMP_NUM_THREADS 0 >> times/par_${SIZE}_tree.txt
            ./par_heapsort $SIZE $OMP_NUM_THREADS 1 >> times/par_${SIZE}_level.txt
            let NUM=NUM+1
        done
        let OMP_NUM_THREADS=$OMP_NUM_THREADS*2
    done
    let SIZE=$SIZE*2
done
