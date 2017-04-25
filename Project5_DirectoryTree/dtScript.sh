#!/bin/bash

# file, indent value
print_file() {
    word=""
    COUNTER=0
    while [  $COUNTER -lt $2 ]; do
        word+="-"
        let COUNTER=COUNTER+1 
    done
    echo $word$1
}

# dir, indent value
print_dir () {

    print_file $1 $2

    for file in $(ls "$1")
    do
        if [ -d ${1}/${file} ] ; then
            let num=$2+1
            print_dir "${1}/${file}" $num
        fi
    done
}

display_dir() {
    let level=$2+1
    row=1
    for file in $(ls "$1")
    do
        

        let line=$row
        line+="p"
        echo info:$row, $line, $1
        ls -l $1 | grep '^d' | awk '{print $9}' | sed -n $line
        display_dir "${1}/${file}" $level
        let row+=1
    done
}

#ls -l $1 | grep '^d' | awk '{print $9}' | sed -n 1p

echo $1
display_dir $1 0