#!/bin/bash

FILE=output.txt
INPF=prepared.json

if test -f $FILE
then
	rm $FILE
fi

cat steps.txt | ./a.out $INPF >> $FILE
