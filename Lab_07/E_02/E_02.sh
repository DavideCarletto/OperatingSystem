#!/bin/bash

echo "Inserire il nome del file:"
read file

path="./$file"
echo -n "" > "./tmp.txt"
cmd=$(cat $path)

for line in $cmd; do
    echo $line | wc -m >> ./tmp.txt
done

max=$(sort -r -n ./tmp.txt | head -n 1)
nrighe=$(wc -l ./tmp.txt)

echo "$max"
echo "$nrighe"

exit 0