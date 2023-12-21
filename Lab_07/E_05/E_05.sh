#!/bin/bash

zombie=1

matches=$(ps -el | grep $1)

# echo "$?"
if [ $? -eq 0 ]; then
    for ((i=0; i<5; i++)); do
        state=$(echo $matches | cut -f 2 -d " ")
        pid=$(echo $matches | cut -f 4 -d " ")
        # echo "$state $pid"

        if [ "$state" != "Z" ]; then
            let "zombie=0"
        fi

        sleep $2
    done

    if [ $zombie -eq 1 ]; then
        echo "Terminazione forzata del processo $pid"
        kill -9 $pid
    fi
else 
    echo "Nessun processo con il nome corrispondente trovato"
fi

exit 0
