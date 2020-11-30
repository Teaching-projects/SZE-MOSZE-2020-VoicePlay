#!/bin/bash

FILE=output.txt
INPF=scenario1.json

if test -f $FILE
then
	rm $FILE
fi

cat steps.txt | ./a.out >> $FILE
