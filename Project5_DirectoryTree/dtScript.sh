#!/bin/bash

print_dir () {
    echo "$2: "
    ls -l $1 | grep '^d' | awk '{print $9}'
    
    for file in $1/*
    do
        if [ -d ${file} ] ; then
            one=1
            level="$2+$one"
            print_dir ${file} ${level}
        fi
    done
}

print_dir $1 0