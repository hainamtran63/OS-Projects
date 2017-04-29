#!/bin/bash
echo Program:
./a.out $1 | sort
echo Shell Script:
ls -R -l $1 | grep '^d' | awk '{print $9}' | sort

diff <(./a.out $1 | sort) <(ls -R -l $1 | grep '^d' | awk '{print $9}' | sort)
DIFF=$?

if [[ $DIFF -eq 0 ]]
then
    echo "The outputs are similar!"
fi