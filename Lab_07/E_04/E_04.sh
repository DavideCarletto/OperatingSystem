#!/bin/bash

if [ $# != 1 ]; then
    echo "Inserire il nome del file in ingresso:"
    read input_file
else 
    input_file="$1"
fi

h=0
cmd=$(cat $input_file)

for word in $cmd; do
    flag=0
    for ((i=0; i<${#word_array[*]}; i++)); do
        if [ "${word_array[$i]}" == "$word" ]; then
            freq_array[$i]=$((freq_array[$i]+1))
            flag=1
            fi
    done

    if [ $flag -eq 0 ]; then
        word_array[$h]=$word
        freq_array[$h]=1
        h=$(($h+1))
    fi

done

for(( i=0; i<${#word_array[*]}; i++ )); do
    echo ${word_array[$i]} "-" ${freq_array[$i]}
done

exit 0