#!/bin/bash


for eachfile in `ls in/in*.txt`

do

a=`echo $eachfile | tr -d -c 0-9`

echo "Working with $a, diff is:"

`./main "in/in${a}.txt" > "myout/myout${a}.txt"`

diff "out/out${a}.txt" "myout/myout${a}.txt"

done