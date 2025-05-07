EXECUTABLE=prog

make

n=4
echo "n T(n)"
while [ $n -le 1024 ]; do
    result=$(./$EXECUTABLE "$n")
    printf "%d %d\n" "$n" "$result"
    n=$((n * 2))
done

make clean
