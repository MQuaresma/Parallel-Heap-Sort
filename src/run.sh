#!/bin/sh

make clean
make

#rm -rf times
#mkdir times
#rm -rf perf
#mkdir perf
#mkdir perf/record
#mkdir perf/stat

#SEQ
SIZE=8192
    NUM=0
    while [ $NUM -lt 15 ]; do
        ./seq_heapsort $SIZE >> times/seq_$SIZE.txt
        let NUM=NUM+1
    done
    perf stat -o perf/stat/seq_$SIZE ./seq_heapsort $SIZE
    perf record -F 99 -g -o perf/record/seq_$SIZE ./seq_heapsort $SIZE

SIZE=65536
    NUM=0
    while [ $NUM -lt 15 ]; do
        ./seq_heapsort $SIZE >> times/seq_$SIZE.txt
        let NUM=NUM+1
    done
    perf stat -o perf/stat/seq_$SIZE ./seq_heapsort $SIZE
    perf record -F 99 -g -o perf/record/seq_$SIZE ./seq_heapsort $SIZE

SIZE=1572864
    NUM=0
    while [ $NUM -lt 15 ]; do
        ./seq_heapsort $SIZE >> times/seq_$SIZE.txt
        let NUM=NUM+1
    done
    perf stat -o perf/stat/seq_$SIZE ./seq_heapsort $SIZE
    perf record -F 99 -g -o perf/record/seq_$SIZE ./seq_heapsort $SIZE

SIZE=3145728
    NUM=0
    while [ $NUM -lt 15 ]; do
        ./seq_heapsort $SIZE >> times/seq_$SIZE.txt
        let NUM=NUM+1
    done
    perf stat -o perf/stat/seq_$SIZE ./seq_heapsort $SIZE
    perf record -F 99 -g -o perf/record/seq_$SIZE ./seq_heapsort $SIZE

#PAR
SIZE=8192
    OMP_NUM_THREADS=2
    while [ $OMP_NUM_THREADS -lt 17 ]; do
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

SIZE=65536
    OMP_NUM_THREADS=2
    while [ $OMP_NUM_THREADS -lt 17 ]; do
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

SIZE=1572864
    OMP_NUM_THREADS=2
    while [ $OMP_NUM_THREADS -lt 17 ]; do
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

SIZE=3145728
    OMP_NUM_THREADS=2
    while [ $OMP_NUM_THREADS -lt 17 ]; do
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
