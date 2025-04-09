#!/bin/sh

EXEC=prog

gcc main.c -o$EXEC
while read data ; do
    echo ">>> $data"
    ./$EXEC "$data"
done <<EOF
    -123+(12+(31+0~)~)~
    01+(3+(31+4~)~)~
    -0+(0+(31+4~)~)~
    521456+56987~
    000+(0+3~)~
    -12558747
EOF
rm -rf $EXEC
