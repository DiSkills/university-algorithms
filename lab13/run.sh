EXECUTABLE=prog

average() {
    sum=0
    for k in $(seq 1 1000); do
        result=$(./$EXECUTABLE "$1" "$1")
        sum=$((sum + result))
    done
    echo $((sum / 1000))
}

gcc -o "$EXECUTABLE" main.c

echo "n T(n)"
n=2
for i in $(seq 1 11); do
    n=$((n * 2))
    result=$(average "$n")
    printf "%d %d\n" "$n" "$result"
done

rm "$EXECUTABLE"
