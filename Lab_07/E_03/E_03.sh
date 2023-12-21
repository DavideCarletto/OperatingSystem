#!/bin/bash

cmd=$(find . -type f)

for sol in $cmd; do
    filename=$(basename "$sol")

    filename_upper=$(echo "$filename" | tr 'a-z' 'A-Z')

    newpath=$(dirname "$sol")/"$filename_upper"

    mv "$sol" "$newpath"

    echo "Rinominato: $sol -> $newpath"
done

echo "Rinomina completata."
exit 0
