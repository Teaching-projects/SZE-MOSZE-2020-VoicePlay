#!/bin/bash

FILE=output.txt

if test -f $FILE
then
	rm $FILE
fi

for unit1 in units/* 
do
	for unit2 in units/* 
  do
    printf $unit1" "$unit2"\n"
		if [ $unit1 != $unit2 ]
    then
			./a.out $unit1 $unit2 >> $FILE
		fi
	done
done

diff $FILE exp_output.txt