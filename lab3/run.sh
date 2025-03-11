EXECUTABLE=prog

average() {
    sum=0
    for k in $(seq 1 1000); do
        result=$(./$EXECUTABLE "$1")
        sum=$((sum + result))
    done
    echo $((sum / 1000))
}

gcc -o "$EXECUTABLE" main.c

echo "n T(n)"
for n in $(seq 100 100 1000); do
    result=$(average "$n")
    printf "%d %d\n" "$n" "$result"
done

rm "$EXECUTABLE"
