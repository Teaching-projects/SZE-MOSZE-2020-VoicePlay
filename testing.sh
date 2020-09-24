#!/bin/bash

IFS=$'\n'

for i in `cat battles.txt`; do
  echo "$i" | ./a.out
done
