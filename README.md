# Parallel-Heap-Sort

Parallel implementation of the heap sort algorithm in a shared memory paradigm using Pthreads.
The implementation supports different granularity levels in terms of critical zones as well
as dynamically changing the number of threads.
Race conditions are avoided using different synchronization primitves to prevent race conditions.

For more information you can have a look [here (PT version only)](report).
