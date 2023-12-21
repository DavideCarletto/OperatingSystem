#!/bin/bash

if [ $# != 3 ]; then
    echo "Errore, necessario inserire 3 parametri"
    exit 1
fi

path="./$1"

res=$(find $path -name "*.c")

path="./$3"

echo -n "" > "$path"

for var in $res; do
    risultato=$(exec grep -Hn "$2 *(.*)" $var | sort -k 1,2 -t ":"| tr ":" "\t")
    echo "$risultato" >> "$path"
done

exit 0