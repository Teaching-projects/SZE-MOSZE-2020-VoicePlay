#!/bin/bash

IFS=$'\n'

rm output.txt

for i in `cat battles.txt`; do
  echo "$i" | ./a.out >> output.txt
done
