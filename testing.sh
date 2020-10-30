#!/bin/bash

FILE=output.txt

if test -f $FILE
then
	rm $FILE
fi
n = 1
for unit1 in scenarios/* 
do
	./a.out $unit1 >> $FILE
done
