#!/bin/bash

if [ $# != 3 ]; then
    echo "Errore, necessario inserire 3 parametri"
    exit 1
fi

path="./$1"

res=$(find $path -name "*.c" -exec grep -Hn "$2 *(.*)" {} \; | sort -k 1,2 -t ":" | tr ":" "\t")

path="./$3"

echo "$res" > "$path"

exit 0