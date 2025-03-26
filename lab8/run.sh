EXECUTABLE=prog

gcc -Wall -ggdb main.c -o$EXECUTABLE

for a in $(seq 1 10); do
    ./$EXECUTABLE $(wc -l < "$a.txt") < "$a.txt"
done

rm $EXECUTABLE
