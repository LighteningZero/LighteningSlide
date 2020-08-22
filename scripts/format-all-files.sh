#!/bin/bash 
echo $1

function dfs_dirs() {
    echo scanning $1
    for file in ` echo $1"/"*.cc `
    do
        if [ ! -f "$file" ]
        then
            echo "skipping .cc files in $1"
        else
            echo formatting $file
            clang-format $file > /tmp/formatted.cc
            cat /tmp/formatted.cc > $file
        fi
    done

    for file in ` echo *.h `
    do
        if [ ! -f "$file" ]
        then
            echo "skipping .h files in $1"
        else
            echo formatting $file
            clang-format $file > /tmp/formatted.cc
            cat /tmp/formatted.cc > $file
        fi
    done

    for file in ` ls $1 `
    do
        if [ -d $1"/"$file ]   
        then
            dfs_dirs $1"/"$file  
        fi
    done
}

cd `dirname $0`
cd ..
INIT_PATH="$(pwd)"  
dfs_dirs $INIT_PATH