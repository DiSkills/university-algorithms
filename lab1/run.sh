EXECUTABLE=prog

gcc -o$EXECUTABLE -Wall -ggdb main.c

for n in $(seq 2 2 30); do
    printf "%d " $(./$EXECUTABLE $n)
done;

printf "\n"

rm $EXECUTABLE
