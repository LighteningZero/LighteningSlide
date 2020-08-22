#!/bin/bash 

function dfs_dirs(){  
    for file in ` ls $1 `  
    do
        if [ -d $1"/"$file ]   
        then  
            dfs_dirs $1"/"$file  
        else  
            clang-format $1 > /tmp/formatted.cc
            cat /tmp/formatted.cc > $1
        fi
    done
}

cd `dirname $0`
INIT_PATH="$(pwd)/.."  
dfs_dirs $INIT_PATH