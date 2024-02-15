exec="$1"
gen="$2"
if [[ "$1" =~ .*\.cpp ]]; then
    g++ "$1" -g
    exec="./a.out"
elif [[ "$1" =~ .*\.py ]]; then
    exec="python3 $1"
fi

if [[ "$2" =~ .*\.cpp ]]; then
    g++ "$2" -g
    gen="./a.out"
elif [[ "$2" =~ .*\.py ]]; then
    gen="python3 $2"
fi

numsuccess=0
$gen > input.txt
while $exec < input.txt &> /dev/null; do
    numsuccess=$(($numsuccess+1))
    echo "$numsuccess: success"
    $gen > input.txt
done
