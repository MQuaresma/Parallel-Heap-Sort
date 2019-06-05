perf report -i seq_8192 -n > ../report/seq_8192
perf report -i seq_65536 -n > ../report/seq_65536
perf report -i seq_1572864 -n > ../report/seq_1572864
perf report -i seq_3145728 -n > ../report/seq_3145728

perf report -i par_8192_2_tree -n > ../report/par_8192_2_tree
perf report -i par_8192_2_level -n > ../report/par_8192_2_level
perf report -i par_8192_4_tree -n > ../report/par_8192_4_tree
perf report -i par_8192_4_level -n > ../report/par_8192_4_level
perf report -i par_8192_8_tree -n > ../report/par_8192_8_tree
perf report -i par_8192_8_level -n > ../report/par_8192_8_level
perf report -i par_8192_16_tree -n > ../report/par_8192_16_tree
perf report -i par_8192_16_level -n > ../report/par_8192_16_level

perf report -i par_65536_2_tree -n > ../report/par_65536_2_tree
perf report -i par_65536_2_level -n > ../report/par_65536_2_level
perf report -i par_65536_4_tree -n > ../report/par_65536_4_tree
perf report -i par_65536_4_level -n > ../report/par_65536_4_level
perf report -i par_65536_8_tree -n > ../report/par_65536_8_tree
perf report -i par_65536_8_level -n > ../report/par_65536_8_level
perf report -i par_65536_16_tree -n > ../report/par_65536_16_tree
perf report -i par_65536_16_level -n > ../report/par_65536_16_level

perf report -i par_1572864_2_tree -n > ../report/par_1572864_2_tree
perf report -i par_1572864_2_level -n > ../report/par_1572864_2_level
perf report -i par_1572864_4_tree -n > ../report/par_1572864_4_tree
perf report -i par_1572864_4_level -n > ../report/par_1572864_4_level
perf report -i par_1572864_8_tree -n > ../report/par_1572864_8_tree
perf report -i par_1572864_8_level -n > ../report/par_1572864_8_level
perf report -i par_1572864_16_tree -n > ../report/par_1572864_16_tree
perf report -i par_1572864_16_level -n > ../report/par_1572864_16_level

perf report -i par_3145728_2_tree -n > ../report/par_3145728_2_tree
perf report -i par_3145728_2_level -n > ../report/par_3145728_2_level
perf report -i par_3145728_4_tree -n > ../report/par_3145728_4_tree
perf report -i par_3145728_4_level -n > ../report/par_3145728_4_level
perf report -i par_3145728_8_tree -n > ../report/par_3145728_8_tree
perf report -i par_3145728_8_level -n > ../report/par_3145728_8_level
perf report -i par_3145728_16_tree -n > ../report/par_3145728_16_tree
perf report -i par_3145728_16_level -n > ../report/par_3145728_16_level
