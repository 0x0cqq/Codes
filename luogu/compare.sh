#!/bin/sh

path="Documents/VSCode/Codes/luogu"
gen="gen"
name1="p1169"
name2="p1169_1"
input_file="in.txt"
output_file1="out1.txt"
output_file2="out2.txt"

cd
cd $path
g++-6 $name1.cpp -o $name1 -o2
g++-6 $name2.cpp -o $name2 -o2
g++-6 $gen.cpp -o $gen -o2

echo "\\033[1;33mFinish building.\\033[0m"

cnt=0

while true
do
    ((cnt++))
    ./$gen > $input_file
    ./$name1 < $input_file > $output_file1
    ./$name2 < $input_file > $output_file2
    if diff $output_file1 $output_file2 > /dev/null 2>&1
    then
        echo "\\033[1;32mTask$cnt:Accepted.\\033[0m"
    else 
        echo "\\033[1;31mTask$cnt:Wrong Answer.\\033[0m"
        break
    fi
    sleep 0.5
done
