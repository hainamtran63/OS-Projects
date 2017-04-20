#!/bin/bash

recurse_dir(){
    for file in $1
    do
        if [ -d $file ] ; then
            let level=$4+1
            print_dir $1 $file $root $level
        fi
    done 
}

# rootFile, root#
print_dir () {
    let root=$2+1
    let arg=$root
    arg+="p"
    ls -l $1 | grep '^d' | awk '{print $9}' | sed -n $arg
    #recurse for current root
    for file in $1
    do
        if [ -d $file ] ; then
            
            print_dir $1 $root
        fi
    done
}

print_dir $1 0