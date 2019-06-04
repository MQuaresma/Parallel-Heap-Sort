echo "Seq:"

./getMed.sh seq_8192.txt 
./getMed.sh seq_65536.txt 
./getMed.sh seq_1572864.txt 
./getMed.sh seq_3145728.txt 

echo ""
echo "8192:"
echo "Tree:"

./getMed.sh par_8192_2_tree.txt 
./getMed.sh par_8192_4_tree.txt 
./getMed.sh par_8192_8_tree.txt 
./getMed.sh par_8192_16_tree.txt 

echo "Level:"

./getMed.sh par_8192_2_level.txt 
./getMed.sh par_8192_4_level.txt 
./getMed.sh par_8192_8_level.txt 
./getMed.sh par_8192_16_level.txt 

echo ""
echo "65536:"
echo "Tree:"

./getMed.sh par_65536_2_tree.txt 
./getMed.sh par_65536_4_tree.txt 
./getMed.sh par_65536_8_tree.txt 
./getMed.sh par_65536_16_tree.txt 

echo "Level:"

./getMed.sh par_65536_2_level.txt 
./getMed.sh par_65536_4_level.txt 
./getMed.sh par_65536_8_level.txt 
./getMed.sh par_65536_16_level.txt 

echo ""
echo "1572864:"
echo "Tree:"

./getMed.sh par_1572864_2_tree.txt 
./getMed.sh par_1572864_4_tree.txt 
./getMed.sh par_1572864_8_tree.txt 
./getMed.sh par_1572864_16_tree.txt 

echo "Level:"

./getMed.sh par_1572864_2_level.txt 
./getMed.sh par_1572864_4_level.txt 
./getMed.sh par_1572864_8_level.txt 
./getMed.sh par_1572864_16_level.txt 

echo ""
echo "3145728:"
echo "Tree:"

./getMed.sh par_3145728_2_tree.txt 
./getMed.sh par_3145728_4_tree.txt 
./getMed.sh par_3145728_8_tree.txt 
./getMed.sh par_3145728_16_tree.txt 

echo "Level:"

./getMed.sh par_3145728_2_level.txt 
./getMed.sh par_3145728_4_level.txt 
./getMed.sh par_3145728_8_level.txt 
./getMed.sh par_3145728_16_level.txt 
