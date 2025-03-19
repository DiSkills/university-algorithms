EXECUTABLE=$1

average() {
    sum=0
    for k in $(seq 1 1000); do
        result=$(./$EXECUTABLE "$1")
        sum=$(echo "$sum + $result" | bc -l)
    done
    echo "scale=6; $sum / 1000" | bc -l
}

make $1

echo "a C(a)"
for a in $(seq 0.05 0.05 0.95); do
    result=$(average "$a")
    printf "%.2f %.4f\n" "$a" "$result"
done

make clean
