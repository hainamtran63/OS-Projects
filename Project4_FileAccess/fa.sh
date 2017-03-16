#!/bin/bash
if [ "$#" -eq 0 ]
then
	./a.out 	
else
	for FILE1 in "$@"
	do
		./a.out $FILE1
	done
fi
