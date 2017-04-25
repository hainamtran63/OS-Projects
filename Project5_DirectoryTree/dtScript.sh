#!/bin/bash

#ls -R -l $1 | grep '^d' | awk '{print $9}' | sort

find $1 -type d -print