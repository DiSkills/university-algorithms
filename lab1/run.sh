EXECUTABLE=prog

gcc -o$EXECUTABLE -Wall -ggdb main.c

echo "n T(n)"
for n in $(seq 2 2 30); do
    printf "%d %d\n" $n $(./$EXECUTABLE $n)
done;

rm $EXECUTABLE
