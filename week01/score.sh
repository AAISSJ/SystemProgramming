#!/bin/bash

make
echo $1 $2|./w3.out > answer.txt
echo $1 $2|./w3.out > result.txt

cat answer.txt
cat result.txt

