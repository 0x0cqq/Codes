#!/bin/sh

path="Documents/VSCode/Codes/luogu"
name1="p1963"
name2="p1963_1"
gen="gen"

cd
cd $path
g++-6 $name1.cpp -o $name1 
g++-6 $name2.cpp -o $name2
g++-6 $gen.cpp -o $gen

echo "\\033[1;31mFinish building.\\033[0m"

cnt=0

while ((1))
do
    ((cnt++))
    ./$gen > in.txt
    ./$name1 < in.txt > out1.txt
    ./$name2 < in.txt > out2.txt
    if diff out1.txt out2.txt &> /dev/null
    then
        echo "\\033[1;32mTask$cnt:Accepted.\\033[0m"
    else 
        echo "\\033[1;33mTask$cnt:Wrong Answer.\\033[0m"
        break
    fi
    sleep 0.5
done


