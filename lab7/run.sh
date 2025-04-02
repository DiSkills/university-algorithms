EXECUTABLE=prog

gcc -o "$EXECUTABLE" main.c

echo "m s E(m, s) D(m, s)"
for m in 10 20 30 40 50 100 500 1000; do
    for s in 2 5 10 100; do
        result=$(./$EXECUTABLE "$m" "$((m * s))")
        printf "%d %d %s\n" "$m" "$((m * s))" "$result"
    done
done

rm "$EXECUTABLE"
