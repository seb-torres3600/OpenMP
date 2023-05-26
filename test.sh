#!/bin/bash
make

for i in {1 2 3 4 5 6 7 8 9 10 11 12 13 14 15}
do 
    shuf -i0-2147483643 -n382 > case$i.txt
    sort -n case$i.txt > case$i.ans
    ./mysort case$i.txt -o case$i.my -t4 --alg=merge
    cmp --silent case$i.my case$i.ans && echo "Pass (5pts)" || echo "Fail (0pts)"

rm case*
done


for i in {1 2 3 4 5 6 7 8 9 10}
do 
    shuf -i0-2147483643 -n382 > case$i.txt
    sort -n case$i.txt > case$i.ans
    ./mysort case$i.txt -o case$i.my -t 8 --alg=merge
    cmp --silent case$i.my case$i.ans && echo "Pass (5pts)" || echo "Fail (0pts)"

rm case*
done

make clean
