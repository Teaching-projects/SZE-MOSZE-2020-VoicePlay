#!/bin/bash

FILE=output.txt
INPF=scneario1.json

if test -f $FILE
then
	rm $FILE
fi

./a.out $INPF >> $FILE
