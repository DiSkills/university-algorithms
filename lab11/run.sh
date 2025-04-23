EXECUTABLE=prog

average() {
    sum=0
    for k in $(seq 1 100); do
        result=$(./$EXECUTABLE "$1")
        sum=$((sum + result))
    done
    echo $((sum / 100))
}

make

echo "n T(n)"
for n in $(seq 1 10); do
    result=$(average "$n")
    printf "%d %d\n" "$n" "$result"
done

make clean
