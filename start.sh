#! /usr/bin/env sh

name=$(echo $1 | awk 'BEGIN{FS="/"}{split($NF,a,/\?/); print a[1]}')
echo "Creating directory \"$name\"..."
if mkdir "$name" 2> /dev/null; then
    cd "$name"
    echo "Choose which language:"
    echo " 1. Python"
    echo " 2. C++"
    read answer
    if   [ "$answer" = "1" ]; then file="$name.py"; template="../templates/empty.py"
    elif [ "$answer" = "2" ]; then file="$name.cpp"; template="../templates/empty.cpp"
    else echo "No option selected, skipping this step"
    fi
    if ! [ -z "$file" ]; then
        cp "$template" "$file"
        echo "created \"$name/$file\""
        code -r "$file"
    fi
    ../fetchsamples.sh "$name"
else
    echo "directory \"$name\" already exists!"
fi