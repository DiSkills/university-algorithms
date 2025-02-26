EXECUTABLE=prog

average() {
    sum=0
    for k in $(seq 1 1000); do
        result=$(./$EXECUTABLE "$1")
        sum=$((sum + result))
    done
    echo $((sum / 1000))
}

compilation_type=
if [ $# -eq 1 ]; then
    compilation_type="-D$1"
fi

gcc -o "$EXECUTABLE" main.c $compilation_type

echo "n T(n)"
for n in $(seq 100 100 10000); do
    if [ -z "$compilation_type" ]; then
        result=$(average "$n")
    else
        result=$(./$EXECUTABLE "$n")
    fi
    printf "%d %d\n" "$n" "$result"
done

rm "$EXECUTABLE"
